#include <stdio.h>
#include <stdlib.h>


/*
Tests Successful

x	0 10 5 6  
SAT Y N  Y Y	


At X=0, with __CPOVER_assume = 0 it's SATISFIABLE

*/


int main(){
	// int arr[] = {1,1,};

	int length_of_arr = 65;

	int arr[] = {100,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1\
				,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	// int N = 0b11100;
	// int N = nondet_int();

	int new_arr[3] = {nondet_int()};

	__CPROVER_assume((arr*+0)>0&&(arr*+1)>0&&(arr*+2)>0);
	
	int xorEd = 0;

	
	for(int y=0;y<3;y++){
		for(int x=0;x<mon65;x++){
			// printf("%d %d\n",(N&(1<<(x+100000))),arr[x]);
			if((N&(1<<(x)))!=0){
			// if(N&x==0){
				xorEd = (xorEd^arr[3*32+x]);
			}
		}
	}

	int flag = 0;

	if((xorEd)!=100){
		flag = 1;
	}
	assert(flag == 1);

	printf("%d\n", xorEd);
}