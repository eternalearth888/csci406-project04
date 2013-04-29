#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

/**
 * Simple, undershooting division of tasks in given order
 * This gives a start state that divides the tasks roughly evenly, which if not optimal shouldn't be
 * bad
 * */
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

		// Give time to next machine to allocate
		underShoot = to_allocate - allocated;
	}

	if (underShoot) state[taskId] = machineId - 1;
}

/**
 * Get a slight variation of the current state, by assigning one of the tasks to a different machine
 */
static void getNeighbor(int8_t *neighbor, int8_t* state, int taskSize, int machineSize) {
	// Loop until we make an actual change
	memcpy(neighbor, state, taskSize);
	size_t i;
	int8_t orig;
	do {
		i = rand() % taskSize;
		orig = neighbor[i];
		neighbor[i] = rand() % machineSize;
	} while (neighbor[i] == orig && machineSize != 1);
}

/**
 * Get the cost of the given state, computed by the maximum time spent by any given machine working
 * on its assigned tasks
 */
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

/**
 * Find the probability that the algorithm will switch to the neighbor state.
 * This is automatically 1 if the neighbor is a better solution. Otherwise, it starts and 1 and
 * increases proportional to on the current temperature, and decreases proportional to the
 * difference between the neighbor's cost and the current state's cost.
 */
static float switchProbability(float temp, float curCost, float neighborCost) {
	if (curCost > neighborCost) {
		return 1;
	} else {
		return expf(-(neighborCost - curCost) / temp);
	}
}

/**
 * Simple linear decrease from 50 at start to 0 at end.
 */
static float temperature(int round, int roundMax) {
	return 50 * (1 - round / (float) roundMax);
}

int** computeTime(int* tasks, int* machines, int taskSize, int machineSize, int precision) {
	// All states are stored as arrays of 8-bit integers, giving the machine ID that each task is
	// assigned to, in order.
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

	int roundMax = (int) (log(taskSize * machineSize) * precision / log(1.1));

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

	// Simple, slow but one-time transformation to expected result format
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
