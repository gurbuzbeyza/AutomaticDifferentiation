class ValDer:

	def __init__(self,val,der=0):
		self.val = val
		self.der = der
	
	def print_(self):
		print "[ "+str(self.val)+" , "+str(self.der)+" ]"



def class_(x):
	return x.__class__.__name__

def prod_(x,y):
	v = ValDer(0,0)
	if class_(x)=='ValDer' and class_(y)=='ValDer':
		print "ERROR: apply chain rule first!!!"
	elif class_(x)=='ValDer':	#y scalar
		v.val = x.val*y
		v.der = y
	elif class_(y)=='ValDer':	#x scalar
		v.val = x*y.val
		v.der = x
	else:	#both scalar
		v.val = x*y
		v.der = 0
	return v

def main():
	x = ValDer(2,1)
	y = 3
	res = prod_(y,x)
	res.print_()
main()


#References
#http://epubs.siam.org/doi/pdf/10.1137/080743627
#http://www.columbia.edu/~ahd2125/post/2015/12/5/