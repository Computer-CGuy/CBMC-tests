#include <stdio.h>
#include <stdlib.h>


/*
Tests Successful

x	0 10 5 6  
SAT Y N  Y Y	


At X=0, with __CPOVER_assume = 0 it's SATISFIABLE

*/


int main(){
	int arr[] = {1,2,3,4,5};
	
	// int N = 0b11100;
	int N = nondet_int();

	__CPROVER_assume(N>0);
	int xorEd = 0;

	for(int x=0;x<5;x++){
		printf("%d %d\n",(N&(1<<x)),arr[x]);
		// if((N&(1<<x))!=0){
		if((N&(1<<x))!=0){
		// if(N%x==0){
			xorEd = (xorEd^arr[x]);
		}
	}

	int flag = 0;

	if((xorEd)!=5){
		flag = 1;
	}
	assert(flag == 1);


	printf("%d\n", xorEd);
}
