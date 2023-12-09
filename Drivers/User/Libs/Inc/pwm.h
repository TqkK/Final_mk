/************************************************************************************
 *
 *									[PWM - TqK]
 *
 ************************************************************************************/

#ifndef __PWM_H_
#define __PWM_H_



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


/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/

/*
 * [OUTPUT COMPARE] ==================================================================================
 */

/*[OUTPUT COMPARE | PWM] -----------------------------------------------------------*/
int Pwm_Init(unsigned int __pulseWIDTH);
int PWM_PulseWidth(unsigned int __pulseWIDTH);


/*[OUTPUT COMPARE | GPIO] -----------------------------------------------------------*/
int PD12_timer4init();


/*[OUTPUT COMPARE | TIM4] -----------------------------------------------------------*/
int Timer4_init(unsigned short __PRESCALER, unsigned int __ARR);
int Timer4_enable();
int Timer4_disable();
int Timer4_prescaler(unsigned short __PSC);
int Timer4_autoReload(unsigned int __VALUE);
int Timer4_compare(unsigned int __VALUE);


/*
 * [INPUT CAPTURE] ==================================================================================
 */


/*[INPUT CAPTURE | COUNT PULSE PWM] -----------------------------------------------------------*/

int CountPwm_Init();
unsigned int CountPwm_frequency();
unsigned int CountPwm_pulseWidth();

/*[INPUT CAPTURE | GPIO] -----------------------------------------------------------*/
int CountPwm_PA0init();

/*[INPUT CAPTURE | TIMER 5] -----------------------------------------------------------*/
int CountPwm_Timer5init(unsigned short __PRESCALER);
int CountPwm_Timer5enable();
int CountPwm_Timer5disable();
unsigned int CountPwm_Timer5ccr1();
unsigned int CountPwm_Timer5ccr2();
int CountPwm_TimerInterrupt();

void TIM5_IRQHandler();

/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/
extern unsigned int _freq, _pulseWitdh;

#ifdef __cplusplus
}
#endif


#endif /* __PWM_H_ */
