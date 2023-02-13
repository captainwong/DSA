
#if defined(_MSC_VER) && defined(_DEBUG)
#define AVP_DUMP_MEM_LEAK
#endif

// Necessary includes and defines for memory leak detection:
#ifdef AVP_DUMP_MEM_LEAK
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#ifndef strdup
#define strdup _strdup
#endif
#else
#include <sys/time.h>
#endif


#define USE_QUADRATIC_HASH


#ifdef USE_QUADRATIC_HASH
#include "hash_quadratic.h"
#else
#include "hash_seperate_chaining.h"
#endif

#define TEST_NUM 400



#ifdef AVP_DUMP_MEM_LEAK
// Code to display the memory leak report 
// We use a custom report hook to filter out Qt's own memory leaks
// Credit to Andreas Schmidts - http://www.schmidt-web-berlin.de/winfig/blog/?p=154

_CRT_REPORT_HOOK prevHook;

int customReportHook(int reportType, char* message, int* returnValue) {
    // This function is called several times for each memory leak.
    // Each time a part of the error message is supplied.
    // This holds number of subsequent detail messages after
    // a leak was reported
    const int numFollowupDebugMsgParts = 2;
    static int ignoreMessage = 0;
    static int debugMsgPartsCount = 0;

    // check if the memory leak reporting starts
    if ((strncmp(message, "Detected memory leaks!\n", 10) == 0)
        || ignoreMessage) {
        // check if the memory leak reporting ends
        if (strncmp(message, "Object dump complete.\n", 10) == 0) {
            _CrtSetReportHook(prevHook);
            ignoreMessage = 0;
        } else
            ignoreMessage = 1;

        // something from our own code?
        if (strstr(message, ".cpp") == NULL) {
            if (debugMsgPartsCount++ < numFollowupDebugMsgParts)
                // give it back to _CrtDbgReport() to be printed to the console
                return FALSE;
            else
                return TRUE;  // ignore it
        } else {
            debugMsgPartsCount = 0;
            // give it back to _CrtDbgReport() to be printed to the console
            return FALSE;
        }
    } else
        // give it back to _CrtDbgReport() to be printed to the console
        return FALSE;
}

#endif // AVP_DUMP_MEM_LEAK

long long timeInMilliseconds(void) {
#ifdef _WIN32
    /* Based on https://doxygen.postgresql.org/gettimeofday_8c_source.html */
    const uint64_t epoch = (uint64_t)116444736000000000ULL;
    FILETIME file_time;
    ULARGE_INTEGER ularge;

    GetSystemTimeAsFileTime(&file_time);
    ularge.LowPart = file_time.dwLowDateTime;
    ularge.HighPart = file_time.dwHighDateTime;
    int64_t tv_sec = (int64_t)((ularge.QuadPart - epoch) / 10000000L);
    int32_t tv_usec = (int32_t)(((ularge.QuadPart - epoch) % 10000000L) / 10);
    return (((long long)tv_sec) * 1000) + (tv_usec / 1000);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
#endif
}


uint64_t hash(const void* key) {
    return hash_gen_hash_function(key, strlen((char*)key));
}

int key_compare(hash_t* h, const void* k1, const void* k2) {
    size_t l1, l2;
    l1 = strlen((char*)k1);
    l2 = strlen((char*)k2);
    return l1 == l2 ? memcmp(k1, k2, l1) == 0 : 0;
}

void* key_dup(hash_t* h, const void* key) {
    return strdup((const char*)key);
}

void key_free(hash_t* h, void* val) {
    free(val);
}


hash_type_t benchmark_hash_type = {
    .hash = hash,
    .key_compare = key_compare,
    .key_dup = key_dup,
    .key_free = key_free,
    .val_dup = NULL,
    .val_free = NULL,
};


#define start_benchmark() start = timeInMilliseconds()
#define end_benchmark(msg) do { \
    elapsed = timeInMilliseconds()-start; \
    printf(msg ": %ld items in %lld ms\n", count, elapsed); \
} while(0)

//char* str_from_ll(long long value) {
//    char buf[32];
//    int len;
//    char* s;
//
//    len = sprintf(buf, "%lld", value);
//    s = malloc(len + 1);
//    memcpy(s, buf, len);
//    s[len] = '\0';
//    return s;
//}


char* static_str_from_ll(long long value) {
    static char buf[32];
    sprintf(buf, "%lld", value);
    return buf;
}

int main()
{
    long long start, elapsed;
    long count = 5000000, j;
    hash_t* h;

#if defined(AVP_DUMP_MEM_LEAK)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    prevHook = _CrtSetReportHook(customReportHook);
    //_CrtSetBreakAlloc(4995436); // Use this line to break at the nth memory allocation
#endif

    srand((unsigned int)time(NULL));
	h = hash_create(&benchmark_hash_type);
	assert(h);

    start_benchmark();
    for (j = 0; j < count; j++) {
        int r = hash_insert(h, static_str_from_ll(j), (void*)j);
        assert(r == HASH_OK);
    }
    end_benchmark("Inserting");
    assert(h->used == count);

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(j);
        entry_t* he = hash_find(h, key);
        assert(he != NULL && he->v.val == (void*)j);
    }
    end_benchmark("Linear access of existing elements");

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(j);
        entry_t* he = hash_find(h, key);
        assert(he != NULL && he->v.val == (void*)j);
    }
    end_benchmark("Linear access of existing elements (2nd round)");

    start_benchmark();
    for (j = 0; j < count; j++) {
        long long val = rand() % count;
        char* key = static_str_from_ll(val);
        entry_t* he = hash_find(h, key);
        assert(he != NULL && he->v.val == (void*)val);
    }
    end_benchmark("Random access of existing elements");

    start_benchmark();
    for (j = 0; j < count; j++) {
        entry_t* he = hash_get_random_key(h);
        assert(he != NULL);
    }
    end_benchmark("Accessing random keys");

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(rand() % count);
        key[0] = 'X';
        entry_t* he = hash_find(h, key);
        assert(he == NULL);
    }
    end_benchmark("Accessing missing");

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(j);
        int retval = hash_remove(h, key);
        assert(retval == HASH_OK);
        key[0] += 17; /* Change first number to letter. */
        retval = hash_insert(h, key, (void*)j);
        assert(retval == HASH_OK);
    }
    end_benchmark("Removing and adding");

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(j);
        key[0] += 17; /* Change first number to letter. */
        entry_t* he = hash_find(h, key);
        assert(he != NULL && he->v.val == (void*)j);
    }
    end_benchmark("Linear access of existing elements");

	hash_free(h);

#if defined(AVP_DUMP_MEM_LEAK)
    // Once the app has finished running and has been deleted,
    // we run this command to view the memory leaks:
    _CrtDumpMemoryLeaks();
#endif 
}
