#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
// thread
#include <pthread.h>
// sem
#include <sys/sem.h>

// define shared memory id
int shmid;
// define semaphore
int semid;
// define process 'readbuf' and 'writebuf'
pthread_t readbuf;
pthread_t writebuf;
// define function of P、V opreations
void P(int semid,int index);
void V(int semid,int index);
// define sub process
void subfunc_readbuf();
void subfunc_writebuf();

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

void subp_readbuf()
{
    int map_addr=0;
    // associated with the shared memory
    shmat(shmid,map_addr,SHM_RND);

    

    // unmap the shared memory
    shmdt(map_addr);
    exit(0);
}

void subp_writebuf()
{
    int map_addr=0;
    // associated with the shared memory
    shmat(shmid,map_addr,SHM_RND);



    // unmap the shared memory
    shmdt(map_addr);
    exit(0);
}

int main(void)
{
    // 创建共享内存组 int shmget(key_t key, size_t size, int shmflg);
    shmid = shmget(IPC_PRIVATE, 10000, IPC_CREAT)
    if(shmid==-1){
        printf("shmget error\n");
        return -1;
    }

    // 创建信号灯 semget(key_t key, int nsems, int semflg);
    semid = semget(IPC_PRIVATE, 1, SEM_A|SEM_R);
    if(semid==-1){
        printf("semget error\n");
        return -1;
    }

    // 信号灯赋初值；
    union semun arg_sem;
    arg_sem.val=1;
    semctl(semid,0,SETVAL,arg_sem);

	// 创建两个进程readbuf、writebuf; Readbuf负责读、writebuf负责写，如何定义？
    readbuf=fork();
    if(readbuf==0){//readbuf
        subp_readbuf();
    }
    else{//main or writebuf
        writebuf=fork();
        if(writebuf==0){//writebuf
            subp_writebuf();
        }
        else{//main
            // 等待两个进程运行结束；
            int status;
            waitpid(readbuf,&status,0);
            waitpid(writebuf,&status,0);

            // 删除信号灯；
            if(semctl(semid,0,IPC_RMID)==0)printf("sem has been closed\n");

            // 删除共享内存组；
            if(shmctl(shmid,0,IPC_RMID)==0)printf("shm has been closed\n");
        }
    }

    return 0;
}
