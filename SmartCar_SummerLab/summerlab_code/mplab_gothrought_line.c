//////////////////////////////////////////////////////////////////////
//                                                                  //
//      AUTHOR:     Your Name                                       //
//      DATE:       xx/07/09                                        //
//      REVISION:   1.0                                             //
//      DEVICE:     PIC18F2525                                      //
//      FILENAME:   LED_ON.c                                        //
//                                                                  //
/////// DESCRIPTION //////////////////////////////////////////////////
// Turn on LED on RA1 on SW1 press                                  //
//////////////////////////////////////////////////////////////////////

#include <p18F2525.h>
#include <pwm.h>
#include <timers.h>
#include <adc.h>

//********** Configuration bits **********//
#pragma config OSC 	= INTIO7 	//Internal oscillator, output to pin 10
#pragma config FCMEN 	= OFF 	//Fail-safe clock monitor disabled
#pragma config IESO 	= OFF 	//Int.-ext. oscillator switch over disabled
#pragma config PWRT 	= OFF 	//Power-up timer disabled
#pragma config BOREN 	= OFF 	//Brown-out reset disabled
#pragma config WDT 	= OFF 	//Watch-dog timer disabled
#pragma config MCLRE 	= ON 	//Master clear enabled
#pragma config LPT1OSC 	= OFF 	//T1 oscillator disabled
#pragma config PBADEN 	= OFF 	//Port B analogue-digital disabled on reset
#pragma config STVREN 	= OFF 	//Stack overflow reset disabled
#pragma config LVP 	= OFF 	//Low voltage programming disabled
#pragma config XINST 	= OFF 	//XINST disabled
#pragma config DEBUG 	= OFF 	//Background debugger disabled

#pragma config CP0 	= OFF 	//Code protection disabled
#pragma config CP1 	= OFF
#pragma config CP2 	= OFF

#pragma config WRT0 	= OFF 	//Write protection disabled
#pragma config WRT1 	= OFF
#pragma config WRT2 	= OFF

#pragma config WRTB 	= OFF	//Boot block write protection
#pragma config WRTC 	= OFF	//Config reg write protection
#pragma config WRTD 	= OFF	//Data EEPROM write protection

#pragma config EBTR0 	= OFF	//Table read write protection
#pragma config EBTR1 	= OFF
#pragma config EBTR2 	= OFF

#pragma config EBTRB 	= OFF	//Boot block table write protection

#pragma config CPB 	= OFF 	//Boot block code protection disabled
#pragma config CPD 	= OFF 	//Data EEPROM code protection disabled

#define MOVE LATCbits.LATC1
#define BACK LATCbits.LATC3
#define LEFT LATCbits.LATC5
#define RIGHT LATCbits.LATC7


#define SW1 PORTBbits.RB0  //move
#define SW2 PORTBbits.RB1  //back
#define SW3 PORTBbits.RB2  //left
#define SW4 PORTBbits.RB3  //right

#define ON 1
#define OFF 0

#pragma code

int result_1;
int result_2;

void main(void)
{
	TRISA=0x03;
	TRISB=0x0F;
	TRISC=0x00;

	MOVE=OFF;
	BACK=ON;
	LEFT=OFF;
	RIGHT=OFF;

	// set Timer
	OpenTimer2( TIMER_INT_ON & T2_PS_1_1 & T2_POST_1_8 );
	// set PWM
	OpenPWM2(250);

	//set ADC
	SetChanADC( ADC_CH0 );
	OpenADC(ADC_FOSC_32      &
 			ADC_RIGHT_JUST   &
 			ADC_12_TAD,

			ADC_CH0          &
 			ADC_REF_VDD_VSS  &
 			ADC_INT_OFF,

			ADC_2ANA
	);
	Delay10TCYx( 5 );     // Delay for 50TCY
	ConvertADC();
	result_1=0;
	while(BusyADC());
	result_1 = ReadADC();
	CloseADC();

	//set ADC
	SetChanADC( ADC_CH1 );
	OpenADC(ADC_FOSC_32      &
 			ADC_RIGHT_JUST   &
 			ADC_12_TAD,

			ADC_CH1          &
 			ADC_REF_VDD_VSS  &
 			ADC_INT_OFF,

			ADC_2ANA
	);
	Delay10TCYx( 5 );     // Delay for 50TCY
	ConvertADC();
	result_2=0;
	while(BusyADC());
	result_2 = ReadADC();
	CloseADC();

	if(result_1>=1 && result_2>=1){// white
		SetDCPWM2(1023);
	}
	else if (result_1==0 && result_2>=1){// left touch black
		SetDCPWM2(1023);
		LEFT=ON;
		Delay1KTCYx(125);
	}
	else if(result_1>=1 && result_2==0){//right touch black
		SetDCPWM2(1023);
		RIGHT=ON;
		LEFT=ON;
		Delay1KTCYx(125);
	}
	else{//
		SetDCPWM2(1023);
	}

}
