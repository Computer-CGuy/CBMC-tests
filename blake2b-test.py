"""Source:https://www.oryx-embedded.com/doc/blake2b_8c_source.html"""

import numpy as np
import struct
from utils import G,sigma,iv


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
	# print(context.h)
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
	
	blake2bProcessBlock(context,True)
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
	print(m)
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
"""
# Missed
 void blake2bFinal(Blake2bContext *context, uint8_t *digest)
 {
    size_t i;
  
    //The last block is padded with zeros to full block size, if required
    for(i = context->size; i < 128; i++)
    {
       context->buffer[i] = 0;
    }
  
    //Compress the last block
    blake2bProcessBlock(context, TRUE);
  
    //Convert from host byte order to big-endian byte order
    for(i = 0; i < 8; i++)
    {
       context->h[i] = htole64(context->h[i]);
    }
  
    //Copy the resulting digest
    if(digest != NULL)
    {
       osMemcpy(digest, context->digest, context->digestSize);
    }
 }
"""

cntx = context_obj()
# number<<8+nonce
# data = np.array([1]*16+[3]+[1], dtype=np.uint32)
print([(1<<8)+3])
data = np.array([1]*16+[(1<<8)+4], dtype=np.uint32)
length=len(data)
init(cntx, 0, 0, 64)
update(cntx, data, length)
# blake2bProcessBlock
# print(cntx.h)



# 4/7