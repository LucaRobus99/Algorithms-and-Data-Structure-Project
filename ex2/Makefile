CC = gcc
all: bin/skiplist bin/test

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/skiplist: build/skiplist.o build/main.o build/utils.o $(COMMON_DEPS)
	$(CC) -o bin/main_ex2 build/skiplist.o  build/main.o build/utils.o

bin/test: build/test.o build/skiplist.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/test  build/test.o build/skiplist.o build/unity.o

clean:
	rm -f build/* bin/*
