CC=clang
CFLAGS=-Wall -Werror -std=c99 -fPIC -DPIC -g -Og
SRC=src

all: malloc.so

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

malloc.so: mm-frontend.o mm-backend.o mm-frontend-aux.o
	$(LD) -shared -o malloc.so mm-frontend.o mm-backend.o mm-frontend-aux.o

clean:
	rm -f *.o *.so

basic-test: malloc.so
	export LD_PRELOAD=malloc.so
	$(CC) $(CFLAGS) malloc-test.c malloc.so -o malloc-test

.PHONY: all clean