#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_loader.h"
#include "magic.h"

int main(int argc, char **argv) {
	int precision = 100;
	char *progname = argv[0];
	bool verbose = false;

	if (argc >= 2 && strcmp(argv[1], "-v") == 0) {
		verbose = true;
		argc--;
		argv++;
	}

	if (argc >= 2 && atoi(argv[1])) {
		precision = atoi(argv[1]);
		argc--;
		argv++;
	}

	if (argc > 2) {
		fprintf(stderr, "Usage: %s [PRECISION] [FILENAME]\n", progname);
		return 1;
	}

	FILE *input = stdin;

	if (argc == 2) {
		input = fopen(argv[1], "rb");

		if (!input) {
			fprintf(stderr, "algowars: cannot access %s: %s\n", argv[1], strerror(errno));
			return 1;
		}
	}

	int taskSize, machineSize;
	int *tasks, *machines;

	loadData(input, &taskSize, &tasks, &machineSize, &machines);

	if (verbose) {
		printf("%d tasks:\n", taskSize);

		for (int i = 0; i < taskSize; i++) {
			printf("  %d\n", tasks[i]);
		}
		
		printf("\n%d machines:\n", machineSize);

		for (int i = 0; i < machineSize; i++) {
			printf("  %d\n", machines[i]);
		}
	}

	int **machineTasks = computeTime(tasks, machines, taskSize, machineSize, precision);

	if (verbose) printf("\nTask assignments:\n");

	float maxCost = 0;

	for (int i = 0; i < machineSize; i++) {
		if (verbose) printf("  Machine %d has tasks: ", i + 1);

		float machineCost = 0;

		for (int j = 0; j < taskSize && machineTasks[i][j] != -1; j++) {
			machineCost += tasks[machineTasks[i][j]];
			printf("%s%d", (j ? " " : ""), machineTasks[i][j] + 1);
		}

		machineCost /= machines[i];
		if (machineCost > maxCost) maxCost = machineCost;

		printf("\n");
	}

	if (verbose) printf("Maximum cost: ");

	printf("%g\n", maxCost);

	return 0;
}
