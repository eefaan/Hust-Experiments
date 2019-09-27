#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);		                     //初始化栈：最多m个元素
    STACK(const STACK&s); 			         //用栈s拷贝初始化栈
    virtual int  size ( ) const;			 //返回栈的最大元素个数max
    virtual operator int ( ) const;			 //返回栈的实际元素个数pos
    virtual int operator[ ] (int x) const;	 //取下标x处的栈元素
    virtual STACK& operator<<(int e); 	     //将e入栈,并返回栈
    virtual STACK& operator>>(int &e);	     //出栈到e,并返回栈
    virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
    virtual void print( ) const;			 //打印栈
    virtual ~STACK( );					     //销毁栈
};


//初始化栈：最多m个元素
STACK::STACK(int m):elems(new int[m]),max(m),pos(0){
    return;
}

//用栈s拷贝初始化栈
STACK::STACK(const STACK&s):elems(new int[s.size()]),max(s.size()),pos(0){
    for(int i=0;i<s;i++){
        *this<<(s[i]);
    }
    return;
}

//返回栈的最大元素个数max
int STACK::size() const{
    return max;
}

//返回栈的实际元素个数pos
STACK::operator int() const{
    return pos;
}

//取下标x处的栈元素
int STACK::operator[ ](int x) const{
    return elems[x];
}

//将e入栈,并返回栈
STACK& STACK::operator<<(int e){
    elems[pos]=e;
    pos++;
    return *this;
}

//出栈到e,并返回栈
STACK& STACK::operator>>(int &e){
    e=elems[pos-1];
    pos--;
    return *this;
}

//赋s给栈,并返回被赋值的栈
STACK& STACK::operator=(const STACK&s){
    pos=0;
    *(int*)(&max)=s.size();
    *(int**)(&elems)=new int[s.size()];
    for(int i=0;i<s;i++){
        (*this)<<(s[i]);
    }
    return *this;
}

//打印栈
void STACK::print() const{
    for(int i=0;i<pos;i++){
        cout<<"  "<<elems[i];
    }
    return;
}

//销毁栈
STACK::~STACK( ){
    free(elems);
}
