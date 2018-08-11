from random import randint
f = open('pages.in','w')
from random import randint
n = randint(20,100)
f.write(str(n))
f.write("\n")
for i in xrange(n):
	temp = randint(1, 10)
	f.write(str(temp)+" ")