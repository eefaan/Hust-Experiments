#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
// thread
#include <pthread.h>
// sem
#include <sys/sem.h>

// function of P、V opreations
void P(int semid,int index);
void V(int semid,int index);

// define semaphore and threads
int semid;
pthread_t p1,p2;

// define sub process
void *subp1();
void *subp2();

// define shared sum
int a=0;

void P(int semid, int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
	return;
}

void V(int semid,int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
	return;
}

// subp1: caculate the sum from 1 to 100
void *subp1()
{
    int i;
	for(i=1;i<=100;i++){
        P(semid,0);
        a+=i;
        V(semid,1);
    }
    pthread_exit(0);
}

// wubp2: printf the sum
void *subp2()
{
    int count=0;
    while(count<100){
        P(semid,1);
        printf("%d\n", a);
        count+=1;
        V(semid,0);
    }
    pthread_exit(0);
}

int main(void)
{
	// 创建信号灯 semget(key_t key, int nsems, int semflg);
    semid = semget(IPC_PRIVATE, 2, SEM_A|SEM_R);
    if(semid==-1){
        printf("semget error\n");
        return -1;
    }

	// 信号灯赋初值；
    union semun arg_0;
    union semun arg_1;
    arg_0.val=0;
    arg_1.val=1;
    semctl(semid,0,SETVAL,arg_1);
    semctl(semid,1,SETVAL,arg_0);

	// 创建两个线程 pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
    pthread_create(&p1,NULL,subp1,NULL);
    pthread_create(&p2,NULL,subp2,NULL);

	// 等待两个线程运行结束 pthread_join(pthread_t thread, void **value_ptr);
    int status;
    if(pthread_join(p1,(void*)&status)==0)printf("p1 terminated\n");
    if(pthread_join(p2,(void*)&status)==0)printf("p2 terminated\n");

    // 删除信号灯；
    if(semctl(semid,0,IPC_RMID)==0)printf("sem has been closed\n");

    return 0;
}
