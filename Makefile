CC=clang
CFLAGS=-Wall -Werror -std=c99 -fPIC -DPIC -Og -g -DDEBUG
SRC=src

all: malloc.so

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

malloc.so: msafe-eprintf.o mm-midend.o mm-backend.o mm-midend-aux.o mm-frontend.o
	$(LD) -shared -o malloc.so mm-frontend.o mm-midend.o mm-midend-aux.o mm-backend.o msafe-eprintf.o

clean:
	rm -f *.o *.so
	rm -f malloc-test driver

malloc-test: malloc.so
	export LD_PRELOAD=malloc.so
	$(CC) $(CFLAGS) malloc-test.c malloc.so -o malloc-test

driver: malloc.so 
	export LD_PRELOAD=malloc.so
	$(CC) $(CFLAGS) driver.c malloc.so -o driver

.PHONY: all clean