#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
// sem
#include <sys/sem.h>
// shm
#include <sys/shm.h>
// fork
#include <unistd.h>
// waitpid
#include <sys/wait.h>
// errno
#include <errno.h>

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
	                           (Linux-specific) */
};

// define shared memory id
#define BLOCKSIZE 10
int shmid[BLOCKSIZE];
// define buffer
#define BUFFERSIZE 1024
struct buffer_node{
	char buffer[BUFFERSIZE];
	int my_eof;
	struct buffer_node *next;
};
struct buffer_node *head=NULL,*tail=NULL,*temp=NULL;
// define semaphore
int semid;
// define process 'readbuf' and 'writebuf'
pid_t readbuf;
pid_t writebuf;
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

// read from file and write into shared memory
void subp_writebuf()
{
	int fd;
	int read_size;
	int times=0;
	const char* filename="/home/parallels/test.mkv";
	struct buffer_node *temp=head;
	if ((fd=open(filename,O_RDONLY))==-1){
		printf("open file fail\n");
		return;
	}
	else
		printf("open file: %s\n",filename);
	while(1){
		P(semid,0);
		read_size=read(fd, temp->buffer, BUFFERSIZE);
		if(read_size!=BUFFERSIZE && read_size!=0){// make eof
			printf("the last time(write into shm) size: %d\n",read_size);
			temp->my_eof=read_size;
			close(fd);
			V(semid,1);
			return;
		}
		printf("the %d time(write into shm) size: %d\n",++times,read_size);
		temp=temp->next;
		V(semid,1);
	}
    return;
}

// read from shared memory and write into new file
void subp_readbuf()
{
	int fd;
	int write_size;
	int times=0;
	const char* filename="/home/parallels/new.mkv";
	struct buffer_node *temp=head;
	if ((fd=open(filename,O_WRONLY|O_CREAT,S_IRWXU|S_IXGRP|S_IROTH|S_IXOTH))==-1){
		printf("open file fail\n");
		return;
	}
	else
		printf("open file: %s\n",filename);
	while(1){
		P(semid,1);
		if(temp->my_eof!=0){// read eof
			write_size=write(fd, temp->buffer, temp->my_eof);
			printf("the last time(read from shm): %d\n",write_size);
			close(fd);
			V(semid,0);
		 	return ;
		}
		write_size=write(fd, temp->buffer, BUFFERSIZE);
		printf("the %d time(read from shm): %d\n",++times,write_size);
		temp=temp->next;
		V(semid,0);
	}
    return;
}


int main(void)
{
    // 创建共享内存组 int shmget(key_t key, size_t size, int shmflg);
	int i;
	for(i=0;i<BLOCKSIZE;i++){
		// get shm
	    shmid[i] = shmget(IPC_PRIVATE, sizeof(struct buffer_node), IPC_CREAT|0600);
	    if(shmid[i]==-1){
	        printf("shmget error: %s\n",strerror(errno));
	        return -1;
	    }

		// make shm list
		if(i==0){// head node
			// link shm
			head=shmat(shmid[i],NULL,SHM_RND);
			if(head==(void*)-1){
				printf("shmat error\n");
				return -1;
			}
			head->next=head;
			head->my_eof=0;
			tail=head;
		}
		else{// else nodes
			// link shm
			temp=shmat(shmid[i],NULL,SHM_RND);
			if(temp==(void*)-1){
				printf("shmat error\n");
				return -1;
			}
			temp->next=head;
			temp->my_eof=0;
			tail->next=temp;
			tail=temp;
		}
	}

    // 创建信号灯 semget(key_t key, int nsems, int semflg);
    semid = semget(IPC_PRIVATE, 2, IPC_CREAT|0600);
    if(semid==-1){
        printf("semget error\n");
        return -1;
    }

    // 信号灯赋初值；
    union semun arg_0,arg_1;
    arg_1.val=BLOCKSIZE;
	arg_0.val=0;
    semctl(semid,0,SETVAL,arg_1);
	semctl(semid,1,SETVAL,arg_0);

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
            if(semctl(semid,0,IPC_RMID)!=-1)printf("sem has been closed\n");
            // 删除共享内存组；
			for(i=0;i<BLOCKSIZE;i++){
            	if(shmctl(shmid[i],0,IPC_RMID)==-1)printf("shm %d closed error\n",i);
			}
			printf("shm has been closed\n");
			// unmap the shared memory
			while(head->next!=tail){
				temp=head;
				head=head->next;
				shmdt((void*)temp);
			}
			shmdt((void*)head);// now head->next==tail
			shmdt((void*)tail);
        }
    }

    return 0;
}
