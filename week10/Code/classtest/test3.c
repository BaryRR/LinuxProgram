#include"my.h"
int g = 10;
int main()
{
	int s=20;
	static int k=30;
	pid_t pid;
	pid = vfork();
	if(pid<0)
	{
		perror("failed vfork!\n");
		exit(-1);
	}
	else if(pid == 0)
	{
		sleep(2);
		execl("./test4","test4",NULL);
		printf("chile pid : = %d ,&g = %16p,&k=%16p\n",getpid(),&g,&s);
		g=100;
		k=300;
		s=200;	
		printf("child pid = %d,&g=%d,&k=%d,&s=%1d\n",getpid(),g,k,s);
		sleep(2);
		_exit(0);
		//return 0;
	}else
	{
		printf("\nparent pid=%d,&g=%16p,&k=%16p,&s=%16p\n",getpid(),&g,&k,&s);
		printf("parent pid=%d:&g=%d,&k=%d,&s=%1d\n",getpid(),g,k,s);
		return 0;
	}
}
