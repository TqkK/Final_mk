/************************************************************************************
 *
 *									[WWDG - TqK]
 *
 ************************************************************************************/

/*
    WWDG Formula:
        tWWDG = tPCLK1 × 4096 × 2^WDGTB[1:0] × (T[5:0] + 1) (ms)
*/

#include "Wwdg.h"

#define WWDG_INTERRUPT
// #define DEBUG

/*
 * @Brief	: WWDG init
 */
int Wwdg_Init(WwdgPrescaler_typedef __PRESCALE, unsigned char __COUNTER, unsigned char __WINDOW)
{
    //--- WWDG clock enable
    WWDG_CLK_ENABLE;
    
    //--- Set prescaler for wwdg
    Wwdg_Prescaler(__PRESCALE);

    Wwdg_SetCounter(__COUNTER);

    Wwdg_SetWindowValue(__WINDOW);

#ifdef  WWDG_INTERRUPT
    Wwdg_InterruptInit();
#endif

#ifdef DEBUG
    Wwdg_Debug();
#endif

    return 0;
}


/*
 * @Brief	: WWDG enable
 */
int Wwdg_Enable()
{
    unsigned int *WWDG_CR = (unsigned int *)(WWDG_AddBase + wwdg_CR);

    bitSET(*WWDG_CR, 1, 7);

    return 0;
}

/*
 * @Brief	: WWDG set counter
 */
int Wwdg_SetCounter(unsigned char __COUNTER)
{
    unsigned int *WWDG_CR = (unsigned int *)(WWDG_AddBase + wwdg_CR);

    bool _tmp = bitVALUE(*WWDG_CR, 7);

    *WWDG_CR = (__COUNTER & ~(1 << 7)) | (_tmp << 7);

    return 0;
}


/*
 * @Brief	: WWDG set window value
 */
int Wwdg_SetWindowValue(unsigned char __WINDOW)
{
    unsigned int *WWDG_CFR = (unsigned int *)(WWDG_AddBase + wwdg_CFR);

    *WWDG_CFR = __WINDOW & ~(0b111 << 7);

    return 0;
}


/*
 * @Brief	: WWDG set time base prescaler
 */
int Wwdg_Prescaler(WwdgPrescaler_typedef __PRESCALE)
{
    unsigned int *WWDG_CFR = (unsigned int *)(WWDG_AddBase + wwdg_CFR);

    bitSET(*WWDG_CFR, __PRESCALE, 7);

    return 0;
}

/*
 * @Brief	: WWDG Early wakeup interrupt init
 */
int Wwdg_InterruptInit()
{
    //--- Set Early wakeup interrupt
    unsigned int *WWDG_CFR = (unsigned int *)(WWDG_AddBase + wwdg_CFR);

    bitSET(*WWDG_CFR, 1, 9);

    //--- Enable WWDG position bit on NVIC ISER	(pos == 0)
    unsigned int *NVIC_ISER0 = (unsigned int *)(0xE000E100);
    bitSET(*NVIC_ISER0, 1, 0);

    return 0;
}

/*
 * @Brief	: WWDG clear Early wakeup interrupt flag
 */
int Wwdg_ClearInterruptFlag()
{
    unsigned int *WWDG_SR = (unsigned int *)(WWDG_AddBase + wwdg_SR);
    
    bitRST(*WWDG_SR, 1, 0);
    
    return 0;
}


/*
 * @Brief	: Freeze WWDG when debug
 */
int Wwdg_Debug()
{
    unsigned int *DBGMCU_APB1_FZ = (unsigned int *)(0xE0042008);

    bitSET(*DBGMCU_APB1_FZ, 1, 11);

    return 0;
}

void WWDG_IRQHandler()
{
    // __asm("NOP");
    unsigned int *WWDG_CFR = (unsigned int *)(WWDG_AddBase + wwdg_CFR);
    unsigned int *WWDG_CR = (unsigned int *)(WWDG_AddBase + wwdg_CR);

    unsigned char _cnt = *WWDG_CR & (0b1111111);
    unsigned char _win = *WWDG_CFR & (0b1111111);

    if(_cnt < _win)
    {
        Wwdg_ClearInterruptFlag();
        Wwdg_SetCounter(0x7F);
    }
}