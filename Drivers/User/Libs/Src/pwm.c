/************************************************************************************
 *
 *									[PWM - TqK]
 *
 ************************************************************************************/

#include "pwm.h"

#define COUNTPWM_INTTERUPT

/*
 * [OUTPUT COMPARE] ==================================================================================
 */

/*[OUTPUT COMPARE | PWM] -----------------------------------------------------------*/

int Pwm_Init(unsigned int __pulseWIDTH)
{
	unsigned short *CCER = (unsigned short *)(0x40000820);
	unsigned short *CCMR1_Output = (unsigned short *)(0x40000818);


	//--- Configure PD12
	PD12_timer4init();

	//--- Set PSC = 1600, ARR = 100
	/*
	 * f = 10khz
	 */
	Timer4_init(1600, 100);

	//--- Disable Compare output
	bitRST(*CCER, 1, 0);

	//--- CC1 channel is configured as output
	bitRST(*CCMR1_Output, 3, 0);

	//--- Set PWM mode 1
	bitRST(*CCMR1_Output, 7, 4);
	bitSET(*CCMR1_Output, 0b110, 4);

	//--- Set PWM pulse width
	PWM_PulseWidth(__pulseWIDTH);

	//--- Enable Compare output
	bitSET(*CCER, 1, 0);

	//--- Enable Timer 4
	Timer4_enable();

	return 0;
}

int PWM_PulseWidth(unsigned int __pulseWIDTH)
{
	Timer4_compare(__pulseWIDTH);
	return 0;
}

/*[OUTPUT COMPARE | GPIO] -----------------------------------------------------------*/

int PD12_timer4init()
{
	//--- Enable GPIOD clock
	__HAL_RCC_GPIOD_CLK_ENABLE();

	unsigned int *OTYPER = (unsigned int *)(0x40020c04);
	unsigned int *MODER = (unsigned int *)(0x40020c00);
	unsigned int *AFRH = (unsigned int *)(0x40020c24);

	//--- Set Output push pull for pin 12
	bitRST(*OTYPER, 1, 12);

	//--- Set Alternate function mode for pin 12
	bitRST(*MODER, 0b11, 24);
	bitSET(*MODER, 0b10, 24);

	//--- Set AF02 for GPIO alternate function
	bitRST(*AFRH, 0xF, 16);
	bitSET(*AFRH, 2, 16);

	return 0;
}




/*[OUTPUT COMPARE | TIM4] -----------------------------------------------------------*/
int Timer4_init(unsigned short __PRESCALER, unsigned int __ARR)
{
	//--- Enable TIMER 4 clock
	__HAL_RCC_TIM4_CLK_ENABLE();

	//--- Disable Timer 4
	Timer4_disable();

	//--- Set prescaler
	Timer4_prescaler(__PRESCALER);

	//--- Set auto-reload
	Timer4_autoReload(__ARR);

	return 0;
}

int Timer4_enable()
{
	unsigned short *CR1 = (unsigned short *)(0x40000800);
	bitSET(*CR1, 1, 0);

	return 0;
}

int Timer4_disable()
{
	unsigned short *CR1 = (unsigned short *)(0x40000800);
	bitRST(*CR1, 1, 0);

	return 0;
}

int Timer4_prescaler(unsigned short __PSC)
{
	unsigned short *PSC = (unsigned short *)(0x40000828);
	*PSC = __PSC - 1;

	return 0;

}

int Timer4_autoReload(unsigned int __VALUE)
{
	unsigned short *ARR = (unsigned short *)(0x4000082c);
	*ARR = __VALUE - 1;

	return 0;
}

int Timer4_compare(unsigned int __VALUE)
{
	unsigned short *CCR1 = (unsigned short *)(0x40000834);
	*CCR1 = __VALUE;

	return 0;
}


/*
 * [INPUT CAPTURE] ==================================================================================
 */

unsigned int _freq = 0;
unsigned int _pulseWitdh = 0;

/*[INPUT CAPTURE | COUNT PULSE PWM] -----------------------------------------------------------*/

int CountPwm_Init()
{
	//--- Init GPIO PA0
	CountPwm_PA0init();

	//--- Init TIMER 5 for measure frequency
	CountPwm_Timer5init(1600);

#if defined COUNTPWM_INTTERUPT
	CountPwm_TimerInterrupt();
#endif

	//--- Enable TIMER 5
	CountPwm_Timer5enable();

	return 0;
}

unsigned int CountPwm_frequency()
{
	return CountPwm_Timer5ccr1();
}

unsigned int CountPwm_pulseWidth()
{
	return CountPwm_Timer5ccr2();
}



/*[INPUT CAPTURE | GPIO] -----------------------------------------------------------*/
int CountPwm_PA0init()
{
	//--- Enable clock GPIO A
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//--- Set AF mode for PA0
	unsigned int *MODER = (unsigned int *)(0x40020000);
	bitRST(*MODER, 3, 0);
	bitSET(*MODER, 2, 0);

	//--- Set AF02 for PA0
	unsigned int *AFRL = (unsigned int *)(0x40020020);
	bitRST(*AFRL, 15, 0);
	bitSET(*AFRL, 2, 0);

	return 0;
}

/*[INPUT CAPTURE | TIMER 5] -----------------------------------------------------------*/
int CountPwm_Timer5init(unsigned short __PRESCALER)
{
	//--- Enable TIMER 5 clock
	__HAL_RCC_TIM5_CLK_ENABLE();

	//--- Disable TIMER 5
	CountPwm_Timer5disable();

	//-- Set prescaler
	unsigned int *TIM5_PSC = (unsigned int *)(0x40000c28);
	*TIM5_PSC = __PRESCALER - 1;

	//--- Set ARR
	unsigned int *TIM5_ARR = (unsigned int *)(0x40000c2c);
	*TIM5_ARR = 0xFFFFFFFF;

	//--- TIM5_CH1 pin is connected to TI1 input
	unsigned int *TIM5_CR2 = (unsigned int *)(0x40000c04);
	bitRST(*TIM5_CR2, 1, 7);

	//--- Set CC1 channel is configured as input, IC1 is mapped on TI1
	unsigned int *TIM5_CCMR1 = (unsigned int *)(0x40000c18);
	bitRST(*TIM5_CCMR1, 3, 0);
	bitSET(*TIM5_CCMR1, 0b01, 0);

	//--- CC1 channel configured as input rising edge
	unsigned int *TIM5_CCER = (unsigned int *)(0x40000c20);
	bitRST(*TIM5_CCER, 1, 1);
	bitRST(*TIM5_CCER, 1, 3);

	//--- Trigger selection == Filtered Timer Input 1 (TI1FP1)
	unsigned int *TIM5_SMCR = (unsigned int *)(0x40000c08);
	bitRST(*TIM5_SMCR, 0b111, 4);
	bitSET(*TIM5_SMCR, 0b101, 4);

	//--- Slave mode selection == Reset mode
	bitRST(*TIM5_SMCR, 0b111, 0);
	bitSET(*TIM5_SMCR, 0b100, 0);

	//--- Set channel 2 in capture input mode, map on TI1
	bitRST(*TIM5_CCMR1, 3, 8);
	bitSET(*TIM5_CCMR1, 0b10, 8);

	//--- Set falling trigger for channel 2
	bitRST(*TIM5_CCER, 1, 7);
	bitSET(*TIM5_CCER, 1, 5);

	//--- Capture channel 1 enable
	bitSET(*TIM5_CCER, 1, 0);

	//--- Capture channel 2 enable
	bitSET(*TIM5_CCER, 1, 4);

	return 0;
}

int CountPwm_Timer5enable()
{
	unsigned int *TIM5_CR1 = (unsigned int *)(0x40000c00);
	bitSET(*TIM5_CR1, 1, 0);

	return 0;
}

int CountPwm_Timer5disable()
{
	unsigned int *TIM5_CR1 = (unsigned int *)(0x40000c00);
	bitRST(*TIM5_CR1, 1, 0);

	return 0;
}

unsigned int CountPwm_Timer5ccr1()
{
	unsigned int *TIM5_CCR1 = (unsigned int *)(0x40000c34);
	return *TIM5_CCR1;
}

unsigned int CountPwm_Timer5ccr2()
{
	unsigned int *TIM5_CCR2 = (unsigned int *)(0x40000c38);
	return *TIM5_CCR2;
}

int CountPwm_TimerInterrupt()
{
	unsigned int *TIM5_DIER = (unsigned int *)(0x40000c0c);

	//--- Capture 1 interrupt enable
	bitSET(*TIM5_DIER, 1, 1);

	//--- Capture 2 interrupt enable
	bitSET(*TIM5_DIER, 1, 2);

	//--- Enable TIM5 position bit on NVIC ISER	(pos == 50)
	unsigned int *NVIC_ISER1 = (unsigned int *)(0xe000e104);
	bitSET(*NVIC_ISER1, 1, (50-32));

	return 0;
}


void TIM5_IRQHandler()
{
	__asm("NOP");

	unsigned int *TIM5_SR = (unsigned int *)(0x40000c10);
	unsigned int *TIM5_CCR1 = (unsigned int *)(0x40000c34);
	unsigned int *TIM5_CCR2 = (unsigned int *)(0x40000c38);

	if(bitVALUE(*TIM5_SR, 1))
	{
		bitRST(*TIM5_SR, 1, 1);
		_freq = *TIM5_CCR1;
	}

	if(bitVALUE(*TIM5_SR, 2))
	{
		bitRST(*TIM5_SR, 1, 2);
		_pulseWitdh = *TIM5_CCR2;
	}
}
