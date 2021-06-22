#include <stdio.h>
#include <stdlib.h>

int main(){
	short int arr1[] = {1,2,3,4,100};
	short int arr2[] = {1,2,3,4,1000};
	
	// int N = 0b11100;
	int N = nondet_int();

	__CPROVER_assume(N>0);
	
	int xorEd1 = 0;
	int xorEd2 = 0;

	for(int x=0;x<5;x++){
		// printf("%d %d\n",(N&(1<<x)),arr[x]);
		// if((N&(1<<x))!=0){
		if((N&(1<<x))!=0){
		// if(N%x==0){
			xorEd1 = (xorEd1^arr1[x]);
			xorEd2 = (xorEd2^arr2[x]);
		}
	}

	// int flag = 0;
	// // int eq = 1;
	// if((xorEd1!=1) && (xorEd2!=1)){
	// 	flag = 1;
	// }
	assert((xorEd1!=101) || (xorEd2!=1001));
	// assert(flag == 1);


	// printf("%d\n", xorEd);
}
