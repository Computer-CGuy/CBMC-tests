#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	

	int n = 10;

	int arr[n];
	
	// bool Ns[] = {1,1,1,1,1};

	int xorEd = 0;
	
	int a = nondet_uint();
	__CPROVER_assume(a!=0);
	for (int i = 0; i < 1; ++i)
	{
		arr[i]=a+i;
		xorEd^=arr[i];
	}

	int flag = 0;

	if((xorEd)!=1){
		flag = 1;
	}
	assert(flag == 1);


	printf("%d\n", xorEd);
}
