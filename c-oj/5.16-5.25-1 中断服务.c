#include<stdio.h>

struct ISR_BITS{
    unsigned int bit0: 1;
    unsigned int bit1: 1;
    unsigned int bit2: 1;
    unsigned int bit3: 1;
    unsigned int bit4: 1;
    unsigned int bit5: 1;
    unsigned int bit6: 1;
    unsigned int bit7: 1;
    unsigned int rsv : 8;
};

union ISR_REG{
    unsigned short all;
    struct ISR_BITS bit;
};

void(*p_isr[8])(void);

void isr0(void){
    printf("The Interrupt Service Routine isr0 is called!\n");
}
void isr1(void){
    printf("The Interrupt Service Routine isr1 is called!\n");
}
void isr2(void){
    printf("The Interrupt Service Routine isr2 is called!\n");
}
void isr3(void){
    printf("The Interrupt Service Routine isr3 is called!\n");
}
void isr4(void){
    printf("The Interrupt Service Routine isr4 is called!\n");
}
void isr5(void){
    printf("The Interrupt Service Routine isr5 is called!\n");
}
void isr6(void){
    printf("The Interrupt Service Routine isr6 is called!\n");
}
void isr7(void){
    printf("The Interrupt Service Routine isr7 is called!\n");
}

int main(void)
{
    p_isr[0]=isr0;
    p_isr[1]=isr1;
    p_isr[2]=isr2;
    p_isr[3]=isr3;
    p_isr[4]=isr4;
    p_isr[5]=isr5;
    p_isr[6]=isr6;
    p_isr[7]=isr7;

    union ISR_REG isr_reg;
    unsigned short N,i;
    scanf("%d",&N);

    for(i=0;i<N;i++){
        scanf("%u",&isr_reg.all);
        printf("%u:\n",isr_reg.all);
        if(isr_reg.bit.bit0) p_isr[0]();
        if(isr_reg.bit.bit1) p_isr[1]();
        if(isr_reg.bit.bit2) p_isr[2]();
        if(isr_reg.bit.bit3) p_isr[3]();
        if(isr_reg.bit.bit4) p_isr[4]();
        if(isr_reg.bit.bit5) p_isr[5]();
        if(isr_reg.bit.bit6) p_isr[6]();
        if(isr_reg.bit.bit7) p_isr[7]();
        printf("\n");
    }

}
