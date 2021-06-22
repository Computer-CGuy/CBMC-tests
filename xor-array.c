#include <stdio.h>
#include <stdlib.h>

int main(){
	int arr[] = {1,2,3,4,5};
	int N = 0b11100;
	int xorEd = 0;
	for(int x=0;x<5;x++){
		printf("%d %d\n",(N&(1<<x)),arr[x]);
		if((N&(1<<x))!=0){
			xorEd = (xorEd^arr[x]);
		}
	}
	printf("%d\n", xorEd);
}