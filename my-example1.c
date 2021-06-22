// cbmc -DBMC my-example1.c

#include <stdio.h>
#include <stdlib.h>

int N;

int main(){
	N = nondet_int();
	int flag = 0;
	__CPROVER_assume(N==998);
	if((N-1000)!=-2){
		flag = 1;
	}
	assert(flag == 1);
	return 0;
}