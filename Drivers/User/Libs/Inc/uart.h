/************************************************************************************
 *
 *								[UART - TqK]
 *
 ************************************************************************************/

#ifndef __UART_H_
#define __UART_H_


#ifdef __cplusplus
extern "C" {
#endif


/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "UserDefine.h"
#include "gpio.h"
#include "exti.h"


/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/


/* PRIVATE DECLARE --------------------------------------------------------------
_________________________________________________________________________________*/
void Uart1_init();
void Uart1_txByte(char __DATA);
char Uart1_rxByte();
void Uart1_txString(char *str);
void Uart1_printf(char *str, ...);


/*[USART1]__INTERRUPT ---------------------------*/

void Uart1_HandlerInit();
void USART1_IRQHandler();
unsigned char Uart1_Handler();

/*[USART1]__DMA ---------------------------*/
void Uart1_DmaInit();
void Dma2Str5_Handler();
void Dm2Str5_ClearPending();

/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/

extern char _uartRxByte;
extern volatile unsigned char flagUSART;
extern char a[10];

#ifdef __cplusplus
}
#endif

#endif /* __UART_H_ */
