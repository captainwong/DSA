#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <stdint.h>

static FILE* open_file(const char* file) {
	FILE* f = fopen(file, "w");
	if (f == NULL) {
		printf("open %s failed\n", file);
		return NULL;
	}
	return f;
}

#define openfile(name) FILE* f; if (!(f = open_file(name))) return;

static void write_str(const char* file, const char* str)
{
	openfile(file);
	fprintf(f, "%s", str);
	fclose(f);
}

static void write_int(const char* file, int content)
{
	openfile(file);
	fprintf(f, "%d", content);
	fclose(f);
}

static void write_int_array(const char* file, int* arr, int len) {
	openfile(file);
	for (int i = 0; i < len; i++) {
		fprintf(f, "%d ", arr[i]);
	}
	fclose(f);
}

//typedef void(*write_content)(FILE *f);
typedef std::function<void(FILE*)> write_content;

static void gen_in_out(int n, write_content write_in, write_content write_out)
{
	char name[FILENAME_MAX];

	{
		sprintf(name, "testcase/%d.in", n);
		openfile(name);
		if (write_in) {
			write_in(f);
		}
		fclose(f);
	}

	{
		sprintf(name, "testcase/%d.out", n);
		openfile(name);
		if (write_out) {
			write_out(f);
		}
		fclose(f);
	}
}


typedef std::vector<uint64_t> BigInt;

