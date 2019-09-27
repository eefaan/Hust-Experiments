#include <stdio.h>
#include <stdlib.h>

typedef struct STACK{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
}STACK;

void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size (const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany (const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem (const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK *const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK *const p);			//打印p指向的栈
void destroySTACK(STACK *const p);		//销毁p指向的栈

int main(int argc, char** argv)//argv[0]=='./xxx.exe'
{
  STACK *p = (STACK*)malloc(sizeof(STACK));
  STACK *s = (STACK*)malloc(sizeof(STACK));
  p->elems=NULL;
  s->elems=NULL;

  int i,j,pop_temp;
  char flag='#';
  for(i=1;i<argc;i++){

    if(argv[i][0]=='-'){
      //printf {flag,temp}
      if(flag=='#');
      else if(flag=='S'){
        printf("S  %d",p->max);
      }
      else if(flag=='N');
      else if(flag=='G');
      else{
        printf("  %c", flag);
        for(j=0;j<p->pos;j++){
          printf("  %d", p->elems[j]);
        }
      }

      switch (argv[i][1]) {
        case 'S':
          flag='S';
          break;

        case 'I':
          flag='I';
          break;

        case 'O':
          flag='O';
          break;

        case 'C':
          s=p;
          p=(STACK*)malloc(sizeof(STACK));
          p->elems=NULL;
          initSTACK(p,*s);
          flag='C';
          break;

        case 'A':
          flag='A';
          break;

        case 'N':
          printf("  N  %d", p->pos);
          flag='N';
          break;

        case 'G':
          flag='G';
          break;

        default:
          //error now
          break;
      }
    }

    else{
      switch (flag){
        case 'S':
          initSTACK(p,atoi(argv[i]));
          if(p->elems==NULL){
            printf("  S  E\n");
            return 0;
          }
          break;

        case 'I':
          if(howMany(p)==size(p)){
            printf("  I  E\n");
            return 0;
          }
          p=push(p,atoi(argv[i]));
          break;

        case 'O':
          for(j=0;j<atoi(argv[i]);j++){
            if(howMany(p)==0){
              printf("  O  E\n");
              return 0;
            }
            else
            p=pop(p,pop_temp);
          }
          break;

        case 'C':
          //error
          return 0;
          break;

        case 'A':
          s=p;
          p=(STACK*)malloc(sizeof(STACK));
          p->elems=NULL;
          assign(p,*s);
          break;

        case 'N':
          break;

        case 'G':
          if(atoi(argv[i])>p->pos){
            printf("  G  E\n");
            return 0;
          }
          printf("  G  %d",getelem(p,atoi(argv[i])));
          break;

        default:
          //first input S, error
          break;
      }
    }

  }

  if(flag=='#');
  else if(flag=='S'){
    printf("S  %d",p->max);
  }
  else if(flag=='N');
  else if(flag=='G');
  else{
    printf("  %c", flag);
    for(j=0;j<p->pos;j++){
      printf("  %d", p->elems[j]);
    }
  }
  printf("\n");

  destroySTACK(p);
  destroySTACK(s);
  return 0;
}


//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, int m)
{
  if(p->elems==NULL){
    p->elems=(int*)malloc(m*sizeof(int));
    p->max=m;
    p->pos=0;
  }
  else p->elems=NULL;
  return;
}


//用栈s初始化p指向的栈
void initSTACK(STACK *const p, const STACK &s)
{
  int i;
  if(s.elems==0){
    printf("栈s未初始化\n");
    return;
  }
  else{
    p->elems=(int*)malloc(s.max*sizeof(int));  
    for(i=0;i<s.pos;i++){
      p->elems[i]=s.elems[i];
    }
    p->max=s.max;
    p->pos=s.pos;
    return;
  }
}


//返回p指向的栈的最大元素个数max
int  size (const STACK *const p)
{
  if(p->elems==0){
    printf("栈p未初始化\n");
    return 0;
  }

  return p->max;
}


//返回p指向的栈的实际元素个数pos
int  howMany (const STACK *const p)
{
  if(p->elems==0){
    printf("栈p未初始化\n");
    return 0;
  }

  return p->pos;
}


//取下标x处的栈元素
int  getelem (const STACK *const p, int x)
{
  if(p->elems==0){
    printf("栈p未初始化\n");
    return 0;
  }

  if(x<p->pos)
    return p->elems[x];
  else{
    printf("栈中元素不足\n");
    return 0;
  }
}


//将e入栈，并返回p
STACK *const push(STACK *const p, int e)
{
  if(p->elems==0){
    printf("栈p未初始化\n");
    return 0;
  }

  if(p->pos==p->max){
    printf("栈p已满\n");
    return 0;
  }
  else{
    p->elems[p->pos]=e;
    (p->pos)++;
    return p;
  }
}


//出栈到e，并返回p
STACK *const pop(STACK *const p, int &e)
{
  if(p->elems==0){
    printf("栈p未初始化\n");
    return 0;
  }

  if(p->pos==0){
    printf("栈p已空\n");
    return 0;
  }
  else{
    e=p->elems[(p->pos)-1];
    p->pos--;
    return p;
  }
}


//赋s给p指的栈,并返回p
STACK *const assign(STACK *const p, const STACK&s)
{
  int i;
  p->elems=(int*)malloc((s.max)*sizeof(int));
  for(i=0;i<s.pos;i++){
    p->elems[i]=s.elems[i];
  }
  p->max=s.max;
  p->pos=s.pos;
  return p;
}


//打印p指向的栈
void print(const STACK *const p)
{
  if(p->elems==0){
    printf("栈p未初始化\n");
    return;
  }

  if(p->pos==0){
    printf("栈p为空\n");
    return;
  }
  int i;
  printf("max:%d ,pos:%d\n堆栈元素:\n",p->max,p->pos);
  for (i=0;i<p->pos;i++){
    printf("%d\n",p->elems[i]);
  }
  return;
}


//销毁p指向的栈
void destroySTACK(STACK *const p)
{
  if(p==0)
    return;
  if(p->elems){
    free(p->elems);
    p->elems=NULL;
  }
  if(p){
    free(p);
  }
  return;
}
