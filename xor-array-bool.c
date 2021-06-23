#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int arr[] = {1,2,3,4,5};
	
	bool Ns[] = {1,1,1,1,1};

	for (int i = 0; i < 5; ++i)
	{
		Ns[i]=nondet_bool();
		__CPROVER_assume(Ns[i]>=0&&Ns[i]<=1);
	}
	int xorEd = 0;

	for(int x=0;x<5;x++){
		// printf("%d %d\n",(N&(1<<x)),arr[x]);
		// if((N&(1<<x))!=0){
		xorEd = xorEd^(Ns[x]*arr[x]);
		// if((N&(1<<x))!=0){
		// // if(N%x==0){
		// 	xorEd = (xorEd^arr[x]);
		// }
	}

	int flag = 0;

	if((xorEd)!=5){
		flag = 1;
	}
	assert(flag == 1);


	printf("%d\n", xorEd);
}
