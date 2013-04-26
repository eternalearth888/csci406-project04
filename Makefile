CFLAGS=-ggdb3 -std=c99

.PHONY: all prepare

all: build build/algowars

build:
	mkdir -p build

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/algowars: build/main.o build/data_loader.o build/magic.o
	$(CC) $(CFLAGS) $^ -o $@
