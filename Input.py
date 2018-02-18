from enum import Enum
from math import *
import numpy as np

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
				variables.append([l[0],NO_OPERATION,l[2:]])	#[varName, operName, [variables]]
	i = input_vals[0].split()
	n = len(i)
	for x in i:
		inputs.vars.append(x)

	input_vals.pop(0)
	for i in input_vals:
		i = i.split()
		inputs.value_list.append(i)
	return variables, inputs, output

# def choose_operation(op, v):
#     return {
#         Operation.Mult: exec (v[0] + ' = ' + v[2][0] + ' * ' + v[2][1]),
#         Operation.Sin: exec (v[0] + ' = ' + 'sin(' + v[2][1] + ')'),
#         Operation.Cos: exec (v[0] + ' = ' + 'cos(' + v[2][1] + ')'),
#         Operation.Log: exec (v[0] + ' = ' + 'log(' + v[2][1] + ')')
#     }[op]

def isScalar(n):
	try:
		float(n)
		return True
	except ValueError:
		return False

def __main__():
	variables, inputs, output = take_input()
	print(variables)
	print(inputs)
	print(output)
	#jacobian = [][]
	jacobian = []
	val_ders = []	#list of: ['var_name','value',[['derivativeToX',val],'derivativeToY',val],...]] #leafs #forwardPass

	for i in inputs.value_list:
		for j in range(len(inputs.vars)):
			exec (inputs.vars[j] + ' = ' + i[j])
			print (inputs.vars[j])
			exec ('print (' + inputs.vars[j] + ')')
		for v in variables:
			valder = [0,0,[]]#placeholder	#['var_name','value','derivative']
			#!!note:!! execs below might be insufficient execute more(? :D) if errors occur

			if v[1] == Operation.Mult:
				valder[0]=v[0]
				valder[1]=eval(v[2][0] + ' * ' + v[2][1]);
				exec (v[0] + ' = ' + v[2][0] + ' * ' + v[2][1])	#exec valder[0] = valder[1]
				if not isScalar(v[2][0]) and not isScalar(v[2][1]):
					valder[2].append([v[2][0],eval(v[2][1])])
					valder[2].append([v[2][1],eval(v[2][0])])
				elif not isScalar(v[2][0]):
					valder[2].append([v[2][0],eval(v[2][1])])
				elif not isScalar(v[2][1]):
					valder[2].append([v[2][1],eval(v[2][0])])
				else:	#not expected
					print("multiplication of 2 scalars given! should i handle it?")
			elif v[1] == Operation.Sin:
				valder[0]=v[0]
				valder[1] = eval('sin(' + v[2][0] + ')')
				exec (v[0] + ' = ' + 'sin(' + v[2][0] + ')')	#exec valder[0] = valder[1] i.e. t_1 = sin(t_0)
				valder[2].append([v[2][0],eval('cos(' + v[2][0] + ')')])
			elif v[1] == Operation.Cos:
				valder[0]=v[0]
				valder[1] = eval('cos(' + v[2][0] + ')')
				exec (v[0] + ' = ' + 'cos(' + v[2][0] + ')')	#exec valder[0] = valder[1] 
				valder[2].append([v[2][0],eval('-sin(' + v[2][0] + ')')])
			elif v[1] ==NO_OPERATION:
				valder[0] = v[0]
				valder[1] = eval(v[2][0])
				valder[2].append([v[2][0],1])
				exec (v[0] + ' = ' + v[2][0])
			else:
				print("i see operations you did not handle!! like: "+v[1])
			val_ders.append(valder)
			# choose_operation(v[1], v)
			print (v[0])
			exec ('print (' + v[0] + ')')


		print("val_ders:")
		for i in val_ders:
			print(i)
		val_ders=[]

__main__()