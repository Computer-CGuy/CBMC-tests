#include <stdio.h>
#include <stdlib.h>


/*
Tests Successful

x	0 10 5 6  
SAT Y N  Y Y	


At X=0, with __CPOVER_assume = 0 it's SATISFIABLE

*/


int main(){
	int arr[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,10000};//1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100};
	
	// int N = 0b11100;
	int N = nondet_int();

	__CPROVER_assume(N>0);
	
	int xorEd = 0;

	// for(int x=0;x<(sizeof(arr)/sizeof(arr[0]));x++){
	for(int x=0;x<32;x++){
		printf("%d %d\n",(N1&(1<<x)),arr[x]);
		// if((N&(1<<x))!=0){
		if((N1&(1<<x))!=0){
		// if(N%x==0){
			xorEd = (xorEd^arr[x]);
		}
	}
	int flag = 0;

	if((xorEd)!=10000){
		flag = 1;
	}
	assert(flag == 1);

	printf("%d\n", xorEd);
}
