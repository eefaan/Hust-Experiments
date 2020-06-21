#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipefd[2];

pid_t sub1;
pid_t sub2;

void my_func(int sig_no){
    if(sig_no == SIGINT){//break in main
        //send sign to sub1 and sub2
        kill(sub1,SIGUSR1);
        kill(sub2,SIGUSR2);
    }
}

void my_sig1_func(int sig_no){
    if(sig_no == SIGUSR1){
        //close pipe
        close(pipefd[0]);
        close(pipefd[1]);
        //printf sign
        printf("\nChild Process %d is Killed by Parent!",1);
        exit(0);
    }
}

void my_sig2_func(int sig_no){
    if(sig_no == SIGUSR2){
        //close pipe
        close(pipefd[0]);
        close(pipefd[1]);
        //printf sign
        printf("\nChild Process %d is Killed by Parent!",2);
        exit(0);
    }
}

int main(void)
{
    pipe(pipefd);//create unnamed pipe
                 //pipefd[0] is only used for read
                 //pipefd[1] is only used for write

    //bind SIGINT with my_func
    signal(SIGINT, my_func);

    //create sub1
    sub1 = fork();
    if(sub1 == 0){//sub1
        signal(SIGINT,SIG_IGN);//ignore SIGINT
        signal(SIGUSR1,my_sig1_func);//bind SIGUSR1 with my_sig1_func
        int count=1;
        while(1){
            write(pipefd[1],&count,sizeof(int));
            printf("I send you %d times\n", count++);
            sleep(1);
        }
    }
    else{//main or sub2
        //create sub2
        sub2 = fork();
        if(sub2 == 0){//sub2
            signal(SIGINT,SIG_IGN);//ignore SIGINT
            signal(SIGUSR2,my_sig2_func);//bind SIGUSR2 with my_sig2_func
            while(1){
                int buf=0;
                read(pipefd[0],&buf,sizeof(int));
                printf("I receive %d times\n",buf);
            }
        }
        else{//main
            //waiting sub function unitl they exit
            int status;
            waitpid(sub1,&status,0);
            waitpid(sub2,&status,0);
            //close pipe
            close(pipefd[0]);
            close(pipefd[1]);
            printf("\nParent Process is Killed!\n");
        }
    }

    return 0;
}
