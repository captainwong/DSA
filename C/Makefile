
OUTDIR=./bin

mkdir:
	@mkdir -p ${OUTDIR}

hash: hash/hash_quadratic.h hash/hash_quadratic.c hash/hash_seperate_chaining.h hash/hash_seperate_chaining.c \
	hash/hash_test.c hash/siphash.c
	gcc hash/hash_quadratic.c hash/hash_seperate_chaining.c hash/hash_test.c hash/siphash.c \
	-o ${OUTDIR}/hash

hash-from-redis: mkdir hash-from-redis/dict.h hash-from-redis/dict.c \
	hash-from-redis/mt19937-64.h hash-from-redis/mt19937-64.c \
	hash-from-redis/siphash.c hash-from-redis/testhelp.h
	gcc hash-from-redis/dict.c hash-from-redis/mt19937-64.c \
	hash-from-redis/siphash.c \
	-o ${OUTDIR}/hash-from-redis

clean:
	@rm hash-from-redis