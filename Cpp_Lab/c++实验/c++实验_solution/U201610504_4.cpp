#include"stack.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

class QUEUE:public STACK{
    STACK  s2;
public:
    QUEUE(int m);                            //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE&s);                    //用队列s拷贝初始化队列
    virtual operator int ( ) const;          //返回队列的实际元素个数
    virtual int full ( ) const;              //返回队列是否已满，满返回1，否则返回0
    virtual int operator[ ](int x)const;     //取下标为x的元素，第1个元素下标为0
    virtual QUEUE& operator<<(int e);        //将e入队列,并返回队列
    virtual QUEUE& operator>>(int &e);	     //出队列到e,并返回队列
    virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
    virtual void print( ) const;			 //打印队列
    virtual ~QUEUE( );					     //销毁队列
};


//每个栈最多m个元素，要求实现的队列最多能入2m个元素
QUEUE::QUEUE(int m):s2(m),STACK(m){}

//用队列s拷贝初始化队列
QUEUE::QUEUE(const QUEUE&s):s2(s.size()),STACK(s.size()){
    for(int i=0;i<s;i++){
        *this<<(s[i]);
    }
    return;
}

//返回队列的实际元素个数
QUEUE::operator int() const{
    return (STACK::operator int()+s2);
}

//返回队列是否已满，满返回1，否则返回0
int QUEUE::full() const{
    if((s2==s2.size())&&(STACK::operator int()>0))return 1;
    return 0;
}

//取下标为x的元素，第1个元素下标为0
int QUEUE::operator[ ](int x) const{
    if(STACK::operator int()>x)return STACK::operator[](STACK::operator int()-x-1);
    else return s2[x-STACK::operator int()];
}

//将e入队列,并返回队列
QUEUE& QUEUE::operator<<(int e){
    if((s2==s2.size())&&(STACK::operator int()==0)){//s2->s
        int temp;
        while(s2>0){
            s2>>(temp);
            STACK::operator<<(temp);
        }
    }
    s2<<e;
    return *this;
}

//出队列到e,并返回队列
QUEUE& QUEUE::operator>>(int &e){
    if(STACK::operator int()>0){
        STACK::operator>>(e);
    }
    else{
        int temp;
        while(s2){
            s2>>(temp);
            STACK::operator<<(temp);
        }
        STACK::operator>>(e);
    }
    return *this;
}

//赋s给队列,并返回被赋值的队列
QUEUE& QUEUE::operator=(const QUEUE&s){
    STACK temp1(s.size());
    STACK temp2(s.size());
    STACK::operator=(temp1);
    s2.operator=(temp2);

    for(int i=0;i<s;i++){
        (*this)<<(s[i]);
    }
    return *this;
}

//打印队列
void QUEUE::print() const{
    for(int i=(STACK::operator int())-1;i>=0;i--){
        cout<<"  "<<STACK::operator[ ](i);
    }
    for(int i=0;i<s2;i++){
        cout<<"  "<<s2[i];
    }
    return;
}

//销毁栈
QUEUE::~QUEUE( ){}

int main(int argc, char** argv)
{
    if(argc==1){
        int M,F,m,f;
        // input here
        cout<<"input M:";
        cin>>M;
        cout<<"input F:";
        cin>>F;
        cout<<"input m:";
        cin>>m;
        cout<<"input f:";
        cin>>f;

        if(m>M||f>F){
            cout<<"wrong input";
            return 0;
        }

        QUEUE q1(M);
        QUEUE q2(F);

        int count=0;
        int temp1=0,temp2=0;
        while(1){
            //initial here
            if(q1==0){
                for(int i=0;i<M;i++){
                    if(i==m-1)q1<<1;
                    else q1<<0;
                }
            }
            if(q2==0){
                for(int i=0;i<F;i++){
                    if(i==f-1)q2<<1;
                    else q2<<0;
                }
            }

            //pop and calculate here
            count++;
            q1>>temp1;
            q2>>temp2;
            if(temp1 && temp2){
                cout<<"result:"<<count<<"\n";
                break;
            }
        }
        return 0;
    }
    QUEUE *p = (QUEUE*)malloc(sizeof(QUEUE));
    QUEUE *s = (QUEUE*)malloc(sizeof(QUEUE));
    p=0;
    s=0;

    int i,j,pop_temp;
    char flag='#';
    for(i=1;i<argc;i++){

      if(argv[i][0]=='-'){
        if(flag=='#');
        else if(flag=='S'){
          printf("S  %d",p->size());
        }
        else if(flag=='N');
        else if(flag=='G');
        else{
          printf("  %c", flag);
          p->print();
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
            s=new QUEUE(*p);
            flag='C';
            break;

          case 'A':
            flag='A';
            break;

          case 'N':
            // printf("  N  %d", *p);
            cout<<"  N  "<<(*p);
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
            p = new QUEUE(atoi(argv[i]));
            break;

          case 'I':
            if(p->full()){
              printf("  I  E\n");
              return 0;
            }
            p=&((*p)<<(atoi(argv[i])));
            break;

          case 'O':
            for(j=0;j<atoi(argv[i]);j++){
              if(*p==0){
                printf("  O  E\n");
                return 0;
              }
              else
              p=&((*p)>>pop_temp);
            }
            break;

          case 'C':
            //error
            return 0;
            break;

          case 'A':
            s=new QUEUE(*p);
            *p=*s;
            break;

          case 'N':
            break;

          case 'G':
            if(atoi(argv[i])>(*p)){
              printf("  G  E\n");
              return 0;
            }
            printf("  G  %d",(*p)[atoi(argv[i])]);
            break;

          default:
            //first input S, error
            break;
        }
      }

    }

    if(flag=='#');
    else if(flag=='S'){
      printf("S  %d",p->size());
    }
    else if(flag=='N');
    else if(flag=='G');
    else{
      printf("  %c", flag);
      p->print();
    }
    printf("\n");

    delete p;
    delete s;
    return 0;
}
