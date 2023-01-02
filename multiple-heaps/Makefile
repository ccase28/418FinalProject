CC=clang
CFLAGS=-Wall -Werror -std=c99 -fPIC -DPIC -Og -g -DDEBUG
SRC=src

all: malloc.so

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

malloc.so: msafe-eprintf.o mm-frontend.o mm-backend.o mm-frontend-aux.o
	$(LD) -shared -o malloc.so mm-frontend.o mm-frontend-aux.o mm-backend.o msafe-eprintf.o

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