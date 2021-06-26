#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
int startNonce = 0;
int endNonce = 1000;

// u_int8_t arr[12];

// int tot_index = 0;

u_int8_t sigma[12][16] = {
   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
   {14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3},
   {11, 8, 12, 0, 5, 2, 15, 13, 10, 14, 3, 6, 7, 1, 9, 4},
   {7, 9, 3, 1, 13, 12, 11, 14, 2, 6, 5, 10, 4, 0, 15, 8},
   {9, 0, 5, 7, 2, 4, 10, 15, 14, 1, 11, 12, 6, 8, 3, 13},
   {2, 12, 6, 10, 0, 11, 8, 3, 4, 13, 7, 5, 15, 14, 1, 9},
   {12, 5, 1, 15, 14, 13, 4, 10, 0, 7, 6, 3, 9, 2, 8, 11},
   {13, 11, 7, 14, 12, 1, 3, 9, 5, 0, 15, 4, 8, 6, 2, 10},
   {6, 15, 14, 9, 11, 3, 0, 8, 12, 2, 13, 7, 1, 4, 10, 5},
   {10, 2, 8, 4, 7, 6, 1, 5, 15, 11, 9, 14, 3, 12, 13, 0},
   {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
   {14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3}
};

u_int64_t rotr64(u_int64_t w, u_int64_t c)
{
  return (w >> c) | (w << (64 - c));
}
void G(u_int64_t *v,int a,int b,int c,int d,u_int32_t x,u_int32_t y){
	v[a] = v[a] + v[b] + x;
	v[d] = rotr64(v[d] ^ v[a], 32);

	v[c] = v[c] + v[d];
	v[b] = rotr64(v[b] ^ v[c], 24);

	v[a] = v[a] + v[b] + y;
	v[d] = rotr64(v[d] ^ v[a], 16);

	v[c] = v[c] + v[d];
	v[b] = rotr64(v[b] ^ v[c], 63);
}
u_int64_t v[]= \
	{0, 0, 0, 0, 18, 0, 0, 0ull, 7640891576956012808ull, 13503953896175478587ull, \
		4354685564936845355ull, 11912009170470909681ull, 5840696475078001361ull, \
		11170449401992604703ull, 16175846103906665108ull, 6620516959819538809ull};
void processblock(u_int32_t *m,u_int64_t *out){
	
		// (u_int64_t *)&v
	
	for(int i=0;i<12;i++){
		G((u_int64_t *)&v,0, 4, 8,  12, m[sigma[i][0]], m[sigma[i][1]]);
		G((u_int64_t *)&v,1, 5, 9,  13, m[sigma[i][2]], m[sigma[i][3]]);
		G((u_int64_t *)&v,2, 6, 10, 14, m[sigma[i][4]], m[sigma[i][5]]);
		G((u_int64_t *)&v,3, 7, 11, 15, m[sigma[i][6]], m[sigma[i][7]]);

		G((u_int64_t *)&v,0, 5, 10, 15, m[sigma[i][8]],  m[sigma[i][9]]);
		G((u_int64_t *)&v,1, 6, 11, 12, m[sigma[i][10]], m[sigma[i][11]]);
		G((u_int64_t *)&v,2, 7, 8,  13, m[sigma[i][12]], m[sigma[i][13]]);
		G((u_int64_t *)&v,3, 4, 9,  14, m[sigma[i][14]], m[sigma[i][15]]);
	}
	
	for (int i = 0; i < 8; i++){
		out[i]=v[i]^v[i+8];
	}
	for (int i = 0; i < 8; ++i)
	{
		printf("%lu ",out[i]);
	}
	printf("\n");
}
void addLayer(int nonce_,int val,int chosen,u_int64_t *xors){
	u_int64_t out[8]={0};
	u_int32_t m[16]={0};
	m[0]=0xfffff;m[1]=0xfffff;

	m[2]=(((u_int32_t)val<<8)+(u_int32_t)nonce_);

	processblock(m,out);
	// return 0;
	int repl[5][12][2] = {{{0, 0}, {0, 8}, {0, 16}, {0, 24}, {0, 32}, {0, 40}, {0, 48}, {0, 56}, {1, 0}, {1, 8}, {1, 16}, {1, 24}}, {{1, 32}, {1, 40}, {1, 48}, {1, 56}, {2, 0}, {2, 8}, {2, 16}, {2, 24}, {2, 32}, {2, 40}, {2, 48}, {2, 56}}, {{3, 0}, {3, 8}, {3, 16}, {3, 24}, {3, 32}, {3, 40}, {3, 48}, {3, 56}, {4, 0}, {4, 8}, {4, 16}, {4, 24}}, {{4, 32}, {4, 40}, {4, 48}, {4, 56}, {5, 0}, {5, 8}, {5, 16}, {5, 24}, {5, 32}, {5, 40}, {5, 48}, {5, 56}}, {{6, 0}, {6, 8}, {6, 16}, {6, 24}, {6, 32}, {6, 40}, {6, 48}, {6, 56}, {7, 0}, {7, 8}, {7, 16}, {7, 24}}};
	
	
	
	// for(int i=0;i<5;i++){
		for(int j=0;j<12;j++){
			// chosen
			// arr[j]=((out[repl[chosen][j][0]]>>repl[chosen][j][1])&0xFF);
			xors[j] = xors[j]^((out[repl[chosen][j][0]]>>repl[chosen][j][1])&0xFF);
			// arr[tot_index][j]=0xFFFFFFFF;
			// printf("%d ",arr[j]);
		}
		// printf("\n");
		// tot_index+=1;
	// }
}
/*
Round 1:
	val:
		no_limit: 1489136 variables, 5085376 clauses
		5_limit: 1490256 variables, 5089728 clauses
	nonce:
		no_limit: 1489136 variables, 5085376 clauses
		5_limit: 1490324 variables, 5089994 clauses
Round 12:
	val:
		no_limit: 3785625 variables, 18527362 clauses
		5_limit: 3785691 variables, 18527591 clauses
	nonce:
		no_limit: 3785625 variables, 18527362 clauses
		5_limit: 3786780 variables, 18531850 clauses

*/
int main(){
	u_int8_t xors[12]={0};
	// int nonce = 12;//nondet_int();
	u_int8_t nonce = 100;//nondet_uint();
	// __CPROVER_assume(nonce<100);
	
	for(int i=0;i<32;i++){
		int val = nondet_uint();
		int chosen = nondet_uint();

		__CPROVER_assume(chosen>=0&&chosen<5);
		__CPROVER_assume(val>0&&val<=100);

		addLayer(nonce,val,chosen,(u_int8_t *)&xors);

	}

	int flag = 0;
	for (int i = 0; i < 10; i++){
		__CPROVER_assume(xors[i]==0);		
	}
	for(int i=10;i<12;i++){
		flag = (flag)||(xors[i]!=0);
	}
	assert(flag == 1);

}
