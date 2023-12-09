/************************************************************************************
 *
 *								[LOW POWER MODE - TqK]
 *
 ************************************************************************************/

#include "LpMode.h"


/*
*   Brief: Configure Sleep mode (Cortex®-M4 with FPU core stopped, peripherals kept running)
*/
int SleepMode()
{
    unsigned int *SCR = (unsigned int *)(NVIC_SCR_AddBase);

    //--- Disable SysTick, SysTick Interrupt
    SYSTICK_DISABLE;
    SYSTICK_INTERRUPT_DISABLE;



    //--- Set SLEEPDEEP = 0
    bitRST(*SCR, 1, 2);

    //--- for WFI
    __asm("WFI");

    return 0;
}

/*
*   Brief: Configure Stop mode (all clocks are stopped)
*/
int StopMode()
{
    unsigned int *SCR = (unsigned int *)(NVIC_SCR_AddBase);

    //--- Disable SysTick, SysTick Interrupt
    SYSTICK_DISABLE;
    SYSTICK_INTERRUPT_DISABLE;

    //--- Set SEVONPEND
    bitSET(*SCR, 1, 4);

    //--- Set SLEEPDEEP = 0
    bitSET(*SCR, 1, 2);

    //--- for WFI
    __asm("WFI");
    
    return 0;
}

/*
*   Brief: Configure Standby mode (1.2 V domain powered off)
*/
int StandbyMode()
{
    return 0;
}
