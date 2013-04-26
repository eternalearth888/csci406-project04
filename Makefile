CFLAGS=-ggdb3

.PHONY: all prepare

all: build build/algowars

build:
	mkdir -p build

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/algowars: build/main.o build/data_loader.o
	$(CC) $(CFLAGS) $^ -o $@
