/*
 * main.c for microAptiv_UP MIPS core running on Nexys4DDR
 * Prints \n\rMIPSfpga\n\r out via UART.
 * Default baudrate 115200,8n1.
 * Also display a shifting 0xf on the LEDs
 */

#include "fpga.h"

#define inline_assembly()  asm("ori $0, $0, 0x1234")

#define CLK_FREQ 50000000
#define IO_SW		   0xB0600008

#define UART_BASE 0xB0401000	//With 1000 offset that axi_uart16550 has
#define rbr		0*4
#define ier		1*4
#define fcr		2*4
#define lcr		3*4
#define mcr		4*4
#define lsr		5*4
#define msr		6*4
#define scr		7*4

#define thr		rbr
#define iir		fcr
#define dll		rbr
#define dlm		ier

#define PWM_BASE 0xB0C00000

#define IS_UART_INTR (1<<15)
#define IS_PWM_INTR  (1<<14)
#define IS_TIMER_INTR (1<<30)

void delay();
void uart_outbyte(char c);
char uart_inbyte(void);
void uart_print(const char *ptr);
void ADT7420_SetTemp(int);

extern char *reverse(char *s);
extern char *my_itoa(int n);

extern void delay_ms(unsigned int ms_count);

// The following is for ADT7420
#include "i2c.h"
#include "ADT7420.h"

/*****************************************************************************/
/********************** Variable Definitions *********************************/
/*****************************************************************************/
volatile int rxData = 0;
volatile unsigned int data_received = 0x0;
int limitTemp = 0;


//------------------
// main()
//------------------
int main() {
	volatile unsigned int pushbutton, count = 0xF;
	volatile unsigned int j = 1,i = 1;
	unsigned int value = 0;

	*WRITE_IO(UART_BASE + lcr) = 0x00000080; // LCR[7]  is 1
	delay();
	*WRITE_IO(UART_BASE + dll) = 27; // DLL msb. 115200 at 50MHz. Formula is Clk/16/baudrate. From axi_uart manual.
	delay();
	*WRITE_IO(UART_BASE + dlm) = 0x00000000; // DLL lsb.
	delay();
	*WRITE_IO(UART_BASE + lcr) = 0x00000003; // LCR register. 8n1 parity disabled
	delay();
	*WRITE_IO(UART_BASE + ier) = 0x00000000; // IER register. disable interrupts
	delay();

	*WRITE_IO(UART_BASE + ier) = 0x00000001; // IER register. Enables Receiver Line Status and Received Data Interrupts
	delay();

	// Begin ADT7420 test
	// Initialize ADT7420 Device
	ADT7420_Init();

	// Display Main Menu on UART
	ADT7420_DisplayMainMenu();

	while(rxData != 'q')
    {
		// uart_print("\n\r");
		// uart_print("rxData=");
		// uart_print(my_itoa(rxData));
		// uart_print("\n\r");
		uart_print("rx=");
		uart_print(my_itoa(rxData));
		uart_print("e");

		// uart_print("button key = ");
		// uart_print(my_itoa(pushbutton));
		// uart_print("\n\r");

		pushbutton = (volatile unsigned int)*READ_IO(IO_SW);
		int sum = 0;
		int cur_sum = 0;
		for(cur_sum = 0; cur_sum < 8; cur_sum++){
			if (pushbutton & (0x8000 >> cur_sum)){
				continue;
			}
			else{
				sum += 1;
			}
		}

		// uart_print("fan level = ");
		// uart_print(my_itoa(sum));
		// uart_print("\n\r");
		uart_print("f=");
		uart_print(my_itoa(sum));
		uart_print("e");

		int level = 0;
		for(cur_sum = 0; cur_sum < sum; cur_sum++){
			level = level | 0x0001<<cur_sum;
		}
		*WRITE_IO(IO_LEDR) = level;//door open, and set fan gear to 1
		// delay();

		limitTemp = pushbutton & 0x00ff;
		// uart_print("limitTemp = ");
		// uart_print(my_itoa(limitTemp));
		// uart_print("\n\r");
		uart_print("l=");
		uart_print(my_itoa(limitTemp));
		uart_print("e");
		// delay();

		Display_Temp(ADT7420_ReadTemp());
		int temp = ADT7420_ReadTemp();
		if(temp >= (limitTemp)*16){
			*WRITE_IO(PWM_BASE) = 0 * 110000;//decrease power
		}
		else if(temp >= (limitTemp-1)*16){
			*WRITE_IO(PWM_BASE) = 1 * 110000;//adjust level 1
		}
		else if(temp >= (limitTemp-2)*16){
			*WRITE_IO(PWM_BASE) = 2 * 110000;//adjust level 2
		}
		else if(temp >= (limitTemp-3)*16){
			*WRITE_IO(PWM_BASE) = 3 * 110000;//adjust level 3
		}
		else if(temp >= (limitTemp-4)*16){
			*WRITE_IO(PWM_BASE) = 4 * 110000;//adjust level 4
		}
		else if(temp >= (limitTemp-5)*16){
			*WRITE_IO(PWM_BASE) = 5 * 110000;//adjust level 5
		}
		else if(temp >= (limitTemp-6)*16){
			*WRITE_IO(PWM_BASE) = 6 * 110000;//adjust level 6
		}
		else if(temp >= (limitTemp-7)*16){
			*WRITE_IO(PWM_BASE) = 7 * 110000;//adjust level 7
		}
		else if(temp >= (limitTemp-8)*16){
			*WRITE_IO(PWM_BASE) = 8 * 110000;//adjust level 8
		}
		else{
			*WRITE_IO(PWM_BASE) = 9 * 110000;//increase power
		}
		delay();

		switch(rxData)
    	{
    	case 't':
    		Display_Temp(ADT7420_ReadTemp());
    		if(ADT7420_ReadTemp() > limitTemp*16){
    			*WRITE_IO(PWM_BASE) = 0 * 110000;//decrease power
    			delay();
    		}
    		else{
    			*WRITE_IO(PWM_BASE) = 9 * 110000;//increase power
    			delay();
    		}
    		break;
    	case 'r':
    		ADT7420_SetResolution();
    		break;
    	case 'h':
    		ADT7420_DisplaySetTHighMenu();
    		break;
    	case 'l':
    		ADT7420_DisplaySetTLowMenu();
    		break;
    	case 'c':
    		ADT7420_DisplaySetTCritMenu();
    		break;
        case 'y':
        	ADT7420_DisplaySetTHystMenu();
    		break;
    	case 'f':
    		ADT7420_DisplaySetFaultQueueMenu();
    		break;
    	case 's':
			ADT7420_DisplaySettings();
			break;
    	case 'm':
    		ADT7420_DisplayMenu();
    		break;
    	case 'p':
			uart_print("\n\rinput a temp please: ");
			i = 2;
			limitTemp = 0;
    		while(i--){
    			value = uart_inbyte();
    			if(value>='0'&&value<='9'){
					//read the temperature(input)
    				limitTemp = limitTemp * 10 + (value-'0');
    			}
				else{
					break;
				}
    		}

			delay( );

			uart_print("\n\ruart_temp_setted: ");
			uart_print(my_itoa(limitTemp));
			uart_print("\n\r");

			rxData = 'm';

    		break;


    	case 0:
    		break;
    	default:
    		uart_print("\n\rWrong option! Please select one of the options below.");
    		ADT7420_DisplayMenu();
    		break;
    	}

    }

	uart_print("Exiting ADT7420 test application!\n\r");

	return 0;
}

void delay() {
	volatile unsigned int j;

	for (j = 0; j < (10000); j++) ;	// delay
}

void uart_outbyte(char c) {
	*WRITE_IO(UART_BASE + thr) = (unsigned int) c;
	delay( );
}

char uart_inbyte(void) {
	unsigned int RecievedByte;

	while(!((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001));

	RecievedByte = *READ_IO(UART_BASE + rbr);

	return (char)RecievedByte;
}

void uart_print(const char *ptr)
{
	while (*ptr) {
		uart_outbyte (*ptr);
		ptr++;
	}
}

void _mips_handle_irq(void* ctx, int reason)
{
	asm volatile ("mtc0	$0, $11");
	uart_print(my_itoa(reason));
	return;

	*WRITE_IO(IO_LEDR) = 0xF00F;  // Display 0xFFFF on LEDs to indicate receive data from uart

	uart_print(my_itoa(reason));

	if(reason & IS_TIMER_INTR) {
		// write C0_Compare = $11
		uart_print("timer_intr");
		asm volatile ("mtc0	$0, $11");
		return;
	}

	if((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001)
		rxData = *READ_IO(UART_BASE + rbr);

	*WRITE_IO(IO_LEDR) = 0x0;

	return;



	// volatile unsigned int period;
	// //volatile unsigned int rxData;
	//
	// *WRITE_IO(IO_LEDR) = 0xF00F;  // Display 0xF00F on LEDs to indicate enter the interrupt
	// data_received = 0x0;
	//
	// if(reason && IS_TIMER_INTR) {
	// 	//write C0_Compare = $11
	// 	asm volatile ("mtc0	$0, $11");
	//
	// 	asm volatile ("li $9, 0x1");
	// 	//write C0_COUNT = $9
	// 	asm volatile ("mtc0 $9, $9");
	// 	return;
	// }
	//
	// if(reason & IS_UART_INTR) {
	// 	/* Read an input value from the console. */
	// 	uart_print("\n\rinter_rx!");
	// 	if((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001)
	// 		rxData = *READ_IO(UART_BASE + rbr);
	// 	// rxData = *READ_IO(UART_BASE + rbr);
	// 	uart_print("\n\rinter_uart_rx: ");
	// 	uart_print(my_itoa(rxData));
	// 	data_received = 0x1;
	// 	return;
	// }
	//
	// if(reason && IS_PWM_INTR) {
	// 	*WRITE_IO(PWM_BASE) = 0x0;
	// 	return;
	// }
	//
	// *WRITE_IO(IO_LEDR) = 0x0FF0;
	// uart_print("Other interrupts occurred!\n\r");
	// uart_print(my_itoa(reason));
	//
	// return;
}
