from enum import Enum

class Operation(Enum):
	Mult = 'mult'
	Sin = 'sin'
	Cos = 'cos'
	Log = 'log'
	#add...

with open('function_def.txt') as f:
    funct_def = f.readlines()

with open('input_vals.txt') as f:
    input_vals = f.readlines()

operations = [item.value for item in Operation]
noOperation = 'no operation'
inputs = []
output = ""
variables = []
for l in funct_def:	#assumed 1 output per function
	l = l.split()
	if l[0] == "input":
		pass #given on inputs file not necessary here
	elif l[0] == "output":
		output = l[1]
	else:
		if(l[2] in operations):
			variables.append([l[0],Operation(l[2]),l[3:]])	#[varName, operName, [variables]]
		else:
			variables.append([l[0],noOperation,l[3:]])	#[varName, operName, [variables]]
i = input_vals[0].split()
n = len(i)
for x in i:
	inputs.append([x,[]])

input_vals.pop(0)
for i in input_vals:
	i = i.split()
	j = 0
	for x in i:
		inputs[j][1].append(x)
		j=j+1
	
print(variables)
print(inputs)
print(output)