#include<stdio.h>
#include<unistd.h>
#include<time.h>
void init_daemon(void);
int main()
{
	FILE *fp;
	time_t t;
	init_daemon();
	while(1)
	{
		sleep(10);
		if((fp=fopen("test5.log","a"))>=0)
			{
				t=time(0);
				fprintf(fp,"守护进程在运行， 时间是 : %s",asctime(loacltime(&t)));
				fclose(fp);
			}
	}
}
