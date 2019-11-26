#include "my.h"
#define NUM 16383
int main()
{
	pid_t p1,p2,p3;
	int pipe1[2];
	int pipe2[2];
	char temp[4];
	char buf_r[NUM];
	int r_num;
	long sum=0;
	if(pipe(pipe1)<0 || pipe(pipe2)<0)
	{
		perror("create pipe failed\n");
	}
	if((p1=fork())<0)//第一次派生
	{
		perror("fork1 failed\n");
		exit(0);
	}
	if(p1==0)//子进程
	{
		close(pipe1[0]); 
		close(pipe2[0]);
		close(pipe2[1]);//关闭管道2的读写 管道1的读
		for(int i=0;i<NUM;i++)
		{
			int bytes = sprintf(temp,"%x",i);
			printf("%s",temp);
			if(bytes>0)
			{
				printf("child write\n");	
				if(write(pipe1[1],temp,sizeof(temp)) != -1)
					printf("child1 write %d,%s\n",i,temp);
			}
		}
		close(pipe1[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		p2=fork(); //第二次派生
		printf("ds");
		if(p2<0)
		{
			perror("fork2 failed\n");
			exit(0);
		}
		if(p2==0)
		{
			int a;
			printf("fork 2\n");
			close(pipe1[1]);
			close(pipe2[0]);
			for(int i=0;i<NUM;i++)
			{
				printf("child\n");
				if((r_num=read(pipe1[0],temp,sizeof(temp)))>0)
					printf("child2 read %d,%s\n",i,temp);
				if(write(pipe2[1],temp,sizeof(temp)) != -1)
					printf("child2 write %d\n",i);
			}
			close(pipe1[1]);
			close(pipe2[1]);
			exit(0);
		}
		else
		{
			wait(NULL);
			p3=fork();//第三次派生
			if(p3<0)
			{
				perror("fork3 failed\n");
				exit(0);
			}
			if(p3==0)
			{
				close(pipe1[0]);
				close(pipe1[1]);
				close(pipe2[1]);
				int b;
				for(int i=0;i<NUM;i++)
				{
					printf("child3\n");
					if((r_num=read(pipe2[0],temp,sizeof(temp)))>0)
						printf("child3 read %d,%s\n",i,temp);
					sscanf(temp,"%x",&b);
					printf("b=%d\n",b);
					sum+=b;
					printf("sum=%d\n",sum);
				}
				printf("sum=%ld\n",sum);
				exit(0);
			}
			else{
				wait(NULL);
				close(pipe1[0]);
				close(pipe1[1]);
				close(pipe2[0]);
				close(pipe2[1]);
			}
		}
	}
}

