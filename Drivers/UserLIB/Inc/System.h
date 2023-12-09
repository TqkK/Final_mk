/************************************************************************************
 *
 *									[SYSTEM - TqK]
 *
 ************************************************************************************/

#ifndef __SYSTEM_H
#define __SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "Rcc.h"
#include "Flash.h"
#include "Systick.h"

/* DEFINES -------------------------------------------------------------------*/

#define SYSCFG_AddBase          0x40013800

/* TYPEDEF -------------------------------------------------------------------*/

typedef enum
{
    sysCfgReg_MEMRMP = 0x00,
    sysCfgReg_PMC = 0x04,
    sysCfgReg_EXTICR1 = 0x08,
    sysCfgReg_EXTICR2 = 0x0C,
    sysCfgReg_EXTICR3 = 0x10,
    sysCfgReg_EXTICR4 = 0x14,
    sysCfgReg_CMPCR = 0x20,
} sysCfgReg_typedef;

/* MACRO ---------------------------------------------------------------------*/






/* VARIABLES -----------------------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

void SystemInit();




#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_H */
