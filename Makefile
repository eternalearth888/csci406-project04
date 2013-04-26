CFLAGS=-ggdb3 -std=c99

.PHONY: all prepare

all: build build/algowars

annealing: build build/algowars_annealing

build:
	mkdir -p build

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/algowars: build/main.o build/data_loader.o build/magic.o
	$(CC) $(CFLAGS) $^ -o $@

build/algowars_annealing: build/main.o build/data_loader.o build/magic_annealing.o
	$(CC) $(CFLAGS) $^ -o $@
