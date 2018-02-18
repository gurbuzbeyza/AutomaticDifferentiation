from enum import Enum

NO_OPERATION = 'no operation'

class Operation(Enum):
	Mult = 'mult'
	Sin = 'sin'
	Cos = 'cos'
	Log = 'log'
	#add...

class Input:
	vars = []
	value_list = []

	def __init__(self):
		pass

def take_input():
	with open('function_def.txt') as f:
	    funct_def = f.readlines()

	with open('input_vals.txt') as f:
	    input_vals = f.readlines()

	operations = [item.value for item in Operation]
	inputs = Input()
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
				variables.append([l[0],NO_OPERATION,l[3:]])	#[varName, operName, [variables]]
	i = input_vals[0].split()
	n = len(i)
	for x in i:
		inputs.vars.append(x)

	input_vals.pop(0)
	for i in input_vals:
		i = i.split()
		inputs.value_list.append(i)
	return variables, inputs, output

def __main__():
	variables, inputs, output = take_input()
	print(variables)
	print(inputs)
	print(output)

	for i in inputs.value_list:
		for j in range(len(inputs.vars)):
			exec (inputs.vars[j] + ' = ' + i[j])
			print (inputs.vars[j])
			exec ('print (' + inputs.vars[j] + ')')
			for v in variables

__main__()