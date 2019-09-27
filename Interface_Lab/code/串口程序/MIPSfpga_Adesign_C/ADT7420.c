/***************************************************************************//**
*   @file   ADT7420.c
*   @brief  ADT7420 Driver Files for MicroBlaze Processor.
*   @author ATofan (alexandru.tofan@analog.com)
********************************************************************************
* Copyright 2012(c) Analog Devices, Inc.
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*  - Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  - Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*  - Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*  - The use of this software may or may not infringe the patent rights
*    of one or more patent holders.  This license does not release you
*    from the requirement that you obtain separate licenses from these
*    patent holders to use this software.
*  - Use of the software either in source or binary form, must be run
*    on or directly connected to an Analog Devices Inc. component.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
********************************************************************************
*   SVN Revision: $WCREV$
*******************************************************************************/

/*****************************************************************************/
/***************************** Include Files *********************************/
/*****************************************************************************/
#include "i2c.h"
#include "ADT7420.h"

extern void uart_print(const char *ptr);
extern char uart_inbyte(void);

extern void intc_disable_interrupts( );
extern void intc_enable_interrupts( );


/*****************************************************************************/
/********************** Variable Definitions *********************************/
/*****************************************************************************/
extern volatile int rxData;
char valid  = 0;
int  TUpper = 0x1FFF;


//反转字符串  
char *reverse(char *s)  
{  
    char temp;  
    char *p = s;    //p指向s的头部  
    char *q = s;    //q指向s的尾部  
    while(*q)  
        ++q;  
    q--;  
  
    //交换移动指针，直到p和q交叉  
    while(q > p)  
    {  
        temp = *p;  
        *p++ = *q;  
        *q-- = temp;  
    }  
    return s;  
}  
  
/* 
 * 功能：整数转换为字符串 
 * char s[] 的作用是存储整数的每一位 
 */  
char *my_itoa(int n)  
{  
    int i = 0,isNegative = 0;  
    static char s[100];      //必须为static变量，或者是全局变量  
    if((isNegative = n) < 0) //如果是负数，先转为正数  
    {  
        n = -n;  
    }  
    do      //从各位开始变为字符，直到最高位，最后应该反转  
    {  
        s[i++] = n%10 + '0';  
        n = n/10;  
    }while(n > 0);  
  
    if(isNegative < 0)   //如果是负数，补上负号  
    {  
        s[i++] = '-';  
    }  
    s[i] = '\0';    //最后加上字符串结束符  
	
    return reverse(s);    
}  


/******************************************************************************
* @brief Performs Software Reset for ADT7420 and sets Alert Mode as Comparator.
*
* @param  None.
*
* @return None.
******************************************************************************/
void ADT7420_Init(void)
{
	unsigned char txBuffer[1] = { 0x00 };
	
	if(I2C_Init(IIC_BASEADDR, ADT7420_IIC_ADDR))
    {
        uart_print("AXI IIC initialized OK!\n\r");
    }
    else
    {
        uart_print("AXI IIC Error!\n\r");
    }
	
	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, SOFT_RST_REG, 1, txBuffer);

	SetAlertModeComparator();
}
/******************************************************************************
* @brief Sets Alert Mode as Comparator.
*
* @param None.
*
* @return None.
******************************************************************************/
void SetAlertModeComparator(void)
{
	unsigned char txBuffer[1] = {0x00};

	txBuffer[0] = 1 << INT_CT;

	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, txBuffer);
}

/******************************************************************************
* @brief Returns value from Configuration Register.
*
* @param None.
*
* @return rxBuffer[0] & 0x7F - all bits in the Configuration Register, except RESOLUTION bit
******************************************************************************/
char ADT7420_ReadConfigReg(void)
{
	unsigned char rxBuffer[1] = {0x00};

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, rxBuffer);

	return(rxBuffer[0] & 0x7F);
}

/******************************************************************************
* @brief Displays Revision ID and Manufacturer ID.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintID(void)
{
	unsigned char rxBuffer[1] = {0x00};

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, ID_REG, 1, rxBuffer);

	uart_print("Revision ID = ");
	uart_print(my_itoa(rxBuffer[0] & REVISION_ID));
	uart_print("\n\r");
	uart_print("Manufacture ID = ");
	uart_print(my_itoa((rxBuffer[0] & MANUFACTURE_ID) >> 3));
	uart_print("\n\r");
	uart_print("-----------------------------------------\n\r");
}

/******************************************************************************
* @brief Displays Main Menu.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplayMainMenu(void)
{
	uart_print("\n\rADT7420 Demo Program \n\r");

	ADT7420_PrintID();

	uart_print("Available options: \n\r");
	uart_print("	[t] Read Temperature\n\r");
	uart_print("	[r] Set Resolution\n\r");
	uart_print("	[h] Set THigh\n\r");
	uart_print("	[l] Set TLow\n\r");
	uart_print("	[c] Set TCrit\n\r");
	uart_print("	[y] Set THyst\n\r");
	uart_print("	[f] Set Fault Queue\n\r");
	uart_print("	[s] Display Settings \n\r");
	uart_print("	[m] Stop the program and display this menu\n\r");
	uart_print("	[p] Set upper critical temperature\n\r");
	uart_print("	[g] Set status of door\n\r");
	uart_print("\n\r");
	uart_print("Press key to select desired option\n\r");
	uart_print("Press [q] to exit the application\n\r");
}

/******************************************************************************
* @brief Displays Menu.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplayMenu(void)
{
	uart_print("\n\rAvailable options: \n\r");
	uart_print("	[t] Read Temperature\n\r");
	uart_print("	[r] Set Resolution\n\r");
	uart_print("	[h] Set THigh\n\r");
	uart_print("	[l] Set TLow\n\r");
	uart_print("	[c] Set TCrit\n\r");
	uart_print("	[y] Set THyst\n\r");
	uart_print("	[f] Set Fault Queue\n\r");
	uart_print("	[s] Display Settings \n\r");
	uart_print("	[m] Stop the program and display this menu\n\r");
	uart_print("	[p] Set upper critical temperature\n\r");
	uart_print("	[g] Set status of door\n\r");
	rxData = 0;
}

/******************************************************************************
* @brief Returns resolution of ADT7420 internal ADC.
*
* @param display - 0 -> resolution is displayed on UART
*				 - 1 -> resolution is not displayed on UART.
*
* @return (rxBuffer[0] & (1 << RESOLUTION)) - bit 7 of CONFIGURATION REGISTER
* 				 - 0 -> resolution is 13 bits
* 				 - 1 -> resolution is 16 bits.
******************************************************************************/
unsigned char ADT7420_GetResolution(char display)
{
	unsigned char rxBuffer[2] = {0x00, 0x00};
	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, rxBuffer);

	if(display == 1)
	{
		if((rxBuffer[0] & (1 << RESOLUTION)) == 0)
		{
			uart_print("Resolution is 13 bits (0.0625 C/LSB)\n\r");
		}
		else
		{
			uart_print("Resolution is 16 bits (0.0078 C/LSB)\n\r");
		}
	}

	return (rxBuffer[0] & (1 << RESOLUTION));
}

/******************************************************************************
* @brief Displays Set Resolution Menu.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplayResolutionMenu(void)
{
	uart_print("\n\r>Set Resolution Menu\n\r");
	uart_print("-----------------------------------------\n\r");
	uart_print("Possible resolutions are:\n\r");
	uart_print("	1. 13 bits (0.0625 C/LSB):\n\r");
	uart_print("	2. 16 bits (0.0078 C/LSB):\n\r");
}


/******************************************************************************
* @brief Sets and displays resolution for ADC of ADT7420
*
* @param None
*
* @return None
******************************************************************************/
void ADT7420_SetResolution(void)
{
	unsigned char txBuffer[1] = { 0x00 };
	char          rx          = 0;

	ADT7420_DisplayResolutionMenu();

	// Check if data is available on the UART
	// Store and display received data
	rx = uart_inbyte();

	switch (rx)
		{
		case '1' :
			txBuffer[0] = (0 << RESOLUTION) | ADT7420_ReadConfigReg() ; // so as not to change other configuration parameters
			uart_print("Resolution is 13 bits (0.0625 C/LSB)\n\r");
			TUpper = 0x1FFF;
			rxData = 'm';
			uart_print("\n\r>Returning to Main Menu...\n\r");
			break;
		case '2' :
			txBuffer[0] = (1 << RESOLUTION) | ADT7420_ReadConfigReg();
			uart_print("Resolution is 16 bits (0.0078 C/LSB)\n\r");
			TUpper = 0xFFFF;
			rxData = 'm';
			uart_print("\n\r>Returning to Main Menu...\n\r");
			break;
		default:
			uart_print("Wrong option!\n\r");
			break;
		}

	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, txBuffer);
}

/******************************************************************************
* @brief Reads data from the Temperature MSB and LSB registers of ADT7420.
*
* @param None.
*
* @return data - value read from the Temperature MSB and LSB registers.
******************************************************************************/
int ADT7420_ReadTemp(void)
{
	unsigned char rxBuffer[2]  = {0x00,0x00};
	int           data         = 0;

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, TEMP_REG, 2, rxBuffer);

	if(ADT7420_GetResolution(0) == 0)
	{
		data = (rxBuffer[0] << 5) | (rxBuffer[1] >> 3);
	}
	else
	{
		data = (rxBuffer[0] << 8) | (rxBuffer[1]);
	}

	return (data);
}

/******************************************************************************
* @brief Displays temperature data in degrees Celsius.
*
* @param data - value read from the Temperature MSB and LSB registers.
*
* @return None.
******************************************************************************/
void Display_Temp(short int data)
{
	int     value     = data;

	// converting data for display
	// if(ADT7420_GetResolution(0) == 0)
	// {
	// 	if(data&0x1000)
	// 	{
	// 		data = data	| 0xffffe000;
	// 	}
	// 	value = data ;
	// }
	// else
	// {
	// 	value = data ;
	// }

	if(value >= 0)
	{
	    uart_print("T = ");
		uart_print(my_itoa(value));
		uart_print(".00 C\n\r");
	}
	else
	{
		value = value * (-1);
		uart_print("T = -");
		uart_print(my_itoa(value));
		uart_print(".00 C\n\r");
	}
}

/******************************************************************************
* @brief Reads data from the UART console.
*
* @param None.
*
* @return value -> data converted to hex value
* 			0 	-> characters read are not hex values.
******************************************************************************/
int ADT7420_ConsoleRead(void)
{
	char rx    = 0;
	char c[4]  = "0000";
	char *c_ptr;
	int  i     = 0;
	char cnt   = 0;
	int  value = 0;

	cnt   = 0;
	i     = 0;
	valid = 0;
	value = 0;
	c_ptr = c;

	while(i < 6)
	{
		// Check if data is available on the UART
		// Store and display received data
		rx = uart_inbyte();
		uart_print(my_itoa(rx));
		
		// Check if pressed key is [Enter]
		if(rx == 0x0D)
		{
			i = 5;
		}
		else if(rx == 0x0A)
		{
			i = 5;
		}
		else if(((rx > 0x00)&&(rx < 0x30))|| // Not 0 - 9
				((rx > 0x39)&&(rx < 0x41))|| // Not A - F
				((rx > 0x46)&&(rx < 0x61))|| // Not a - f
				(rx > 0x66))
		{
			uart_print("\n\rCharacters entered must be HEX values (0 to 9 and A B C D E F)\n\r");
			i = 6;
			valid = 0;
		}
		else
		{
			*c_ptr++ = rx;
			cnt = cnt + 1;
			valid = 1;
		}
		if(cnt == 4)
		{
			i = 6;
		}
		i++;
	}

	// Translate from ASCII to hex
	for(i = 0; i < cnt; i++)
	{
		if(c[i] > 0x60)
		{
			value = value * 16 + (c[i] - 0x57);
		}
		else if(c[i] > 0x39)
		{
			value = value * 16 + (c[i] - 0x37);
		}
		else
		{
			value = value * 16 + (c[i] - 0x30);
		}
	}

	if(valid == 1)
	{
		return value;
	}
	else
	{
		return 0;
	}
}

/******************************************************************************
* @brief Menu for setting data in THigh register.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplaySetTHighMenu(void)
{
	int THigh = 0;

	uart_print("\n\r>Set THigh Menu\n\r");
	uart_print("-----------------------------------------\n\r");

	uart_print("\n\rPlease enter a value between 0x0000 and 0x003C");

	THigh = ADT7420_ConsoleRead();

	while(!((THigh>=0x0000)&(THigh<=0x003C)))
	{
		uart_print("\n\rValue for THigh must be in the range 0x0000 and 0x003C\n\r");
		uart_print("Please enter a valid value: 0x");
		THigh = ADT7420_ConsoleRead();
	}

	if(valid == 1)
	{
		ADT7420_SetTHigh(THigh);
		rxData = 'm';
		uart_print("\n\r\n\r>Returning to Main Menu...\n\r");
	}
}

/******************************************************************************
* @brief Sets value of THigh register.
*
* @param THigh - value to be placed in the register.
*
* @return None.
******************************************************************************/
void ADT7420_SetTHigh(int THigh)
{
	unsigned char txBuffer[2] = {0x00, 0x00};

	if(ADT7420_GetResolution(0) == 0)
	{
		txBuffer[0] = (THigh & 0x1FE0) >> 5;
		txBuffer[1] = (THigh & 0x001F) << 3;
	}
	else
	{
		txBuffer[0] = (THigh & 0xFF00) >> 8;
		txBuffer[1] = THigh & 0x00FF;
	}

	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, TH_SETP_MSB, 2, txBuffer);
}

/******************************************************************************
* @brief Displays value of THigh setpoint.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintTHigh(void)
{
	unsigned char rxBuffer[2] = {0x00, 0x00};
	int           val         = 0;

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, TH_SETP_MSB, 2, rxBuffer);

	if(ADT7420_GetResolution(0) == 0)
		val = ( rxBuffer[0] << 5 ) | ( rxBuffer[1] >> 3);
	else
		val = (rxBuffer[0] << 8) | rxBuffer[1];

	uart_print("THigh Setpoint ");
	Display_Temp(val);
}

/******************************************************************************
* @brief Menu for setting data in TLow register.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplaySetTLowMenu(void)
{
	int TLow = 0;

	uart_print("\n\r>Set TLow Menu\n\r");
	uart_print("-----------------------------------------\n\r");
	uart_print("\n\rPlease enter a value between 0x0000 and 0x000A");

	TLow = ADT7420_ConsoleRead();

	while(!((TLow>=0x0000)&(TLow<=0x000A)))
	{
		uart_print("\n\rValue for TLow must be in the range 0x0000 and 0x000A\n\r");
		uart_print("Please enter a valid value: 0x");
		TLow = ADT7420_ConsoleRead();
	}

	if(valid == 1)
	{
		ADT7420_SetTLow(TLow);
		rxData = 'm';
		uart_print("\n\r\n\r>Returning to Main Menu...\n\r");
	}
}

/******************************************************************************
* @brief Sets value of  TLow register.
*
* @param TLow - value to be placed in the register.
*
* @return None.
******************************************************************************/
void ADT7420_SetTLow(int TLow)
{
	unsigned char txBuffer[2] = {0x00, 0x00};

	if(ADT7420_GetResolution(0) == 0)
	{
		txBuffer[0] = (TLow & 0x1FE0) >> 5;
		txBuffer[1] = (TLow & 0x001F) << 3;
	}
	else
	{
		txBuffer[0] = (TLow & 0xFF00) >> 8;
		txBuffer[1] = TLow & 0x00FF;
	}

	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, TL_SETP_MSB, 2, txBuffer);
}

/******************************************************************************
* @brief Displays value of TLow setpoint.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintTLow(void)
{
	unsigned char rxBuffer[2] = {0x00, 0x00};
	int           val         = 0;

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, TL_SETP_MSB, 2, rxBuffer);

	if(ADT7420_GetResolution(0) == 0)
	{
		val = ( rxBuffer[0] << 5 ) | ( rxBuffer[1] >> 3);
	}
	else
	{
		val = (rxBuffer[0] << 8) | rxBuffer[1];
	}

	uart_print("TLow Setpoint ");
	Display_Temp(val);
}

/******************************************************************************
* @brief Sets value of  TCrit register.
*
* @param TCrit - value to be placed in the register.
*
* @return None.
******************************************************************************/
void ADT7420_SetTCrit(int TCrit)
{
	unsigned char txBuffer[2] = {0x00, 0x00};
	if(ADT7420_GetResolution(0) == 0)
	{
		txBuffer[0] = (TCrit & 0x1FE0) >> 5;
		txBuffer[1] = (TCrit & 0x001F) << 3;
	}
	else
	{
		txBuffer[0] = (TCrit & 0xFF00) >> 8;
		txBuffer[1] = TCrit & 0x00FF;
	}

	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, TCRIT_SETP_MSB, 2, txBuffer);
}

/******************************************************************************
* @brief Menu for setting data in TCrit register.
*
* @param None.
*
* @return None.
******************************************************************************/

void ADT7420_DisplaySetTCritMenu(void)
{
	int TCrit = 0;

	uart_print("\n\r>Set TCrit Menu\n\r");
	uart_print("-----------------------------------------\n\r");
	uart_print("\n\rPlease enter a value between 0x0000 and 0x0064");

	TCrit = ADT7420_ConsoleRead();

	while(!((TCrit>=0x0000)&(TCrit<=0x0064)))
	{
		uart_print("\n\rValue for TCrit must be in the range 0x0000 and 0x0064\n\r");
		uart_print("Please enter a valid value: 0x");
		TCrit = ADT7420_ConsoleRead();
	}

	if(valid == 1)
	{
		ADT7420_SetTCrit(TCrit);
		rxData = 'm';
		uart_print("\n\r\n\r>Returning to Main Menu...\n\r");
	}
}

/******************************************************************************
* @brief Displays value of TCrit setpoint.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintTCrit(void)
{
	unsigned char rxBuffer[2] = {0x00, 0x00};
	int           val         = 0;

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, TCRIT_SETP_MSB, 2, rxBuffer);

	if(ADT7420_GetResolution(0) == 0)
	{
		val = ( rxBuffer[0] << 5 ) | ( rxBuffer[1] >> 3);
	}
	else
	{
		val = (rxBuffer[0] << 8) | rxBuffer[1];
	}

	uart_print("TCrit Setpoint ");
	Display_Temp(val);
}

/******************************************************************************
* @brief Menu for setting data in THyst register.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplaySetTHystMenu(void)
{
	int THyst = 0;

	uart_print("\n\r>Set THyst Menu\n\r");
	uart_print("-----------------------------------------\n\r");
	uart_print("Enter a value from 0x0000 to 0x000F: 0x");

	THyst = ADT7420_ConsoleRead();

	while(!((THyst>=0)&(THyst<16)))
	{
		uart_print("\n\rValue for THyst must be in the range 0 C to 15 C\n\r");
		uart_print("Please enter a valid value: 0x");
		THyst = ADT7420_ConsoleRead();
	}

	if(valid == 1)
	{
		ADT7420_SetHysteresis(THyst);
		rxData = 'm';
		uart_print("\n\r\n\r>Returning to Main Menu...\n\r");
	}
}

/******************************************************************************
* @brief Sets value of THyst register.
*
* @param THyst - value from 0x0000 to 0x000F to be placed in the register.
*
* @return None.
******************************************************************************/
void ADT7420_SetHysteresis(int THyst)
{
	unsigned char txBuffer[1] = {0x00};
	txBuffer[0] = THyst & 0x0F;
	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, T_HYST_SETP, 1, txBuffer);
}

/******************************************************************************
* @brief Displays value of THyst.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintHysteresis(void)
{
	unsigned char rxBuffer[2] = { 0x00 };
	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, T_HYST_SETP, 1, rxBuffer);
	uart_print("THyst Setpoint T = ");
	uart_print(my_itoa(rxBuffer[0]));
	uart_print(" C\n\r");
}

/******************************************************************************
* @brief Menu for setting Fault Queue.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplaySetFaultQueueMenu(void)
{
	unsigned char txBuffer[1] = { 0x00 };
	char          rx          = 0;

	uart_print("\n\r>Fault Queue Menu\n\r");
	uart_print("-----------------------------------------\n\r");
	uart_print("Number of fault queues:\n\r");
	uart_print("	1. 1 fault\n\r");
	uart_print("	2. 2 faults\n\r");
	uart_print("	3. 3 faults\n\r");
	uart_print("	4. 4 faults\n\r");

	// Check if data is available on the UART
	// Store and display received data
	rx = uart_inbyte( );

	switch (rx)
	{
	case '1' :
			txBuffer[0] = 0x00 << FAULT_QUEUE;
			uart_print("1 fault queue\n\r");
			rxData = 'm';
			uart_print("\n\r>Returning to Main Menu...\n\r");
			break;
		case '2' :
			txBuffer[0] = 0x01 << FAULT_QUEUE;
			uart_print("2 fault queues\n\r");
			rxData = 'm';
			uart_print("\n\r>Returning to Main Menu...\n\r");
			break;
		case '3' :
			txBuffer[0] = 0x02 << FAULT_QUEUE;
			uart_print("3 fault queues\n\r");
			rxData = 'm';
			uart_print("\n\r>Returning to Main Menu...\n\r");
			break;
		case '4' :
			txBuffer[0] = 0x03 << FAULT_QUEUE;
			uart_print("4 fault queues\n\r");
			rxData = 'm';
			uart_print("\n\r>Returning to Main Menu...\n\r");
			break;
		default:
			uart_print("Wrong option!\n\r");
			break;
	}
	I2C_Write(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, txBuffer);
}

/******************************************************************************
* @brief Displays value of Fault Queues.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintFaultQueue(void)
{
	unsigned char rxBuffer[1] = { 0x00 };
	char          rx          = 0;

	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, rxBuffer);

	rx = rxBuffer[0] & (0x03 << FAULT_QUEUE);

	switch (rx)
	{
		case 0x00 :
			uart_print("1 fault queue\n\r");
			break;
		case 0x01 :
			uart_print("2 fault queues\n\r");
			break;
		case 0x02 :
			uart_print("3 fault queues\n\r");
			break;
		case 0x03 :
			uart_print("4 fault queues\n\r");
			break;
		default:
			break;
	}
}

/******************************************************************************
* @brief Displays Alert Mode setting.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintAlertMode(void)
{
	unsigned char rxBuffer[2] = { 0x00 };
	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, rxBuffer);

	if (rxBuffer[0] & (1 << INT_CT))
	{
		uart_print("Alert Mode: Comparator\n\r");
	}
	else
	{
		uart_print("Alert Mode: Interrupt\n\r");
	}
}

/******************************************************************************
* @brief Displays output polarity setting for CT pin.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintCTPolarity(void)
{
	unsigned char rxBuffer[1] = { 0x00 };
	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, rxBuffer);

	if (rxBuffer[0] & (1 << CT_POL))
	{
		uart_print("CT pin is Active High\n\r");
	}
	else
	{
		uart_print("CT pin is Active Low\n\r");
	}
}


/******************************************************************************
* @brief Displays output polarity setting for INT pin.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_PrintINTPolarity(void)
{
	unsigned char rxBuffer[1] = { 0x00 };
	I2C_Read(IIC_BASEADDR, ADT7420_IIC_ADDR, CONFIG_REG, 1, rxBuffer);

	if (rxBuffer[0] & (1 << INT_POL))
	{
		uart_print("INT pin is Active High\n\r");
	}
	else
	{
		uart_print("INT pin is Active Low\n\r");
	}
}

/******************************************************************************
* @brief Displays current settings of the ADT7420.
*
* @param None.
*
* @return None.
******************************************************************************/
void ADT7420_DisplaySettings(void)
{
	uart_print("\n\r ADT7420 Settings \n\r");
	uart_print("-----------------------------------------\n\r");
	ADT7420_GetResolution(1);

	ADT7420_PrintTHigh();
	ADT7420_PrintTLow();
	ADT7420_PrintTCrit();
	ADT7420_PrintHysteresis();

	ADT7420_PrintFaultQueue();

	ADT7420_PrintAlertMode();
	ADT7420_PrintCTPolarity();
	ADT7420_PrintINTPolarity();

	rxData = 'm';
	uart_print("\n\r>Returning to Main Menu...\n\r");
}



