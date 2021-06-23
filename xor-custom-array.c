#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	

	int n = 5;

	int arr[n];
	
	// bool Ns[] = {1,1,1,1,1};

	int xorEd = 0;
	
	for (int i = 0; i < n; ++i)
	{
		arr[i]=nondet_uint();
		__CPROVER_assume(arr[i]!=0);
		xorEd^=arr[i];
	}

	int flag = 0;

	if((xorEd)!=0){
		flag = 1;
	}
	assert(flag == 1);


	printf("%d\n", xorEd);
}
