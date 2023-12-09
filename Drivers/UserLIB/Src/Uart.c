/************************************************************************************
 *
 *									[UART - TqK]
 *
 ************************************************************************************/


#include "Uart.h"

char ResetColor[] = "\033[0m"; 
char RedColor[] = "\033[0;31m";
char BoldBlueColor[] = "\033[1;34m";
char BoldRedColor[] = "\033[1;31m";

/*[USART1] -----------------------------------------------------------*/
/*__________________________________________________________________*/

/*
 * Brief	: UART 1 initialize
 */
int Uart1_init()
{
	//--- Enable UART 1 clock
	USART1_CLK_ENABLE;


	//--- Tx Rx init
	PB6_Uart1txInit();
	PB7_Uart1rxInit();

	//--- bitSET Baudrate == 9600
	/*
	 * OVER8 == 0
	 * Fck == 16 mhz
	 * UartDIV == 16mhz / (8*2*9600) = 104.1666667
	 * mantissa == 104
	 * fraction == 0.166667*16 = 2.66667 --> 3
	 */
	//OVER8 == 0
	unsigned int *cr1 = (unsigned int *)(0x4001100c);
	bitRST(*cr1, 1, 15);

	unsigned int *brr = (unsigned int *)(0x40011008);
	bitSET(*brr, 104, 4);
	bitSET(*brr, 3, 0);

	//--- bitSET Data size == 8 bits
	bitRST(*cr1, 1, 12);

	//--- bitSET Parity (none)
	// Parity control disable
	bitRST(*cr1, 1, 10);

	//--- Enable Tx, Rx, Uart1
	bitSET(*cr1, 1, 3);
	bitSET(*cr1, 1, 2);
	bitSET(*cr1, 1, 13);

	return 0;
}

/*
 * @Brief	: UART 1 transfer 1 byte
 */
int  Uart1_txByte(char __DATA)
{
	unsigned int *sr = (unsigned int *)(0x40011000);
	unsigned int *dr = (unsigned int *)(0x40011004);

	//--- Check Transmit data register empty
	while(!bitVALUE(*sr, 7));
	*dr = __DATA;

	//--- Check Transmission complete
	while(!bitVALUE(*sr, 6));
	bitRST(*sr, 1, 6);

	return 0;
}

/*
 * @Brief	: UART 1 transfer string
 */
int Uart1_txString(char *str)
{
	while(*str)
	{
		Uart1_txByte(*str++);
	}

	return 0;
}

/*
 * Brief	: UART 1 print log
 */
int Uart1_printf(char *str, ...)
{
	char buffer[100] = {0};

	va_list aptr;
	va_start(aptr, str);
	vsprintf(buffer, str, aptr);
	
	va_end(aptr);
	Uart1_txString(buffer);
	
	return 0;
}

/*
 * Brief	: UART 1 receive 1 byte
 */
char Uart1_rxByte()
{
	unsigned int *sr = (unsigned int *)(0x40011000);
	unsigned int *dr = (unsigned int *)(0x40011004);

	while(!bitVALUE(*sr, 5));
	char _tmp = *dr;
	return _tmp;
}



/*[USART1 | PB6_PB7 - TX_RX] ------------------------------------------*/
/*__________________________________________________________________*/

/*
 * @Brief	: PB6 Tx pin of UART 1 initialize
 */
int PB6_Uart1txInit()
{
	//--- Enable GPIO B clock
	GPIOB_CLK_ENABLE;

	//--- GPIO_MODER == alternate function mode
	unsigned int *moder = (unsigned int *)(0x40020400);
	bitRST(*moder, 0b11, 12);
	bitSET(*moder, 0b10, 12);

	//--- GPIO_AFRL == AF07
	unsigned int *afrl = (unsigned int *)(0x40020420);
	bitRST(*afrl, 0x0F, 24);
	bitSET(*afrl, 7, 24);

	return 0;
}

/*
 * @Brief	: PB7 Rx pin of UART 1 initialize
 */
int PB7_Uart1rxInit()
{
	//--- Enable GPIO B clock
	GPIOB_CLK_ENABLE;

	//--- GPIO_MODER == alternate function mode
	unsigned int *moder = (unsigned int *)(0x40020400);
	bitRST(*moder, 0b11, 14);
	bitSET(*moder, 0b10, 14);

	//--- GPIO_AFRL == AF07
	unsigned int *afrl = (unsigned int *)(0x40020420);
	bitRST(*afrl, 0x0F, 28);
	bitSET(*afrl, 7, 28);

	return 0;
}