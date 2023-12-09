/************************************************************************************
 *
 *								[Soft Timer - TqK]
 *
 ************************************************************************************/

#ifndef __SOFT_TIMER_H_
#define __SOFT_TIMER_H_



#ifdef __cplusplus
extern "C" {
#endif

/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/

#include "systick.h"

/* PRIVATE MACRO --------------------------------------------------------------
_________________________________________________________________________________*/



/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/

typedef struct
{
	unsigned short cnt;

	unsigned char lastSTT;
	unsigned char currentSTT;

}SoftTimer_typedef;

/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/

int SoftTimer_init();
int SoftTimer(SoftTimer_typedef *TIM, unsigned short __TIMEVALUE);




/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/


#ifdef __cplusplus
}
#endif


#endif /* __SOFT_TIMER_H_ */
