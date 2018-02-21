from enum import Enum
from mpmath import *
import numpy as np

jacobian = []
vds = {}

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

def choose_operation(op, v, vd):
	if v.operation == Operation.Mult:
		mult_valder(vd, v.dependent_vars[0], v.dependent_vars[1])
	elif v.operation == Operation.Sin:
		sin_valder(vd, v.dependent_vars[0])
	elif v.operation == Operation.Cos:
		cos_valder(vd, v.dependent_vars[0])
	elif v.operation == Operation.Log:
		log_valder(vd, v.dependent_vars[0])
	elif v.operation == Operation.Div:
		div_valder(vd, v.dependent_vars[0], v.dependent_vars[1])
	elif v.operation == Operation.Pow:
		pow_valder(vd, v.dependent_vars[0], v.dependent_vars[1])
	elif v.operation == Operation.Tan:
		tan_valder(vd, v.dependent_vars[0])
	elif v.operation == Operation.Cot:
		cot_valder(vd, v.dependent_vars[0])
	elif v.operation == Operation.Exp:
		exp_valder(vd, v.dependent_vars[0])
	elif v.operation == Operation.NoOp:
		noop_valder(vd, v.dependent_vars[0])
	else:
		print("i see operations you did not handle!! like: "+str(v.operation))
   

def mult_valder(vd, x1, x2):
	if not isScalar(x1) and not isScalar(x2):
		vd.val = vds[x1].val * vds[x2].val
		vd.der.append((x1,vds[x2].val))
		vd.der.append((x2,vds[x1].val))
	elif not isScalar(x1):
		vd.val = vds[x1].val * float(x2)
		vd.der.append((x1,float(x2)))
	elif not isScalar(x2):
		vd.val = float(x1) * vds[x2].val
		vd.der.append((x2,float(x1)))
	else:	#not expected
		print("multiplication of 2 scalars given! should i handle it?")

def sin_valder(vd, x):
	vd.val = sin(vds[x].val)
	vd.der.append((x,cos(vds[x].val)))

def cos_valder(vd, x):
	vd.val = cos(vds[x].val)
	vd.der.append((x,-sin(vds[x].val)))

def log_valder(vd, x):
	vd.val = log(vds[x].val)
	vd.der.append((x,1/(vds[x].val)))

def div_valder(vd, x1, x2):
	if not isScalar(x1) and not isScalar(x2):
		vd.val = vds[x1].val / vds[x2].val
		vd.der.append((x1,1/vds[x2].val))
		vd.der.append((x2,(-vds[x1].val)/vds[x2].val**2))
	elif not isScalar(x1):
		vd.val = vds[x1].val / float(x2)
		vd.der.append((x1,1/float(x2)))
	elif not isScalar(x2):
		vd.val = float(x1) * vds[x2].val
		vd.der.append((x2,(-float(x1))/vds[x2].val**2))
	else:	#not expected
		print("division of 2 scalars given! should i handle it?")

def pow_valder(vd, x1, x2):
	if not isScalar(x1) and not isScalar(x2):
		vd.val = vds[x1].val ** vds[x2].val
		vd.der.append((x1,vds[x2].val*(vds[x1].val**(vds[x2].val-1))))
		vd.der.append((x2,(vds[x1].val**vds[x2].val)*log(vds[x1].val)))
	elif not isScalar(x1):
		vd.val = vds[x1].val ** float(x2)
		vd.der.append((x1,float(x2)*(vds[x1].val**float(x2-1))))
	elif not isScalar(x2):
		vd.val = float(x1) ** vds[x2].val
		vd.der.append((x2,(float(x1) ** vds[x2].val)*log(float(x1))))
	else:	#not expected
		print("division of 2 scalars given! should i handle it?")

def tan_valder(vd, x):
	vd.val = tan(vds[x].val)
	vd.der.append((x,1/((cos(vds[x].val))**2)))

def cot_valder(vd, x):
	vd.val = cot(vds[x].val)
	vd.der.append((x,-1/((sin(vds[x].val))**2)))

def exp_valder(vd, x):
	vd.val = e**(vds[x].val)
	vd.der.append((x,e**(vds[x].val)))

def noop_valder(vd, x):
	vd.val = vds[x].val
	vd.der.append((x,1))

def solve_lin_eq():
	global vds
	vdslen = len(vds)
	jacobian = np.zeros((vdslen, vdslen)) - np.identity(vdslen)

	vd_list = list(vds.values())
	for v in vd_list:
		for i in v.der:
			jacobian[vd_list.index(vds[i[0]])][vd_list.index(v)] = i[1]

	# print(str(jacobian))

	y = np.zeros(vdslen)

	y[vdslen - 1] = -1

	x = np.linalg.solve(jacobian, y)

	return x


def isScalar(n):
	try:
		float(n)
		return True
	except ValueError:
		return False

def __main__():
	global vds
	variables, inputs, output = take_input()
	# print(variables)
	# print(inputs)
	# print(output)
	for i in inputs.value_list:
		for j in range(len(inputs.vars)):
			vd = Valder(inputs.vars[j])
			vd.val = float(i[j])
			vd.der.append((inputs.vars[j], -1))
			vds[inputs.vars[j]] = vd
		for v in variables:
			#!!note:!! execs below might be insufficient execute more(? :D) if errors occur
			vd = Valder(v.name)
			choose_operation(v.operation, v, vd)
			vds[v.name] = vd

		# for key, value in vds.items():
		# 	print (key + ' ' + str(value.val) + ' ' + str(value.der) + '\n')
		x = solve_lin_eq()

		for j in range(len(inputs.vars)):
			print(inputs.vars[j] + ': ' + str(x[j]))

		vds = {}


__main__()