import numpy as np
import struct
from utils import G

sigma = [
   [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
   [14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3],
   [11, 8, 12, 0, 5, 2, 15, 13, 10, 14, 3, 6, 7, 1, 9, 4],
   [7, 9, 3, 1, 13, 12, 11, 14, 2, 6, 5, 10, 4, 0, 15, 8],
   [9, 0, 5, 7, 2, 4, 10, 15, 14, 1, 11, 12, 6, 8, 3, 13],
   [2, 12, 6, 10, 0, 11, 8, 3, 4, 13, 7, 5, 15, 14, 1, 9],
   [12, 5, 1, 15, 14, 13, 4, 10, 0, 7, 6, 3, 9, 2, 8, 11],
   [13, 11, 7, 14, 12, 1, 3, 9, 5, 0, 15, 4, 8, 6, 2, 10],
   [6, 15, 14, 9, 11, 3, 0, 8, 12, 2, 13, 7, 1, 4, 10, 5],
   [10, 2, 8, 4, 7, 6, 1, 5, 15, 11, 9, 14, 3, 12, 13, 0],
   [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
   [14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3]
]

iv = \
[
    0x6A09E667F3BCC908, 0xBB67AE8584CAA73B, 0x3C6EF372FE94F82B, 0xA54FF53A5F1D36F1,
    0x510E527FADE682D1, 0x9B05688C2B3E6C1F, 0x1F83D9ABFB41BD6B, 0x5BE0CD19137E2179
]
sigma = np.array(sigma,dtype=np.uint8)

class context_obj(object):

	def __init__(self):
		self.h = np.zeros(8,dtype=np.uint64)
		self.totalSize = [0,0]
		self.size = 0
		self.buffer = np.zeros(128,dtype=np.uint8)

def init(context,key,keyLen,digestLen):
	l = iv.copy()
	l[0]=l[0]^digestLen^0x01010000
	context.h[:] = l
	print(context.h)
	# context.h[0]=(context.h[0]^digestLen^0x01010000)

def update(context,data,length):
	
	while(length>0):
		if(context.size==128):
			blake2bProcessBlock(context)
			context.size = 0

		n = min(length, 128-context.size)
		# print(n)
		context.buffer[context.size:n+context.size] = data[:n]
		context.size+=n

		data = data[n:]
		length-=n
	if(context.size==128):
		blake2bProcessBlock(context)
		context.size = 0

def blake2bProcessBlock(context,last=False):
	v = np.zeros(16,dtype=np.uint64)
	v[:8] = context.h
	v[8:16] = iv

	context.totalSize[0]+=context.size

	if(context.totalSize[0]<context.size):
		context.totalSize[1]+=1

	v[12]^=np.array([context.totalSize[0]],dtype=np.uint64)#context.totalSize[0]
	v[13]^=np.array([context.totalSize[1]],dtype=np.uint64)#context.totalSize[1]

	if(last):
		v[14] = ~v[14]


	# m = context.m
	m = struct.unpack_from('<16%s' % 'Q', bytes(context.buffer))	

	for i in range(12):
		G(v,0, 4, 8,  12, m[sigma[i][0]], m[sigma[i][1]]);
		G(v,1, 5, 9,  13, m[sigma[i][2]], m[sigma[i][3]]);
		G(v,2, 6, 10, 14, m[sigma[i][4]], m[sigma[i][5]]);
		G(v,3, 7, 11, 15, m[sigma[i][6]], m[sigma[i][7]]);

		G(v,0, 5, 10, 15, m[sigma[i][8]],  m[sigma[i][9]]);
		G(v,1, 6, 11, 12, m[sigma[i][10]], m[sigma[i][11]]);
		G(v,2, 7, 8,  13, m[sigma[i][12]], m[sigma[i][13]]);
		G(v,3, 4, 9,  14, m[sigma[i][14]], m[sigma[i][15]]);
	print("done")

	
	for i in range(8):
		context.h^=v[i]^v[i+8]

cntx = context_obj()
data = np.array([1]*128, dtype=np.uint8)
length=len(data)
init(cntx, 0, 0, 64)
update(cntx, data, length)
# blake2bProcessBlock
print(cntx.h)