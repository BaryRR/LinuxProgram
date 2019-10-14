#include "lib.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>

int main()
{	
	int a[UNUMBER];
	
	void *handle;
	void (*show)();
	int (*max)(),(*sum)();
	void(*urand)();
	char* error;
	handle = dlopen("/home/rlk/Study/week6/Code/DynamicLib/libtest.so",RTLD_LAZY);

	if(!handle)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);	
	}
	urand=dlsym(handle,"urand");
	if((error=dlerror())!=NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);	
	}
	urand(a,UNUMBER);
	show=dlsym(handle,"show");
	if((error=dlerror())!=NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);	
	}
	max=dlsym(handle,"max");
	if((error=dlerror())!=NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);	
	}
	sum=dlsym(handle,"sum");
	if((error=dlerror())!=NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);	
	}
	show(a,UNUMBER);
	printf("max=%d\n", max(a, UNUMBER));
	printf("sum=%d\n", sum(a, UNUMBER));
	if(dlclose(handle)<0)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);	
	}
	return 0;
}
