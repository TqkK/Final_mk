/************************************************************************************
 *
 *									[IWDG - TqK]
 *
 ************************************************************************************/

// #include "../Inc/Iwdg.h"
#include "Iwdg.h"

/*
 * @Brief	: IWDG init
 */
int Iwdg_Init(IwdgPrescale_typedef __PRESCALE, unsigned short __VALUE)
{
    LSI_Enable();

    // IWDG_START;

    Iwdg_Prescaler(__PRESCALE);

    Iwdg_Reload(__VALUE);

    // IWDG_RESET;

    return 0;
}

/*
 * @Brief	: IWDG Prescaler
 */
int Iwdg_Prescaler(IwdgPrescale_typedef __PRESCALE)
{
    // unsigned int *IWDG_SR = (unsigned int *)(IWDG_AddBase + iwdg_SR);
    unsigned int *IWDG_PR = (unsigned int *)(IWDG_AddBase + iwdg_PR);

    //--- Enale access to the IWDG_PR
    IWDG_WRITE_ENABLE;

    //--- wait PVU bit reset to be able to change the prescale divider
    // while(bitVALUE(*IWDG_SR, 0));
    
    //--- set prescale
    *IWDG_PR = __PRESCALE;

    return 0;
}

/*
 * @Brief	: IWDG reload
 */
int Iwdg_Reload(unsigned short __VALUE)
{
    // unsigned int *IWDG_SR = (unsigned int *)(IWDG_AddBase + iwdg_SR);
    unsigned int *IWDG_RLR = (unsigned int *)(IWDG_AddBase + iwdg_RLR);
    
    //--- Enale access to the IWDG_RLR
    IWDG_WRITE_ENABLE;

    //--- wait PVU bit reset to be able to change the prescale divider
    // while(bitVALUE(*IWDG_SR, 1));

    //--- set reload value
    *IWDG_RLR = __VALUE;

    return 0;
}


/*
 * @Brief	: IWDG Unlock with key register
 */
int Iwdg_Key(unsigned int __KEY)
{
    unsigned int *IWDG_KR = (unsigned int *)(IWDG_AddBase + iwdg_KR);    

    *IWDG_KR = __KEY;

    return 0;
}