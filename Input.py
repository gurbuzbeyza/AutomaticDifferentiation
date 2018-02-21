from enum import Enum
from mpmath import *
import numpy as np

jacobian = []
valders = {}

class Operation(Enum):
	Mult = 'mult'
	Sin = 'sin'
	Cos = 'cos'
	Log = 'log'
	Add = 'add'
	Subs = 'subs'
	Div = 'div'
	NoOp = 'no_operation'
	Pow = 'pow'
	Tan = 'tan'
	Cot = 'cot'
	Exp = 'exp'
	#add...

class Input:
	vars = []
	value_list = []

	def __init__(self):
		self.vars = []
		self.value_list = []

class Valder:
	name = ''
	val = 0
	der = []

	def __init__(self, name):
		self.name = name
		self.val = 0
		self.der = []

class Variable:
	name = ''
	operation = ''
	dependent_vars = []

	def __init__(self, name, operation, dependent_vars):
		self.name = name
		self.operation = operation
		self.dependent_vars = dependent_vars

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
				variables.append(Variable(l[0], Operation(l[2]), l[3:]))	#[varName, operName, [variables]]
			else:
				variables.append(Variable(l[0], Operation.NoOp, l[2:]))	#[varName, operName, [variables]]
	i = input_vals[0].split()
	n = len(i)
	for x in i:
		inputs.vars.append(x)

	input_vals.pop(0)
	for i in input_vals:
		i = i.split()
		inputs.value_list.append(i)
	return variables, inputs, output

def choose_operation(op, v, valder):
	if v.operation == Operation.Mult:
		mult_valder(valder, v.dependent_vars[0], v.dependent_vars[1])
	elif v.operation == Operation.Sin:
		sin_valder(valder, v.dependent_vars[0])
	elif v.operation == Operation.Cos:
		cos_valder(valder, v.dependent_vars[0])
	elif v.operation == Operation.Log:
		log_valder(valder, v.dependent_vars[0])
	elif v.operation == Operation.Div:
		div_valder(valder, v.dependent_vars[0], v.dependent_vars[1])
	elif v.operation == Operation.Pow:
		pow_valder(valder, v.dependent_vars[0], v.dependent_vars[1])
	elif v.operation == Operation.Tan:
		tan_valder(valder, v.dependent_vars[0])
	elif v.operation == Operation.Cot:
		cot_valder(valder, v.dependent_vars[0])
	elif v.operation == Operation.Exp:
		exp_valder(valder, v.dependent_vars[0])
	elif v.operation == Operation.NoOp:
		noop_valder(valder, v.dependent_vars[0])
	else:
		print("i see operations you did not handle!! like: "+str(v.operation))
   

def mult_valder(valder, x1, x2):
	if not isScalar(x1) and not isScalar(x2):
		valder.val = valders[x1].val * valders[x2].val
		valder.der.append((x1,valders[x2].val))
		valder.der.append((x2,valders[x1].val))
	elif not isScalar(x1):
		valder.val = valders[x1].val * float(x2)
		valder.der.append((x1,float(x2)))
	elif not isScalar(x2):
		valder.val = float(x1) * valders[x2].val
		valder.der.append((x2,float(x1)))
	else:	#not expected
		print("multiplication of 2 scalars given! should i handle it?")

def sin_valder(valder, x):
	valder.val = sin(valders[x].val)
	valder.der.append((x,cos(valders[x].val)))

def cos_valder(valder, x):
	valder.val = cos(valders[x].val)
	valder.der.append((x,-sin(valders[x].val)))

def log_valder(valder, x):
	valder.val = log(valders[x].val)
	valder.der.append((x,1/(valders[x].val)))

def div_valder(valder, x1, x2):
	if not isScalar(x1) and not isScalar(x2):
		valder.val = valders[x1].val / valders[x2].val
		valder.der.append((x1,1/valders[x2].val))
		valder.der.append((x2,(-valders[x1].val)/valders[x2].val**2))
	elif not isScalar(x1):
		valder.val = valders[x1].val / float(x2)
		valder.der.append((x1,1/float(x2)))
	elif not isScalar(x2):
		valder.val = float(x1) * valders[x2].val
		valder.der.append((x2,(-float(x1))/valders[x2].val**2))
	else:	#not expected
		print("division of 2 scalars given! should i handle it?")

def pow_valder(valder, x1, x2):
	if not isScalar(x1) and not isScalar(x2):
		valder.val = valders[x1].val ** valders[x2].val
		valder.der.append((x1,valders[x2].val*(valders[x1].val**(valders[x2].val-1))))
		valder.der.append((x2,(valders[x1].val**valders[x2].val)*log(valders[x1].val)))
	elif not isScalar(x1):
		valder.val = valders[x1].val ** float(x2)
		valder.der.append((x1,float(x2)*(valders[x1].val**float(x2-1))))
	elif not isScalar(x2):
		valder.val = float(x1) ** valders[x2].val
		valder.der.append((x2,(float(x1) ** valders[x2].val)*log(float(x1))))
	else:	#not expected
		print("division of 2 scalars given! should i handle it?")

def tan_valder(valder, x):
	valder.val = tan(valders[x].val)
	valder.der.append((x,1/((cos(valders[x].val))**2)))

def cot_valder(valder, x):
	valder.val = cot(valders[x].val)
	valder.der.append((x,-1/((sin(valders[x].val))**2)))

def exp_valder(valder, x):
	valder.val = e**(valders[x].val)
	valder.der.append((x,e**(valders[x].val)))

def noop_valder(valder, x):
	valder.val = valders[x].val
	valder.der.append((x,1))

def solve_lin_eq():
	global valders
	valderslen = len(valders)
	jacobian = np.zeros((valderslen, valderslen)) - np.identity(valderslen)

	valder_list = list(valders.values())
	for v in valder_list:
		for i in v.der:
			jacobian[valder_list.index(valders[i[0]])][valder_list.index(v)] = i[1]

	# print(str(jacobian))

	y = np.zeros(valderslen)

	y[valderslen - 1] = -1

	x = np.linalg.solve(jacobian, y)

	return x


def isScalar(n):
	try:
		float(n)
		return True
	except ValueError:
		return False

def __main__():
	global valders
	variables, inputs, output = take_input()
	# print(variables)
	# print(inputs)
	# print(output)
	for i in inputs.value_list:
		for j in range(len(inputs.vars)):
			valder = Valder(inputs.vars[j])
			valder.val = float(i[j])
			valder.der.append((inputs.vars[j], -1))
			valders[inputs.vars[j]] = valder
		for v in variables:
			#!!note:!! execs below might be insufficient execute more(? :D) if errors occur
			valder = Valder(v.name)
			choose_operation(v.operation, v, valder)
			valders[v.name] = valder

		# for key, value in valders.items():
		# 	print (key + ' ' + str(value.val) + ' ' + str(value.der) + '\n')
		x = solve_lin_eq()

		for j in range(len(inputs.vars)):
			print(inputs.vars[j] + ': ' + str(x[j]))

		valders = {}


__main__()