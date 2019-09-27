#include<stdio.h>
#include<string.h>

struct web_manage{
    char short_name[20];
    char full_name[40];
    char website[100];
};

int main (void)
{
    struct web_manage web[100];
    int N,i,j;
    scanf("%d",&N);

    //input
    for(i=0;i<N;i++)
        scanf("%s%s%s",web[i].short_name,web[i].full_name,web[i].website);

    //output
    for(i=0;i<N;i++)
        printf("%-20s%-40s%s\n",web[i].short_name,web[i].full_name,web[i].website);
    printf("\n");

    //sort
    struct web_manage temp;
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            if(strcmp(web[i].short_name,web[j].short_name)>1){
                temp=web[i];
                web[i]=web[j];
                web[j]=temp;
            }
        }
    }

    //output after sort
    for(i=0;i<N;i++)
        printf("%-20s%-40s%s\n",web[i].short_name,web[i].full_name,web[i].website);

}
