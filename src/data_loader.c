#include <stdio.h>
#include <stdlib.h>

#define REQUIRE(x) { if (!x) { fprintf(stderr, "Failed to load data"); exit(2); } } 

void loadData(FILE *input, int *taskSize, int **tasks, int *machineSize, int **machines) {
	REQUIRE(fscanf(input, "%d\n", taskSize));
	REQUIRE(fscanf(input, "%d\n", machineSize));

	*tasks = calloc(sizeof(int), *taskSize);
	*machines = calloc(sizeof(int), *machineSize);

	for (int i = 0; i < *taskSize; i++) {
		REQUIRE(fscanf(input, "%d", *tasks + i));
	}

	for (int i = 0; i < *machineSize; i++) {
		REQUIRE(fscanf(input, "%d", *machines + i));
	}
 }
