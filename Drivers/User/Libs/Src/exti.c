/************************************************************************************
 *
 *								[EXTI - TqK]
 *
 ************************************************************************************/


#include "exti.h"


/*[EXTI0] -----------------------------------------------------------*/
/*__________________________________________________________________*/
void Exti0_Init()
{
	//--- bitSET PA0: input
	PA0_inInit();

	//--- SYSCFG external interrupt configuration
	unsigned int *exticr1 = (unsigned int *)(0x40013808);
	bitRST(*exticr1, 0x0F, 0);

	//--- Rising trigger selection
	unsigned int *rtsr = (unsigned int *)(0x40013c08);
	bitSET(*rtsr, 1, 0);

	//--- Interrupt mask register
	unsigned int *imr = (unsigned int *)(0x40013c00);
	bitSET(*imr, 1, 0);

	//--- NVIC enable EXTI0 postion
	unsigned int *nvicIser0 = (unsigned int *)(0xe000e100);
	bitSET(*nvicIser0, 1, 6);
}

void Exti0_ClearPending()
{
	unsigned int *pr = (unsigned int *)(0x40013c14);
	bitSET(*pr, 1, 0);
}

void EXTI0_IRQHandler()
{
	__asm("nop");
	Exti0_ClearPending();
}

void Exti0_Handler()
{
	__asm("nop");
	Exti0_ClearPending();
}

/*[Vector Table] ---------------------------------------------------*/
/*__________________________________________________________________*/
void CopyVttbToRam(unsigned int __destinateADRESS, unsigned short __BYTE)
{
	memcpy(__destinateADRESS, 0x00000000, __BYTE);

	//--- Assign to ARM cortex Vector table address at RAM
	unsigned int *vtor = (unsigned int *)(0xE000ED08);
	*vtor = __destinateADRESS;
}

void ModifyAddressFunction(unsigned int __adrVTTB, unsigned int __adrOldFUNC, unsigned int __nameFUNC)
{
	unsigned int *userFunc = (unsigned int *)(__adrVTTB + __adrOldFUNC);
	*userFunc = (unsigned int)(__nameFUNC) | 1;
}


