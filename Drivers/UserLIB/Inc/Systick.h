/************************************************************************************
 *
 *									[SYSTICK - TqK]
 *
 ************************************************************************************/

#ifndef __SYSTICK_H
#define __SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"

/* MACRO ---------------------------------------------------------------------*/

typedef Ctrl_Typedef SysTickCtrl_Typedef;


/* DEFINES -------------------------------------------------------------------*/

#define SYSTICK_ENABLE			SysTick_Ctrl(Enable)
#define SYSTICK_DISABLE			SysTick_Ctrl(Disable)

#define SYSTICK_INTERRUPT_ENABLE        SysTick_Interrupt(Enable)
#define SYSTICK_INTERRUPT_DISABLE       SysTick_Interrupt(Disable)

/* VARIABLES | CONSTANTS -----------------------------------------------------*/




/* VARIABLES -----------------------------------------------------*/

extern _Bool __flagSysTick;


/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

int SysTick_Init(unsigned int __ReloadVALUE);
int SysTick_Ctrl(SysTickCtrl_Typedef __STATE);
int SysTick_Interrupt(SysTickCtrl_Typedef __STATE);
int SysTick_ClcSource();
int SysTick_ReloadValue(unsigned int __VALUE);
int SysTick_CurrentValue(unsigned int __VALUE);

// void SysTick_Handler();

#ifdef __cplusplus
}
#endif

#endif /* __SYSTICK_H */
