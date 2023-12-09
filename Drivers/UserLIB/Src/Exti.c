/************************************************************************************
 *
 *								    [EXTI - TqK]
 *
 ************************************************************************************/

#include "Exti.h"

unsigned char __exti0Flag = 0;

/*
*   Brief: Initialize EXTI0 on PA0 pin
*/
int EXTI0_Pa0Init()
{
	//--- bitSET GPIO_MODER == input
	unsigned int *GPIOA_MODER = (unsigned int *)(0x40020000);
	bitRST(*GPIOA_MODER, 0b11, 0);
	bitSET(*GPIOA_MODER, 0b00, 0);

	unsigned int *EXTI_EMR = (unsigned int *)(EXTI_AddBase + exti_EMR);
	bitSET(*EXTI_EMR, 1, 0);


	//--- External interrupt/event GPIO mapping
	unsigned int *SYSCFG_EXTICR1 = (unsigned int *)(SYSCFG_AddBase + sysCfgReg_EXTICR1);
	bitRST(*SYSCFG_EXTICR1, 0b1111, 0);

	//--- Rising trigger enable 
	unsigned int *EXTI_RTSR = (unsigned int *)(EXTI_AddBase + exti_RTSR);
	bitSET(*EXTI_RTSR, 1, 0);

	//--- Interrupt mask register
	unsigned int *EXTI_IMR = (unsigned int *)(EXTI_AddBase + exti_IMR);
	bitSET(*EXTI_IMR, 1, 0);

	//--- NVIC enable EXTI0 postion
	unsigned int *nvicIser0 = (unsigned int *)(NVIC_ISER_AddBase);
	bitSET(*nvicIser0, 1, 6);

	return 0;
}

/*
*   Brief: Interrupt Service Handler for EXTI0
*/
void EXTI0_IRQHandler()
{
	__asm("NOP");

	EXTI0_ClearPending();
	
	__exti0Flag = 0;
	
#if ( __use_HSE == 1 )
	unsigned char __PLLM = 4;
	unsigned short __PLLN = 64;

	Rcc_Init(__PLLM, __PLLN, PLLP_Div2);
#endif

	unsigned int *SYST_CSR = (unsigned int *)(0xE000E010);
	SYSTICK_INTERRUPT_ENABLE;
	SYSTICK_ENABLE;

	while(! bitVALUE(*SYST_CSR, 0) );

}

/*
*   Brief: Clear pending bit of EXTI0
*/
int EXTI0_ClearPending()
{
	unsigned int *EXTI_PR = (unsigned int *)(EXTI_AddBase + exti_PR);
	bitSET(*EXTI_PR, 1, 0);

	return 0;
}



// #if ( __use_HSE == 1 )
// 	unsigned char __PLLM = 4;
// 	unsigned short __PLLN = 64;

// 	Rcc_Init(__PLLM, __PLLN, PLLP_Div2);
// #endif

// 	unsigned int *SYST_CSR = (unsigned int *)(0xE000E010);
// 	SYSTICK_INTERRUPT_ENABLE;
// 	SYSTICK_ENABLE;

// 	while(! bitVALUE(*SYST_CSR, 0) );