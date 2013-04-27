#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simple, undershooting division of tasks in given order
static void getStart(int8_t *state, int* tasks, int* machines, int taskSize, int machineSize) {
	int remainingTime = 0;
	for (int i = 0; i < taskSize; i++) remainingTime += tasks[i];

	int totalSpeed = 0;
	for (int i = 0; i < machineSize; i++) totalSpeed += machines[i];

	int underShoot = 0;
	int taskId = 0;
	int machineId = 0;
	for (; machineId < machineSize; machineId++) {
		int allocated = 0;
		int to_allocate = remainingTime * machines[machineId] / totalSpeed + underShoot;

		while (taskId < taskSize && allocated + tasks[taskId] < to_allocate) {
			allocated += tasks[taskId];
			state[taskId] = machineId;
			taskId++;
		}

		underShoot = to_allocate - allocated;
	}

	if (underShoot) state[taskId] = machineId - 1;
}

static void getNeighbor(int8_t *neighbor, int8_t* state, int taskSize, int machineSize) {
	// Loop until we make an actual change
	memcpy(neighbor, state, taskSize);
	size_t i;
	int8_t orig;
	do {
		i = rand() % taskSize;
		orig = neighbor[i];
		neighbor[i] = rand() % machineSize;
	} while (neighbor[i] == orig);
}

static float cost(int8_t *state, int* tasks, int* machines, int taskSize, int machineSize) {
	float machineCosts[machineSize];
	for (int i = 0; i < machineSize; i++) machineCosts[i] = 0;

	for (int i = 0; i < taskSize; i++) {
		machineCosts[state[i]] += tasks[i] / (float) machines[state[i]];
	}

	float maxCost = 0;

	for (int i = 0; i < machineSize; i++) {
		if (machineCosts[i] > maxCost) maxCost = machineCosts[i];
	}

	return maxCost;
}

static float switchProbability(float temp, float curCost, float neighborCost) {
	if (curCost > neighborCost) {
		return 1;
	} else {
		return expf(-(neighborCost - curCost) / temp);
	}
}

static float temperature(int round, int roundMax) {
	return 50 * (1 - round / (float) roundMax);
}

int** computeTime(int* tasks, int* machines, int taskSize, int machineSize) {
	srand(time(NULL));

	int8_t best[taskSize];
	float bestCost = 0;

	int8_t state[taskSize];
	float curCost = 0;

	int8_t neighbor[taskSize];
	float neighborCost = 0;

	// Reasonable start
	getStart(state, tasks, machines, taskSize, machineSize);
	curCost = cost(state, tasks, machines, taskSize, machineSize);
	
	memcpy(best, state, taskSize);
	bestCost = curCost;

	int roundMax = 1000;

	for (int round = 0; round < roundMax; round++) {
		getNeighbor(neighbor, state, taskSize, machineSize);
		neighborCost = cost(neighbor, tasks, machines, taskSize, machineSize);

		if (switchProbability(temperature(round, roundMax), curCost, neighborCost) > rand() / (float) RAND_MAX) {
			memcpy(state, neighbor, taskSize);
			curCost = neighborCost;

			if (curCost < bestCost) {
				bestCost = curCost;
				memcpy(best, state, taskSize);
			}
		}
	}

	// Simple, dumb transformation to expected result format
	int **machinesTasks = malloc(machineSize * sizeof(int*));
	for (int8_t i = 0; i < machineSize; i++) {
		machinesTasks[i] = malloc(taskSize * sizeof(int));

		int end = 0;
		int j = 0;
		for (; j < taskSize; j++) {
			if (best[j] == i) machinesTasks[i][end++] = j;
		}
		if (end < taskSize) machinesTasks[i][end] = -1;
	}	

	return machinesTasks;
}
