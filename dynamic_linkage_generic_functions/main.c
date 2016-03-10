#include "String.h"
#include "../abstract_data_types/new.h"
#include <stdio.h>


int main()
{
	void * a = new(String, "a"), *aa = clone(a);
	void * b = new(String, "b");
	printf("sizeOf(a) == %zu\n",sizeOf(a));
	if(differ(a,b))
		puts("ok");
	if(differ(a,b))
		puts("differ?");
	if(a == aa)
		puts("clone?");

	//delete(a), delete(aa), delete(b);
	return 0;
}
