/************************************************************************************
 *
 *									[SysTick - TqK]
 *
 ************************************************************************************/

/*[PRIVATE INCLUDE] --------------------------------------------------------
 _________________________________________________________________________*/

#include "systick.h"


/*[PRIVATE DEFINE] ---------------------------------------------------------
 _________________________________________________________________________*/



/*[PRIVATE DECLARE] --------------------------------------------------------
 _________________________________________________________________________*/

unsigned char __flagSysTick = 0;

/*
 * [SUBROUTINES] ----------------------------------------------------------
 _________________________________________________________________________*/

int SysTick_init(unsigned int __FCLK)
{
	unsigned int *STCSR = (unsigned int *)(0xe000e010);
	unsigned int *STRVR = (unsigned int *)(0xe000e014);

	//--- Disable systick
	SysTick_disable();

	//--- Indicate the clock source == processor clock
	bitSET(*STCSR, 1, 2);

	//--- Enable Systick exception request (interrupt event)
	bitSET(*STCSR, 1, 1);

	//--- Calculate Reload Value
	/*
	 * RELOAD = __FCLC * timeDelay (1ms)
	 */
	*STRVR = 16000 - 1;

	return 0;
}

int SysTick_enable()
{
	unsigned int *STCSR = (unsigned int *)(0xe000e010);
	bitSET(*STCSR, 1, 0);

	return 0;
}

int SysTick_disable()
{
	unsigned int *STCSR = (unsigned int *)(0xe000e010);
	bitRST(*STCSR, 1, 0);

	return 0;
}

void SysTick_Handler()
{
	__flagSysTick = !__flagSysTick;
}
