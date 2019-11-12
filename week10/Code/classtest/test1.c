#include"my.h"
static void fun1(void)
{
	printf("inboked callbackfun1!\n");
}
static void fun2(void)
{printf("inboked callbackfun2\n");}
int main()
{
	atexit(fun1);
	atexit(fun2);
	FILE *fp;
	char buf[] = "buffer data!";
	if((fp = fopen("test.dat","w+")) == NULL)
	{
		perror("create file failed!\n");
		exit(-1);	
	}
	if(fputs(buf,fp) == EOF)
	{
		perror("fputs file failed!\n");
		exit(-1);
	}
	printf("hello    \n");
	exit(0);
}
