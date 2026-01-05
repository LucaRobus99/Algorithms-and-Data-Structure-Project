CC = gcc
all: bin/libsort bin/libsort_test

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/libsort: build/libsort.o  build/getfile.o  build/main.o build/utils.o $(COMMON_DEPS)
	$(CC) -o bin/main_ex1 build/utils.o build/getfile.o build/libsort.o  build/main.o

bin/test: build/test.o build/libsort.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/test  build/test.o build/libsort.o build/unity.o
clean:
	rm -f build/* bin/*
