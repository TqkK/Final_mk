/************************************************************************************
 *
 *								[LOW POWER MODE - TqK]
 *
 ************************************************************************************/

#ifndef __LOW_POWER_MODE_H
#define __LOW_POWER_MODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "Systick.h"



/* DEFINES -------------------------------------------------------------------*/
#define NVIC_SCR_AddBase        0xE000ED10          // System Control Register


/* TYPEDEF -------------------------------------------------------------------*/



/* MACRO ---------------------------------------------------------------------*/





/* VARIABLES -----------------------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

int SleepMode();
int StopMode();
int StandbyMode();


#ifdef __cplusplus
}
#endif

#endif /* __LOW_POWER_MODE_H */
