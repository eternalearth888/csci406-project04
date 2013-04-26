#include <stdio.h> 
#include <stdlib.h>

/*
// # % -- ; main
*/

//return the time after adding taskTime to currentTasks at machineSpeed
float timeAfterTask(int* currentTasks, int machineSpeed, int* tasks, int taskId) {
	int amount = 0;
	int numTasksAssigned = 0;
	for (numTasksAssigned; currentTasks[numTasksAssigned] != -1; numTasksAssigned++) {
	}
	// now we have number of tasks currently assigned, ie the next task goes into index of numTasksAssigned
	for (int i = 0; i < numTasksAssigned; i++) {
		amount += tasks[currentTasks[i]];
	}
	amount += tasks[taskId];


	return (float)(amount/machineSpeed);
}
//will append the task to the array of assigned tasks
void appendToMachine(int* currentTasks, int tasksID) {
	int numTasksAssigned = 0;
	for (numTasksAssigned; currentTasks[numTasksAssigned] != -1; numTasksAssigned++) {
	}
	currentTasks[numTasksAssigned] = tasksID;
}

int** computeTime(int* tasks, int* machines, int taskSize, int machineSize) {
	float currentWorstTime = 0; // the amount of time it takes to finish the task assigned to their respective machines

	int **machinesTasks = malloc(machineSize * sizeof(int*));
	for (int i = 0; i < machineSize; i++){
		machinesTasks[i] = malloc(taskSize * sizeof(int));
	}
	//int machinesTasks[machineSize][taskSize]; // each index corresponds to a machine, and the array it cotains is the tasks assigned to that machine
	for (int i = 0; i < machineSize; i++) {
		for (int j = 0; j < taskSize; j++) {
			machinesTasks[i][j] = -1;
		}
	}	

	for (int i = 0; i < taskSize; i++) {
		int hasAssigned = 0; //bool for checking if we have assigned a task
		printf("Task %i has the time %i\n", i, tasks[i]);
		for (int j = 0; j < machineSize; j++) {
			printf("At machine %i\n", j); 
			if (timeAfterTask(machinesTasks[j], machines[j], tasks, i) <= currentWorstTime && hasAssigned == 0) {
				printf("No increase, assigned Task %i to machine %i\n", i, j);
				appendToMachine(machinesTasks[j], i);
				hasAssigned = 1;
			}
		}
		if (hasAssigned == 0) { // in the case that the task could not be assinged to any machine without increasing the currentWorstTime
				float lowestIncrease = 999999999999999; // A large number
				int lowestMachine = 0;
				for (int j = 0; j < machineSize; j++) {
					if ((currentWorstTime - timeAfterTask(machinesTasks[j], machines[j], tasks, i)) < lowestIncrease) {
						lowestIncrease = currentWorstTime - timeAfterTask(machinesTasks[j], machines[j], tasks, i);
						lowestMachine = j;
					}
				}
			printf("Increase occured, assigned Task %i, to machine %i\n", i, lowestMachine);
			printf("CurrentWorstTime is currently %f", currentWorstTime);
		    currentWorstTime = currentWorstTime + timeAfterTask(machinesTasks[lowestMachine], machines[lowestMachine], tasks, i);
		    printf("  CurrentWorstTime is now %f\n", currentWorstTime);
			appendToMachine(machinesTasks[lowestMachine], i);
		}
	}

	int** barryManillow = machinesTasks;

	return barryManillow;
}