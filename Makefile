CC=clang
CFLAGS=-Wall -Werror -std=c99 -fPIC -DPIC
SRC=src

all: malloc.so

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

malloc.so: mm-frontend.o mm-backend.o
	$(LD) -shared -o malloc.so mm-frontend.o mm-backend.o

clean:
	rm -f *.o *.so

.PHONY: all clean