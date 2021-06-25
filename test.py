import numpy as np


l = [0,8,16,24,32,40,48,56]
p = []
for x in range(8):
	for i in l:
		p.append((x,i))
p = p[:-4]
print(np.array(p).reshape(5,12,2).tolist())