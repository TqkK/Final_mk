/************************************************************************************
 *
 *									[Timer - TqK]
 *
 ************************************************************************************/

#ifndef __TIMER_H_
#define __TIMER_H_



#ifdef __cplusplus
extern "C" {
#endif

/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/

#include "UserDefine.h"


/* PRIVATE MACRO --------------------------------------------------------------
_________________________________________________________________________________*/



/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/

typedef struct
{
	unsigned short cnt;

	unsigned char lastSTT;
	unsigned char currentSTT;

}__timer1_typedef;

typedef __timer1_typedef Timer1Data;

/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/

/*[Timer 1] --------------------------------------------------------*/
/*__________________________________________________________________*/

int Timer1_init(unsigned short __arrVALUE, unsigned short __pscVALUE);
int Timer1_enable();
int Timer1_disable();
int Timer1_delay(Timer1Data *TIM, unsigned short __TIMEDELAY);
int Timer1_ClearUIF();

/*[TIMER 1 | INTERRUPT]*/
int Timer1_interruptInit();

void TIM1_UP_TIM10_IRQHandler();

/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/

extern unsigned char _timer1Flag;

#ifdef __cplusplus
}
#endif


#endif /* __TIMER_H_ */
