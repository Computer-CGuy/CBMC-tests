#include <stdio.h>
#include <stdlib.h>


int main(){
	int arr[] = {1,2,3,4,5};
	
	// int N = 0b11100;
	int nonDets[5];
	for (int i=0;i<5;i++){
		nonDets[i] = nondet_int();
		__CPROVER_assume(nonDets[i]>=0&&nonDets[i]<5);
	}

	// __CPROVER_assume(N>0);
	int xorEd = 0;

	for(int x=0;x<3;x++){
		// printf("%d %d\n",(N&(1<<x)),arr[x]);
		// if((N&(1<<x))!=0){
		// if((N&(1<<x))!=0){
		// // if(N%x==0){
		// 	xorEd = (xorEd^arr[x]);
		// }
		xorEd = xorEd^arr[nonDets[x]];
	}

	int flag = 0;

	if((xorEd)!=10){
		flag = 1;
	}
	assert(flag == 1);


	printf("%d\n", xorEd);
}
