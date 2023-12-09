/************************************************************************************
 *
 *								    [UART - TqK]
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

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#include "UserDefine.h"
#include "Rcc.h"

/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/


/* PRIVATE DECLARE --------------------------------------------------------------
_________________________________________________________________________________*/

/*[USART1] -----------------------------------------------------------*/

int Uart1_init();
int Uart1_txByte(char __DATA);
char Uart1_rxByte();
int Uart1_txString(char *str);
int Uart1_printf(char *str, ...);

/*[USART1 | PB6_PB7 - TX_RX] ------------------------------------------*/

int PB6_Uart1txInit();
int PB7_Uart1rxInit();

/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/
extern char ResetColor[];
extern char RedColor[], BoldRedColor[];
extern char BoldBlueColor[];

#ifdef __cplusplus
}
#endif

#endif /* __UART_H_ */