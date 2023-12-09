/************************************************************************************
 *
 *								[EXTI - TqK]
 *
 ************************************************************************************/

#ifndef __EXTI_H_
#define __EXTI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/
#include "string.h"
#include "UserDefine.h"

#include "gpio.h"
#include "uart.h"


/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/


/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/
void Exti0_Init();
void Exti0_ClearPending();
void EXTI0_IRQHandler();
void Exti0_Handler();

void CopyVttbToRam(unsigned int __destinateADRESS, unsigned short __BYTE);
void ModifyAddressFunction(unsigned int __adrVTTB, unsigned int __adrOldFUNC, unsigned int __nameFUNC);



/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/


#ifdef __cplusplus
}
#endif

#endif /* __EXTI_H_ */
