/************************************************************************************
 *
 *									[WWDG - TqK]
 *
 ************************************************************************************/

#ifndef __WWDG_H
#define __WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "Rcc.h"


/* DEFINES -------------------------------------------------------------------*/
#define WWDG_AddBase     0x40002C00


/* TYPEDEF -------------------------------------------------------------------*/
typedef enum
{
    wwdg_CR = 0x00,         // Control register
    wwdg_CFR = 0x04,        // Configuration register
    wwdg_SR = 0x08,         // Status register
} WwdgReg_typedef;

typedef enum
{
    wwdg_Div1 = 0,
    wwdg_Div2 = 0b01,
    wwdg_Div4 = 0b10,
    wwdg_Div8 = 0b11,
} WwdgPrescaler_typedef;

/* MACRO ---------------------------------------------------------------------*/





/* VARIABLES -----------------------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/
int Wwdg_Init(WwdgPrescaler_typedef __PRESCALE, unsigned char __COUNTER, unsigned char __WINDOW);
int Wwdg_Enable();
int Wwdg_SetCounter(unsigned char __COUNTER);
int Wwdg_SetWindowValue(unsigned char __WINDOW);
int Wwdg_Prescaler(WwdgPrescaler_typedef __PRESCALE);

int Wwdg_InterruptInit();
int Wwdg_ClearInterruptFlag();

int Wwdg_Debug();



#ifdef __cplusplus
}
#endif

#endif /* __WWDG_H */
