#include <stdio.h>
#include "LIB.H"

int main(){
	Stash ptr;
	initialize(&ptr,4);
	
	int a=4;
	int b=8;
	add(&ptr,&a);
	add(&ptr,&b);
	
	printf("count is %d\n",count(&ptr));

	int* intPtr=(int*) fetch(&ptr,1);

	printf("fetch num is %d\n", (*intPtr));


	cleanup(&ptr);
	
	return 0;
	
}