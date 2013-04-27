CFLAGS=-ggdb3 -std=c99 -Werror=implicit-function-declaration
LDFLAGS=-lm

.PHONY: all clean

all: build build/algowars

build:
	mkdir -p build

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/algowars: build/main.o build/data_loader.o build/magic_annealing.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)