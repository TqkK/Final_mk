/************************************************************************************
 *
 *									[CORTEX M4 - TqK]
 *
 ************************************************************************************/

#include "CortexM4.h"

/*
*   Brief: Get priority for External interrupt/ event controller 
            what have their positions from 0 to 85
*/
unsigned char Nvic_GetInterruptPriority(IRQnPos_typedef __IRQ)
{
    /*  Find the IPR number and byte offset for interrupt m as follows:
        • the corresponding IPR number, n = m DIV 4
        • the byte offset of the required Priority field in this register is m MOD 4
    ** Only access 4 highest bits in 8 bits
    */
    unsigned char _n = __IRQ/4;
    unsigned char _offset = __IRQ%4;
    
    unsigned int *NVIC_IPRn = (unsigned int *)(NVIC_IPR_AddBase + (_n*4));

    unsigned char _priority = *NVIC_IPRn >> ((_offset*8)+4);

    return _priority;
}


/*
*   Brief: Set priority for External interrupt/ event controller 
            what have their positions from 0 to 85
*/
int Nvic_SetInterruptPriority(IRQnPos_typedef __IRQ, unsigned char __PRIORITY)
{
    if(__PRIORITY < 0 || __PRIORITY > 15)
    {
        return -1;
    }
    
    /*  Find the IPR number and byte offset for interrupt m as follows:
            • the corresponding IPR number, n = m DIV 4
            • the byte offset of the required Priority field in this register is m MOD 4
        ** Only access 4 highest bits in 8 bits
    */
    unsigned char _iPRn = __IRQ / 4;
    unsigned char _byteOffset = __IRQ % 4;
    
    unsigned int *NVIC_IPRn = (unsigned int *)(NVIC_IPR_AddBase + (_iPRn*4));

    bitRST(*NVIC_IPRn, 0b1111, ((_byteOffset*8) + 4));
    bitSET(*NVIC_IPRn, __PRIORITY, ((_byteOffset*8) + 4));

    return 0;
}

/*
*   Brief: Get priority for System Handler
*/
unsigned char Nvic_GetSysHandlerPriority(IRQnPos_typedef __IRQ)
{
    unsigned int *SHPR1 = (unsigned int *)(0xE000ED18);
    unsigned int *SHPR2 = (unsigned int *)(0xE000ED1C);
    unsigned int *SHPR3 = (unsigned int *)(0xE000ED20);

    unsigned char _tmpData;

    if((__IRQ == MemoryManagement_IRQn) || (__IRQ == BusFault_IRQn) || (__IRQ == UsageFault_IRQn))
    {
        _tmpData = (*SHPR1 >> (((__IRQ + 12)*8) + 4));
    }
    
    if(__IRQ == SVCall_IRQn)
    {
        _tmpData = (*SHPR2 >> (24 + 4));
    }

    if((__IRQ == PendSV_IRQn) || (__IRQ == SysTick_IRQn))
    {
        _tmpData = (*SHPR3 >> (((__IRQ + 4)*8) + 4));
    }

    return _tmpData;
}

/*
*   Brief: Set priority for System Handler
*/
int Nvic_SetSysHandlerPriority(IRQnPos_typedef __IRQ, unsigned char __PRIORITY)
{
    unsigned int *SHPR1 = (unsigned int *)(0xE000ED18);
    unsigned int *SHPR2 = (unsigned int *)(0xE000ED1C);
    unsigned int *SHPR3 = (unsigned int *)(0xE000ED20);

    if((__IRQ == MemoryManagement_IRQn) || (__IRQ == BusFault_IRQn) || (__IRQ == UsageFault_IRQn))
    {
        bitRST(*SHPR1, 0b1111, (((__IRQ + 12)*8) + 4));
        bitSET(*SHPR1, __PRIORITY, (((__IRQ + 12)*8) + 4));
    }
    
    if(__IRQ == SVCall_IRQn)
    {
        bitRST(*SHPR2, 0b1111, (24 + 4));
        bitSET(*SHPR2, __PRIORITY, (24 + 4));
    }

    if((__IRQ == PendSV_IRQn) || (__IRQ == SysTick_IRQn))
    {
        bitRST(*SHPR3, 0b1111, (((__IRQ + 4)*8) + 4));
        bitSET(*SHPR3, __PRIORITY, (((__IRQ + 4)*8) + 4));
    }

    return 0;
}

