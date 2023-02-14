
OUTDIR=./bin

mkdir:
	@mkdir -p ${OUTDIR}

hash-from-redis: mkdir hash-from-redis/dict.h hash-from-redis/dict.c \
	hash-from-redis/mt19937-64.h hash-from-redis/mt19937-64.c \
	hash-from-redis/siphash.c hash-from-redis/testhelp.h
	gcc hash-from-redis/dict.c hash-from-redis/mt19937-64.c \
	hash-from-redis/siphash.c \
	-o hash-from-redis \
	-I ./hash-from-redis

clean:
	@rm hash-from-redis