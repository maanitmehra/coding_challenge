import numpy as np
import math
import csv
univ = []

def create_mat(size):
	mat = np.random.random((size,size))
	for i in range(0,len(mat)):
		for j in range(0,len(mat)):
			if i==j:
				mat[i][j]=-np.inf
			elif i<j:
				if mat[i][j]<0.5:
					mat[i][j]=0
				else:
					mat[i][j]=1
				mat[j][i]=mat[i][j]
	return mat

def scan_list(list, item):
	indices=[]
	for i in range(0,len(list)):
		if list[i]==item:
			indices.append(i)
	return indices 


def find_link(depth, req, mat, first, last):
	## depth --> Depth number
	## req   --> Required Relation
	## mat   --> Relationship Matrix

	if depth == len(req)-1:
		ind = scan_list(mat[first], int(req[depth]))
		if last in ind:
			if mat[first][last] == int (req[depth]):
				status = True
				univ.append(last)
			else:
				status = False
		else:
			status = False
		return status
	else:
		ind = scan_list(mat[first], int (req[depth]))
		for i in ind:
			stat = find_link(depth+1, req, mat, i, last)		
			if stat == True:
				univ.append(i)
				return True
			else:
				return False	


def main ():
	global univ

	## creating a matrix
	mat = create_mat(5)
	print mat

	## Required Relations
	req="10101"

	##source & dest
	source_ind = 0
	dest_ind=2

	## find path from source to dest
	find_link(0, req, mat, 0, 2)	

	## display results
	print req
	univ.append(source_ind)
	print univ[::-1]
	
main()
import time
start =3 
end =100
times=[]
x=[]
## Testing for size of mat
for n in range(start,end):
	x.append(n)
	mat=create_mat(n)
	## Required Relations
        req="10101"

        ##source & dest
        source_ind = 0
        dest_ind=2


	t=time.time()	
        ## find path from source to dest
        find_link(0, req, mat, 0, 2)
	times.append(time.time()-t)


try:
	file = open ('Results.csv', 'w')
except:
	file = open ('Results.csv', 'r+')

writer = csv.DictWriter(file, fieldnames=["N","Time"], delimiter=",", lineterminator="\n")

for i in range(start,end):
	writer.writerow({"N":i ,"Time":times[i-start]})
	#file.write((i, times[i]))

file.close()

import matplotlib as mpl
mpl.use('agg')
import matplotlib.pyplot as plt
mpl.rcParams['savefig.dpi'] = 100

plt.clf()
plt.plot(x, times, 'r*-')

plt.xlabel('# elements in matrix A')
plt.ylabel('$Time$')
plt.title('Time v/s N')
plt.legend('O(n^2)', loc='upper west')
plt.grid(True)
#plt.draw()
plt.savefig('Results.png')

