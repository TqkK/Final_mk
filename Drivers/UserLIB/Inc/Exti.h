/************************************************************************************
 *
 *								    [EXTI - TqK]
 *
 ************************************************************************************/

#ifndef __EXTI_H
#define __EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "System.h"
#include "CortexM4.h"
#include "Systick.h"

/* DEFINES -------------------------------------------------------------------*/

#define EXTI_AddBase            0x40013C00



/* TYPEDEF -------------------------------------------------------------------*/

typedef enum
{
    exti_IMR = 0x00,
    exti_EMR = 0x04,
    exti_RTSR = 0x08,
    exti_FTSR = 0x0C,
    exti_SWIER = 0x10,
    exti_PR = 0x14,
} extiReg_typedef;


/* MACRO ---------------------------------------------------------------------*/





/* VARIABLES -----------------------------------------------------------------*/

extern unsigned char __exti0Flag;


/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

int EXTI0_Pa0Init();
int EXTI0_ClearPending();



#ifdef __cplusplus
}
#endif

#endif /* __EXTI_H */
