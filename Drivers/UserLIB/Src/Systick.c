/************************************************************************************
 *
 *									[SYSTICK - TqK]
 *
 ************************************************************************************/

/*
 * INCLUDES ------------------------------------------------------------------
 _____________________________________________________________________________*/
// #include "../Inc/Systick.h"
#include "Systick.h"


/*
 * VARIABLES ------------------------------------------------------------------
 _____________________________________________________________________________*/

_Bool __flagSysTick = 0;

/*
 * FUNCTIONS ------------------------------------------------------------------
 _____________________________________________________________________________*/

/*
 * @Brief	: Initialize System Tick
 * @Prama	: None
 * @Retval	: None
 */
int SysTick_Init(unsigned int __ReloadVALUE)
{
	//--- Disable SysTick
	SysTick_Ctrl(Disable);

	//--- Calculate Reload Value
	/*
	 *	ReloadValue = F x 1ms
	 */
	SysTick_ReloadValue(__ReloadVALUE - 1);


	//--- Clear current value
	SysTick_CurrentValue(0);

	//--- Set clock source == processor clock
	SysTick_ClcSource();

	//--- Enable interrupt
	SysTick_Interrupt(Enable);

	return 0;
}


/*
 * @Brief	: System Tick control: Enable or Disable
 * @Prama	: State of System Tick
 * @Retval	: None
 */
int SysTick_Ctrl(SysTickCtrl_Typedef __STATE)
{
	unsigned int *SYST_CSR = (unsigned int *)(0xE000E010);

	bitRST(*SYST_CSR, 1, 0);

	bitSET(*SYST_CSR, __STATE, 0);

	return 0;
}


/*
 * @Brief	: Initialize Interrupt System Tick
 * @Prama	: State (Enable/ Disable)
 * @Retval	: None
 */
int SysTick_Interrupt(SysTickCtrl_Typedef __STATE)
{
	unsigned int *SYST_CSR = (unsigned int *)(0xE000E010);

	bitRST(*SYST_CSR, 1, 1);

	bitSET(*SYST_CSR, __STATE, 1);

	return 0;
}


/*
 * @Brief	: Set System Tick clock source. Default = processor clock
 * @Prama	: None
 * @Retval	: None
 */
int SysTick_ClcSource()
{
	unsigned int *SYST_CSR = (unsigned int *)(0xE000E010);

	bitSET(*SYST_CSR, 1, 2);

	return 0;
}


/*
 * @Brief	: Set reload value of system tick
 * @Prama	: None
 * @Retval	: None
 */
int SysTick_ReloadValue(unsigned int __VALUE)
{
	unsigned int *SYST_RVR = (unsigned int *)(0xE000E014);
	*SYST_RVR = __VALUE;

	return 0;
}

/*
 * @Brief	: Set current value of system tick
 * @Prama	: None
 * @Retval	: None
 */
int SysTick_CurrentValue(unsigned int __VALUE)
{
	unsigned int *SYST_RVR = (unsigned int *)(0xE000E018);
	*SYST_RVR = __VALUE;

	return 0;
}

#ifdef __Use_ManSysTick
void SysTick_Handler()
{
	__flagSysTick = !__flagSysTick;
}
#endif