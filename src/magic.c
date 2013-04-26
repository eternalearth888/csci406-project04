#include <stdio.h> 
#include <stdlib.h>
//return the time after adding taskTime to currentTasks at machineSpeed
float timeAfterTask (int *currentTasks, int machineSpeed, int taskTime);

//will append the task to the array of assigned tasks
void appendToMachine (int *currentTasks, int task);

float computeTime (int *tasks, int *machines, int taskSize, int machineSize); 

/*
// # % -- ; main
*/


float timeAfterTask(int* currentTasks, int machineSpeed, int taskTime) {
	int amount = 0;
	int numTasksAssigned = 0;
	for (numTasksAssigned; currentTasks[numTasksAssigned] != -1; numTasksAssigned++) {
	}
	// now we have number of tasks currently assigned, ie the next task goes into index of numTasksAssigned
	for (int i = 0; i < numTasksAssigned; i++) {
		amount += currentTasks[i];
	}
	amount += taskTime;


	return (float)(amount/machineSpeed);
}

void appendToMachine(int* currentTasks, int task) {
	int numTasksAssigned = 0;
	for (numTasksAssigned; currentTasks[numTasksAssigned] != -1; numTasksAssigned++) {
	}
	currentTasks[numTasksAssigned] = task;
}

float computeTime(int* tasks, int* machines, int taskSize, int machineSize) {
	float currentWorstTime = 0; // the amount of time it takes to finish the task assigned to their respective machines

	int machinesTasks[machineSize][taskSize]; // each index corresponds to a machine, and the array it cotains is the tasks assigned to that machine
	for (int i = 0; i < machineSize; i++) {
		for (int j = 0; j < taskSize; j++) {
			machinesTasks[i][j] = -1;
		}
	}	

	for (int i = 0; i < taskSize; i++) {
		int hasAssigned = 0; //bool for checking if we have assigned a task
		for (int j = 0; j < machineSize; j++) {
			if (timeAfterTask(machinesTasks[j], machines[j], tasks[i]) <= currentWorstTime && hasAssigned == 0) {
				appendToMachine(machinesTasks[j], tasks[i]);
				hasAssigned = 1;
			}
		}
		if (hasAssigned == 0) { // in the case that the task could not be assinged to any machine without increasing the currentWorstTime
				float lowestIncrease = 999999999999999; // A large number
				int lowestMachine = 0;
				for (int j = 0; j < machineSize; j++) {
					if (timeAfterTask(machinesTasks[j], machines[j], tasks[i]) < lowestIncrease) {
						lowestIncrease = timeAfterTask(machinesTasks[j], machines[j], tasks[i]);
						lowestMachine = j;
					}
				}
		    currentWorstTime = currentWorstTime + timeAfterTask(machinesTasks[lowestMachine], machines[lowestMachine], tasks[i]);
			appendToMachine(machinesTasks[lowestMachine], tasks[i]);
		}
	}

	float barryManillow = currentWorstTime;

	return barryManillow;
}