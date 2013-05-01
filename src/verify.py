import sys
inputFile = open(sys.argv[1], "r")
text = inputFile.readlines();
inputFile.close();
tasksAssigned = []
machineSpeeds = [1, 2, 1]
taskTimes = [10, 10, 10, 10, 10, 10]
for i in range(0, len(text)-1):
	derp = []
	splitText = text[i].split()
	for number in splitText:
		if number != " "and number != "\n":
			derp.append(int(number))
	tasksAssigned.append(derp)
givenCost = float(text[len(text)-1].split()[0])
currentCost = 0
for machine in range(0, len(tasksAssigned)):
	machineTime = 0
	for task in tasksAssigned[machine]:
		machineTime += (float(taskTimes[task])/machineSpeeds[machine])
	currentCost += machineTime

if currentCost != givenCost:
	print "\nNOT VALID\n"
else:
	print "\nVALID\n"
