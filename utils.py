import numpy as np
def ROR64(a,n):
	n =np.array([n],dtype=np.uint64)
	return (((a) >> (n)) | ((a) << (64 - (n))))

def G(v,a,b,c,d,x,y):
	v[a]+=v[b]+np.array([x],dtype=np.uint64)
	v[d] = ROR64(v[d], 32)
	v[c] += v[d] 
	v[b] ^= v[c]
	v[b] = ROR64(v[b], 24)
	v[a] += v[b] + np.array([y],dtype=np.uint64)
	v[d] ^= v[a]
	v[d] = ROR64(v[d], 16)
	v[c] += v[d]
	v[b] ^= v[c]
	v[b] = ROR64(v[b], 63)