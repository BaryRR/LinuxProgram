#include<>

int main()
{
	pid_t resutl;
	int r_num;
	int pipe_fd[2];
	char buf_r[100]
	memset(buf_r,0,sizeof(buf_r));
	if(pipe(pipe_fd) < 0)
	{
		perror("创建管道失败");
		return -1;
	}
	result = fork();
	if(result < 0)
	{
		perror("创建子进程失败");
		exit;	
	}
	else if(result == 0)
	{
		colse(pipe_fd[1]);
				
	}
}
