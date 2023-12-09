/************************************************************************************
 *
 *								[UART - TqK]
 *
 ************************************************************************************/


#include "uart.h"

char _uartRxByte;
volatile unsigned char flagUSART = 0;
char a[10];


/*[USART1] -----------------------------------------------------------*/
/*__________________________________________________________________*/

void Uart1_init()
{
	//--- Enable UART 1 clock
	__HAL_RCC_USART1_CLK_ENABLE();


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


//	Uart1_HandlerInit();

//	Uart1_DmaInit();
}


void Uart1_txByte(char __DATA)
{
	unsigned int *sr = (unsigned int *)(0x40011000);
	unsigned int *dr = (unsigned int *)(0x40011004);

	//--- Check Transmit data register empty
	while(!bitVALUE(*sr, 7));
	*dr = __DATA;

	//--- Check Transmission complete
	while(!bitVALUE(*sr, 6));
	bitRST(*sr, 1, 6);
}

void Uart1_txString(char *str)
{
	while(*str)
	{
		Uart1_txByte(*str++);
	}
}

void Uart1_printf(char *str, ...)
{
	char buffer[100] = {0};

	va_list aptr;
	va_start(aptr, str);
	vsprintf(buffer, str, aptr);
	Uart1_txString(buffer);
	va_end(aptr);
}

char Uart1_rxByte()
{
	unsigned int *sr = (unsigned int *)(0x40011000);
	unsigned int *dr = (unsigned int *)(0x40011004);

	while(!bitVALUE(*sr, 5));
	char _tmp = *dr;
	return _tmp;
}

/*[USART1]__INTERRUPT ---------------------------*/

void Uart1_HandlerInit()
{
	unsigned int *cr1 = (unsigned int *)(0x4001100c);

	//--- bitSET Rx Interrput
	bitSET(*cr1, 1, 5);

	//--- Enable UART1 position bit on NVIC ISER	(pos == 37)
	unsigned int *iser1 = (unsigned int *)(0xe000e104);
	bitSET(*iser1, 1, (37-32));
}


void USART1_IRQHandler()
{
	unsigned int *dr = (unsigned int *)(0x40011004);
	_uartRxByte = *dr;

}

unsigned char Uart1_Handler()
{
	_uartRxByte = Uart1_rxByte();
	return 1;
}


/*[USART1]__DMA ---------------------------*/

void Uart1_DmaInit()
{
	//--- UART DMA enable receiver
	unsigned int *uartCr3 = (unsigned int *)(0x40011014);
	bitSET(*uartCr3, 1, 6);

	//--- DMA2 clock enable
	__HAL_RCC_DMA2_CLK_ENABLE();

	/*
	 * data receive size == 1
	 * from: UART1_DR
	 * to: _uartRxByte
	 */
	unsigned int *s5ndtr = (unsigned int *)(0x4002648c);
	unsigned int *s5par = (unsigned int *)(0x40026490);
	unsigned int *s5m0ar = (unsigned int *)(0x40026494);

	*s5ndtr = 1;
	*s5par = 0x40011004;
	*s5m0ar = &_uartRxByte;

	//--- Use DMA2, Stream 5, Channel 4
	unsigned int *s5cr = (unsigned int *)(0x40026488);
	bitSET(*s5cr, 0b100, 25);

	//--- Memory increment mode enable
	bitSET(*s5cr, 1, 10);

	//--- Circular mode enable
	bitSET(*s5cr, 1, 8);

	//--- Transfer complete interrupt enable
	bitSET(*s5cr, 1, 4);

	//--- Enable DMA2 str5_ch4 position bit on NVIC ISER	(pos == 68)
	unsigned int *NVIC_ISER2 = (unsigned int *)(0xe000e108);
	bitSET(*NVIC_ISER2, 1, (68-64));

	//--- Enable DMA2, Stream 5
	bitSET(*s5cr, 1, 0);
}

void Dma2Str5_Handler()
{
	__asm("NOP");
	Dm2Str5_ClearPending();
}

void Dm2Str5_ClearPending()
{
	unsigned int *HIFCR = (unsigned int *)(0x4002640c);
	bitSET(*HIFCR, 1, 11);
}
