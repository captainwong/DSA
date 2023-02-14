CC = gcc
CFLAGS +=

OUTDIR = ./bin

mkdir:
	@mkdir -p ${OUTDIR}

cny: mkdir cny/cny.c
	$(CC) cny/cny.c \
	$(CFLAGS) \
	-o ${OUTDIR}/cny

hash: mkdir hash/hash_quadratic.h hash/hash_quadratic.c hash/hash_seperate_chaining.h hash/hash_seperate_chaining.c \
	hash/hash_test.c hash/siphash.c
	$(CC) hash/hash_quadratic.c hash/hash_seperate_chaining.c hash/hash_test.c hash/siphash.c \
	$(CFLAGS) \
	-o ${OUTDIR}/hash

hash-from-redis: mkdir hash-from-redis/dict.h hash-from-redis/dict.c \
	hash-from-redis/mt19937-64.h hash-from-redis/mt19937-64.c \
	hash-from-redis/siphash.c hash-from-redis/testhelp.h
	$(CC) hash-from-redis/dict.c hash-from-redis/mt19937-64.c \
	hash-from-redis/siphash.c \
	$(CFLAGS) \
	-o ${OUTDIR}/hash-from-redis

clean:
	@rm hash hash-from-redis 

