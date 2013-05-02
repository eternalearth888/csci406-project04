import sys
"""
if given an output in the format in the pdf, will compare the
results and print valid if valid and not valid if it is not valid
Our input file is hardcoded in 

takes file to test against as a system argument. 

"""
inputFile = open(sys.argv[1], "r")#get file
text = inputFile.readlines(); # get the lines
inputFile.close(); #close the file
tasksAssigned = [] #the array where each index is a machine and each machine has a list of task indexs
machineSpeeds = [1, 1, 1, 1, 1, 1, 1 ,1 ,1, 1] # our hardcoded input
taskTimes = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,2 ,2, 2] #our hardcoded input
for i in range(0, len(text)-1):#for each machine
	derp = [] # array of assigned tasks for each machine
	splitText = text[i].split() # split by whitespace
	for number in splitText: #for each task
		if number != " "and number != "\n":#check for whitespace and newline
			derp.append(int(number)) #add the task to the machines assigned 
	tasksAssigned.append(derp)  #add the array of tasks to machine
givenCost = float(text[len(text)-1].split()[0]) # get the cost the other group said they got
maxCost = 0 #intilize 0
#get the cost with the tasks assigned to the respective machine
for machine in range(0, len(tasksAssigned)):
	machineTime = 0 #assume machine has 0
	for task in tasksAssigned[machine]:
		machineTime += (float(taskTimes[task])/machineSpeeds[machine]) # add the time it takes to run the task on that machine
	if maxCost < machineTime: #if that machine takes longer than the current max
		maxCost = machineTime #make it the max

if maxCost != givenCost: # if their cost is not equal to the cost calculated above
	print "\nNOT VALID\n" #its not valid
else:
	print "\nVALID\n" #otherwise it is
