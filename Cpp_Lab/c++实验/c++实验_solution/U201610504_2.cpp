   #include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);		          //初始化栈：最多m个元素
    STACK(const STACK&s);         //用栈s拷贝初始化栈
    int  size ( ) const;		  //返回栈的最大元素个数max
    int  howMany ( ) const;	      //返回栈的实际元素个数pos
    int  getelem (int x) const;	  //取下标x处的栈元素
    STACK& push(int e); 	      //将e入栈,并返回栈
    STACK& pop(int &e);        	  //出栈到e,并返回栈
    STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
    void print( ) const;		  //打印栈
    ~STACK( );				      //销毁栈
};

//初始化栈：最多m个元素
STACK::STACK(int m):elems(new int[m]),max(m),pos(0){
    return;
}

//用栈s拷贝初始化栈
STACK::STACK(const STACK&s):elems(new int[s.size()]),max(s.size()),pos(0){
    for(int i=0;i<s.howMany();i++){
        this->push(s.getelem(i));
    }
    return;
}

//返回栈的最大元素个数max
int STACK::size() const{
    return this->max;
}

//返回栈的实际元素个数pos
int STACK::howMany() const{
    return this->pos;
}

//取下标x处的栈元素
int STACK::getelem(int x) const{
    if(x>=0 && x<pos)
        return this->elems[x];
    else
        return -1;
}

//将e入栈,并返回栈
STACK& STACK::push(int e){
    elems[pos]=e;
    pos++;
    return *this;
}

//出栈到e,并返回栈
STACK& STACK::pop(int &e){
    e=elems[pos-1];
    pos--;
    return *this;
}

//赋s给栈,并返回被赋值的栈
STACK& STACK::assign(const STACK&s){
    pos=0;
    *(int*)(&max)=s.size();
    *(int**)(&elems)=new int[s.size()];
    for(int i=0;i<s.howMany();i++){
        push(s.getelem(i));
    }
    return *this;
}

//打印栈
void STACK::print() const{
    for(int i=0;i<pos;i++){
        cout<<' '<<' '<<elems[i];
    }
    return;
}

//销毁栈
STACK::~STACK( ){
    delete []elems;
}

int main(int argc, char** argv)
{
    STACK *p = (STACK*)malloc(sizeof(STACK));
    STACK *s = (STACK*)malloc(sizeof(STACK));
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
            s=new STACK(*p);
            flag='C';
            break;

          case 'A':
            flag='A';
            break;

          case 'N':
            printf("  N  %d", p->howMany());
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
            p = new STACK(atoi(argv[i]));
            break;

          case 'I':
            if(p->howMany()==p->size()){
              printf("  I  E\n");
              return 0;
            }
            p=&(p->push(atoi(argv[i])));
            break;

          case 'O':
            for(j=0;j<atoi(argv[i]);j++){
              if(p->howMany()==0){
                printf("  O  E\n");
                return 0;
              }
              else
              p=&(p->pop(pop_temp));
            }
            break;

          case 'C':
            //error
            return 0;
            break;

          case 'A':
            s=new STACK(*p);
            p=&(p->assign(*s));
            break;

          case 'N':
            break;

          case 'G':
            if(atoi(argv[i])>p->howMany()){
              printf("  G  E\n");
              return 0;
            }
            printf("  G  %d",p->getelem(atoi(argv[i])));
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
