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

	// int arr[] = {100,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1\
	// 			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	// int N = 0b11100;
	// int N = nondet_int();

	int arr[32];// = {1};
	for(int i=0;i<32;i++){
		arr[i]=1;
	}
	arr[0]=100;

	int new_arr[2] = {nondet_int()};

	// __CPROVER_assume(arr[0]>0&&arr[0]);
	
	int xorEd = 0;

	
	for(int y=0;y<2;y++){
		for(int x=0;x<16;x++){
			// printf("%d %d\n",(N&(1<<(x+100000))),arr[x]);
			if((new_arr[y]&(1<<(x)))!=0){
			// if(N&x==0){
				xorEd = (xorEd^arr[y*16+x]);
			}
		}
	}

	int flag = 0;

	if((xorEd)!=1){
		flag = 1;
	}
	assert(flag == 1);

	printf("%d\n", xorEd);
}