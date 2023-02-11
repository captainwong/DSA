#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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

void key_free(hash_t* h, void* val) {
    free(val);
}

int key_compare(hash_t* h, const void* k1, const void* k2) {
    size_t l1, l2;
    l1 = strlen((char*)k1);
    l2 = strlen((char*)k2);
    return l1 == l2 ? memcmp(k1, k2, l1) == 0 : 0;
}


hash_type_t benchmark_hash_type = {
    .hash = hash,
    .key_dup = NULL,
    .val_dup = NULL,
    .key_free = key_free,
    .val_free = NULL,
    .key_compare = key_compare,
};


#define start_benchmark() start = timeInMilliseconds()
#define end_benchmark(msg) do { \
    elapsed = timeInMilliseconds()-start; \
    printf(msg ": %ld items in %lld ms\n", count, elapsed); \
} while(0)

char* str_from_ll(long long value) {
    char buf[32];
    int len;
    char* s;

    len = sprintf(buf, "%lld", value);
    s = malloc(len + 1);
    memcpy(s, buf, len);
    s[len] = '\0';
    return s;
}


char* static_str_from_ll(long long value) {
    static char buf[32];
    sprintf(buf, "%lld", value);
    return buf;
}

int main()
{
    long long start, elapsed;
    long count = 5000000, j;
	hash_t* h = hash_create(&benchmark_hash_type);
	assert(h);

    start_benchmark();
    for (j = 0; j < count; j++) {
        int r = hash_insert(h, str_from_ll(j), (void*)j);
        assert(r == HASH_OK);
    }
    end_benchmark("Inserting");
    assert(h->used == count);

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(j);
        entry_t* he = hash_find(h, key);
        assert(he != NULL);
    }
    end_benchmark("Linear access of existing elements");

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(j);
        entry_t* he = hash_find(h, key);
        assert(he != NULL);
    }
    end_benchmark("Linear access of existing elements (2nd round)");

    start_benchmark();
    for (j = 0; j < count; j++) {
        char* key = static_str_from_ll(rand() % count);
        entry_t* he = hash_find(h, key);
        assert(he != NULL);
    }
    end_benchmark("Random access of existing elements");

	hash_free(h);
}
