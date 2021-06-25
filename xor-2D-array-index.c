#include <stdio.h>
#include <stdlib.h>


int main(){
	int arr[2][5] = {{1,2,3,4,5},{1,2,3,4,5}};
	
	// int N = 0b11100;
	int nonDets[5];
	for (int i=0;i<3;i++){
		nonDets[i] = nondet_int();
		__CPROVER_assume(nonDets[i]>=0&&nonDets[i]<5);
	}

	// __CPROVER_assume(N>0);
	// int xorEd = 0;
	int xors[2] = {0};

	for(int x=0;x<3;x++){
		for(int i=0;i<2;i++){
			xors[i] = xors[i]^arr[i][nonDets[x]];
		}
	}

	int flag = 0;

	for(int i=0;i<2;i++){
		flag = (flag)||(xors[i]!=7);
	}
	
	assert(flag == 1);

}
