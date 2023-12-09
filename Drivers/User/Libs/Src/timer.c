/************************************************************************************
 *
 *									[Timer - TqK]
 *
 ************************************************************************************/

/*[PRIVATE INCLUDE] --------------------------------------------------------
 _________________________________________________________________________*/

#include "timer.h"


/*[PRIVATE DEFINE] ---------------------------------------------------------
 _________________________________________________________________________*/



/*[PRIVATE DECLARE] --------------------------------------------------------
 _________________________________________________________________________*/
unsigned char _timer1Flag = 0;

/*
 * [SUBROUTINES] ----------------------------------------------------------
 _________________________________________________________________________*/
/*[Timer 1] --------------------------------------------------------*/

int Timer1_init(unsigned short __arrVALUE, unsigned short __pscVALUE)
{
	unsigned short *CR1 = (unsigned short *)(0x40010000);
	unsigned short *ARR = (unsigned short *)(0x4001002c);
	unsigned short *PSC = (unsigned short *)(0x40010028);

	//--- Disable Timer 1
	Timer1_disable();

	//--- Enable clock
	__HAL_RCC_TIM1_CLK_ENABLE();
//	__TIM1_CLK_ENABLE;


	//--- Direction == UpCounter
	bitRST(*CR1, 1, 4);

	//--- Set TIM1_ARR value
	*ARR = __arrVALUE - 1;

	//--- Set TIM1_PSC value
	*PSC = __pscVALUE - 1;

	//--- Enable Timer 1
//	Timer1_enable();

	return 0;
}

int Timer1_enable()
{
	unsigned short *CR1 = (unsigned short *)(0x40010000);
	bitSET(*CR1, 1, 0);

	return 0;
}

int Timer1_disable()
{
	unsigned short *CR1 = (unsigned short *)(0x40010000);
	bitRST(*CR1, 1, 0);

	return 0;
}

int Timer1_delay(Timer1Data *TIM, unsigned short __TIMEDELAY)
{
	char _flag = 0;
	TIM->currentSTT = _timer1Flag;

	if(TIM->lastSTT != TIM->currentSTT)
	{
		TIM->lastSTT = TIM->currentSTT;

		if((TIM->cnt++) >= __TIMEDELAY)
		{
			TIM->cnt = 0;
			 _flag = 1;
		}
	}

	return _flag;
}

int Timer1_ClearUIF()
{
	unsigned short *SR = (unsigned short *)(0x40010010);
	bitRST(*SR, 1, 0);
	return 0;
}

/*[TIMER 1 | INTERRUPT]*/

int Timer1_interruptInit()
{
	//--- Enable Timer 1 Update interrupt
	unsigned short *DIER = (unsigned short *)(0x4001000c);
	bitSET(*DIER, 1, 0);

	//--- Enable TIM1 position bit on NVIC ISER	(pos == 25)
	unsigned int *NVIC_ISER0 = (unsigned int *)(0xe000e100);
	bitSET(*NVIC_ISER0, 1, 25);

	return 0;
}

void TIM1_UP_TIM10_IRQHandler()
{
	_timer1Flag = !_timer1Flag;

	Timer1_ClearUIF();
}

