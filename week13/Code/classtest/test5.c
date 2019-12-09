#include "my.h"

void usage()
{
	fprintf(stderr,"sigqueue_send sig pid [times].\n");
}

int main(int argc,char *argv[])
{
	pid_t pid;
	int sig;
	union sigval,mysigval;
	int times;
	if(argc<3)
	{
		usage();
		return -1;
	}
	pid = atoi(argv[1]);
	sig = atoi(argv[2]);
	if(argc>=4)
	{
		times = atoi(argv[3]);	
	}	
	mysigval.sival_int = 123;
	if(sig<0||sig>64||times<0)
	{
		usage();
		return -1;
	}
	int i=0;
	for(i=0;i<times;i++)
	{
		
	}
}