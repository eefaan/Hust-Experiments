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
pthread_t p1,p2,p3,p4;

// define sub process
void *subp1();
void *subp2();
void *subp3();
void *subp4();

// define shared sum
int a=0;
const int b=100;

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

// subp1: seller1
void *subp1()
{
    while(1){
        P(semid,0);
        if(a<b){
            a+=1;
            printf("ticket %d has been sold to p1\n",a);
            V(semid,0);
        }
        else{
            V(semid,0);
            pthread_exit(0);
        }
    }
}

// subp2: seller2
void *subp2()
{
    while(1){
        P(semid,0);
        if(a<b){
            a+=1;
            printf("ticket %d has been sold to p2\n",a);
            V(semid,0);
        }
        else{
            V(semid,0);
            pthread_exit(0);
        }
    }
}

// subp3: seller3
void *subp3()
{
    while(1){
        P(semid,0);
        if(a<b){
            a+=1;
            printf("ticket %d has been sold to p3\n",a);
            V(semid,0);
        }
        else{
            V(semid,0);
            pthread_exit(0);
        }
    }
}

// subp4: seller4
void *subp4()
{
    while(1){
        P(semid,0);
        if(a<b){
            a+=1;
            printf("ticket %d has been sold to p4\n",a);
            V(semid,0);
        }
        else{
            V(semid,0);
            pthread_exit(0);
        }
    }
}

int main(void)
{
	// 创建信号灯 semget(key_t key, int nsems, int semflg);
    semid = semget(IPC_PRIVATE, 1, SEM_A|SEM_R);
    if(semid==-1){
        printf("semget error\n");
        return -1;
    }

	// 信号灯赋初值；
    union semun arg_1;
    arg_1.val=1;
    semctl(semid,0,SETVAL,arg_1);

	// 创建两个线程 pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
    pthread_create(&p1,NULL,subp1,NULL);
    pthread_create(&p2,NULL,subp2,NULL);
    pthread_create(&p3,NULL,subp3,NULL);
    pthread_create(&p4,NULL,subp4,NULL);

	// 等待两个线程运行结束 pthread_join(pthread_t thread, void **value_ptr);
    int status;
    if(pthread_join(p1,(void*)&status)==0)printf("p1 terminated\n");
    if(pthread_join(p2,(void*)&status)==0)printf("p2 terminated\n");
    if(pthread_join(p3,(void*)&status)==0)printf("p3 terminated\n");
    if(pthread_join(p4,(void*)&status)==0)printf("p4 terminated\n");

    // 删除信号灯；
    if(semctl(semid,0,IPC_RMID)==0)printf("sem has been closed\n");

    return 0;
}
