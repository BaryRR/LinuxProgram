
#include "my.h"
typedef struct
{
        int Res[5];

        pthread_cond_t wr_cond;
        pthread_mutex_t wr_mutex;
        int wr_wait;
        pthread_cond_t rd_cond;
        pthread_mutex_t rd_mutex;
        int rd_wait;
        
}Storage;

void set_data(Storage* s,int value)
{
        Res[i]=value;
}

int get_data(Storage* s)
{
        return s->Res[i];
}

void *set_fn(void* arg)
{
        int i=0;
        int sum=0;
        Storage* s=(Storage*)arg;
        for(i=0;i<=4;i++)
        {
                sum=rand()%100;
                set_data(i,sum);
                printf("0x%lx(count=%d) write data=%d\n",pthread_self(),i,s->Res);
		}
                //对共享的资源条件变量进行上上锁保护，直到读取线程准备完成                      
                pthread_mutex_lock(&s->rd_mutex);
                while(!s->rd_wait)
                {
                        pthread_mutex_unlock(&s->rd_mutex);
                        usleep(100);
                        pthread_mutex_lock(&s->rd_mutex);
                }
                //读取线程准备好之后，清零，下次继续等待。解锁
                s->rd_wait=0;
                pthread_mutex_unlock(&s->rd_mutex);
                //通知读线程
                pthread_cond_broadcast(&s->rd_cond);

                //写线程完成后，再将写线程上锁阻塞，等待读线程想写线程发送命令
                pthread_mutex_lock(&s->wr_mutex);
                s->wr_wait=1;
                pthread_cond_wait(&s->wr_cond,&s->wr_mutex);
                pthread_mutex_unlock(&s->wr_mutex);
				return 0;

        }

/*
*读数据线程，将计算的结果写入到结果值中再通知读线程
*/
void *get_fn(void* arg)
{
        Storage* s=(Storage*)arg;
        int i=0;
        for(i=1;i<=5;i++)
        {
                //对条件变量进行上锁。保护等待队列，直到条件变量触发。
                pthread_mutex_lock(&s->rd_mutex);
                s->rd_wait=1;
                pthread_cond_wait(&s->rd_cond,&s->rd_mutex);
                pthread_mutex_unlock(&s->rd_mutex);
                //获取数据
                get_data(s);
                printf("0x%lx(count=%d )get data=%d\r\n",pthread_self(),i,s->Res);
		}
                //对条件变量进行上锁，直到写线程准备好之后，进行广播通知写线程
                pthread_mutex_lock(&s->wr_mutex);
                while(!s->wr_wait)
                {
                        pthread_mutex_unlock(&s->wr_mutex);
                        usleep(100);
                        pthread_mutex_lock(&s->wr_mutex);
                }
                //写数据的条件清零，以便下次等待写线程等待通知
                s->wr_wait=0;
                pthread_mutex_unlock(&s->wr_mutex);
                pthread_cond_broadcast(&s->wr_cond);
        
        return 0;
}

//主程序，创建读写任务的函数
int main(void)
{
        int err;
        pthread_t set,get;
        Storage s;
        s.wr_wait=0;
        s.rd_wait=0;
        //初始化条件变量与互斥锁
        pthread_cond_init(&s.wr_cond,NULL);
        pthread_cond_init(&s.rd_cond,NULL);
        pthread_mutex_init(&s.wr_mutex,NULL);
        pthread_mutex_init(&s.rd_mutex,NULL);
        //创建两个线程，一个写数据线程一个对数据线程
        if((err=pthread_create(&set,NULL,set_fn,(void*)&s))!=0)
        {
                perror("set_fn creat fail!\r\n");
        }

        if((err=pthread_create(&get,NULL,get_fn,(void*)&s))!=0)
        {
                perror("get_fn creat fail!\r\n");
        }
        //线程等待
        pthread_join(set,NULL);
        pthread_join(get,NULL);
        //线程互斥锁销毁与条件变量销毁
        pthread_mutex_destroy(&s.wr_mutex);
        pthread_mutex_destroy(&s.rd_mutex);
        pthread_cond_destroy(&s.wr_cond);
        pthread_cond_destroy(&s.rd_cond);

        return 0;
}
