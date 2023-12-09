/************************************************************************************
 *
 *									[SOFT TIMER - TqK]
 *
 ************************************************************************************/

#ifndef __SOFT_TIMER_H
#define __SOFT_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "Systick.h"

/* DEFINES -------------------------------------------------------------------*/


/* TYPEDEF -------------------------------------------------------------------*/
typedef struct
{
	unsigned short cnt;

	unsigned char lastSTT;
	unsigned char currentSTT;
} SoftTimer_Typedef;

typedef SoftTimer_Typedef SoftTimerData;
/* MACRO ---------------------------------------------------------------------*/



/* VARIABLES | CONSTANTS -----------------------------------------------------*/




/* VARIABLES -----------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

int SoftTimer(SoftTimerData *TIM, unsigned short __TIMEVALUE);



#ifdef __cplusplus
}
#endif

#endif /* __SOFT_TIMER_H */
