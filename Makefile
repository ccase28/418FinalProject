CC=clang
CFLAGS=-Wall -Werror -pthread -std=c99 -fPIC -DPIC -Og -g -DDEBUG
LDFLAGS=-lpthread
SRC=src

all: malloc.so

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

malloc.so: msafe-eprintf.o mm-midend.o mm-backend.o mm-midend-aux.o mm-frontend.o mm-frontend-aux.o
	$(LD) $(LDFLAGS) -shared -o malloc.so mm-frontend.o mm-midend.o mm-midend-aux.o mm-backend.o msafe-eprintf.o mm-frontend-aux.o

clean:
	rm -f *.o *.so
	rm -f malloc-test driver

malloc-test: malloc.so malloc-test.c
	export LD_PRELOAD=malloc.so
	$(CC) $(CFLAGS) malloc-test.c malloc.so -o malloc-test

driver: malloc.so driver.c
	export LD_PRELOAD=malloc.so
	$(CC) $(CFLAGS) driver.c malloc.so -o driver

# driver-dbg: driver.o msafe-eprintf.o mm-midend.o mm-backend.o mm-midend-aux.o mm-frontend.o
# 	$(LD) -o driver-dbg driver.o msafe-eprintf.o mm-midend.o mm-backend.o mm-midend-aux.o mm-frontend.o

.PHONY: all clean