#include"my.h"
void pr_exit(int s,pid_t pid)
{
	int sig;
	if(WIFEXITED(s))
		printf("process %d normal terminaltion,exit status=%d\n",pid,WEXITSTATUS(s));
	else if(WIFSIGNALED(s))
		{
			sig=WTERMSIG(s);
			printf("process %d abnormal termination, signal number=%d%s\n",pid,sig,
			#ifdef WCOREDUMP
				WCOREDUMP(s)?"core file generated":"");
			#else
				"");
			#endif
				psignal(sig,"");
		}
	else if(WIFSTOPPED(s))
		{
			sig=WSTOPSIG(s);
			printf("process %d stopped ,signal number=%d",pid,sig);
			psignal(sig,"");
		}
}
int zero=0;

int main()
{
	int pid,status,r;
	if((pid=fork()) == 0) exit(0);
	if((pid=fork()) == 0) abort();
	if((pid=fork()) == 0) 
		{
			status = status/zero;
			exit(0);
		}	
	while((pid=wait(&status))>=0)
		pr_exit(status,pid);
	perror("parent wait over!\n");
	exit(0);
}
