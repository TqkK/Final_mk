/************************************************************************************
 *
 *										[GPIO - TqK]
 *
 ************************************************************************************/

#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/
#include "UserDefine.h"
#include "Rcc.h"


/* DEFINES -------------------------------------------------------------------*/




/* MACRO ---------------------------------------------------------------------*/
#define LED_GREEN_INIT         PD12_ouputInit()
#define LED_GREEN_ON           PD12_outputWrite(1)
#define LED_GREEN_OFF          PD12_outputWrite(0)

#define LED_RED_INIT          PD14_ouputInit()
#define LED_RED_ON            PD14_outputWrite(1)
#define LED_RED_OFF           PD14_outputWrite(0)

#define LED_BLUE_INIT         PD15_ouputInit()
#define LED_BLUE_ON           PD15_outputWrite(1)
#define LED_BLUE_OFF          PD15_outputWrite(0)

/* VARIABLES -----------------------------------------------------------------*/


/* VARIABLES | CONSTANTS -------------------------------------------*/


/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

int PD12_ouputInit();
int PD12_outputWrite(unsigned char __STATE);

int PD14_ouputInit();
int PD14_outputWrite(unsigned char __STATE);

int PD15_ouputInit();
int PD15_outputWrite(unsigned char __STATE);

int PA0_inputInit();
unsigned char PA0_inputState();

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
