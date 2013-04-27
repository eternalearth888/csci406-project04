#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/** Creates random numbers for machines and tasks for testing**/

static const int taskMax = 1000;
static const int machineMax = 50;
static const int speedMax = 20;
static const int timeMax = 10000;

int main() {

srand(time(NULL));

int taskNum = rand() % taskMax + 1;
int machineNum = rand() % machineMax + 1;

printf("%i\n%i\n", taskNum, machineNum);

for (int i = 0; i < taskNum; i++) {
	printf("%i ", rand() % timeMax + 1);
}

printf("\n");

for (int i = 0; i < machineNum; i++) {
	printf("%i ", rand() % speedMax + 1);
}

printf("\n");

}