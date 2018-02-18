def add_diff(constant, val):
	return val

def subt_diff(constant, val):
	return '-' + val

def mult_diff(constant, val):
	return constant

def sin_diff(val):
	return 'cos(' + val + ')'

def cos_diff(val):
	return '-sin(' + val + ')'

def direct_diff(val):
	return 1

t0_x1 = mult_diff(2, 'x1')
t1_t0 = sin_diff('t0')
t2_x1 = mult_diff('x2', 'x1')
t2_x2 = mult_diff('x1', 'x2')
t3_t2 = cos_diff('t2')
t4_t1 = mult_diff('t3', 't1')
t4_t3 = mult_diff('t1', 't3')
f_t4 = direct_diff('t4')

print(str(f_t4) + ' ' + str(t4_t3) + ' ' + str(t4_t1) + ' ' + str(t3_t2))