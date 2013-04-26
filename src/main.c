#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "data_loader.h"
#include "magic.h"

int main(int argc, char **argv) {
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [FILENAME]\n", argv[0]);
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

	printf("%d tasks:\n", taskSize);

	for (int i = 0; i < taskSize; i++) {
		printf("  %d\n", tasks[i]);
	}
	
	printf("\n%d machines:\n", machineSize);

	for (int i = 0; i < machineSize; i++) {
		printf("  %d\n", machines[i]);
	}

	int **machineTasks = computeTime(tasks, machines, taskSize, machineSize);

	puts("\nTask assignments:\n");

	for (int i = 0; i < machineSize; i++) {
		printf("  Machine %d:", i + 1);

		for (int j = 0; machineTasks[i][j]; j++) {
			printf(" %d", machineTasks[i][j] + 1);
		}

		puts("\n");
	}
}
