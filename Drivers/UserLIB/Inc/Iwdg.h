/************************************************************************************
 *
 *									[IWDG - TqK]
 *
 ************************************************************************************/

#ifndef __IWDG_H
#define __IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "Rcc.h"


/* DEFINES -------------------------------------------------------------------*/
#define IWDG_AddBase     0x40003000


/* TYPEDEF -------------------------------------------------------------------*/
typedef enum
{
    iwdg_KR = 0x00,         //  Key register
    iwdg_PR = 0x04,         //  Prescaler register
    iwdg_RLR = 0x08,        //  Reload register
    iwdg_SR = 0x0C,         //  Status register
} IwdgReg_typedef;


typedef enum
{
    iwdg_Div4 = 0,
    iwdg_Div8,
    iwdg_Div16,
    iwdg_Div32,
    iwdg_Div64,
    iwdg_Div128,
    iwdg_Div256,
} IwdgPrescale_typedef;

/* MACRO ---------------------------------------------------------------------*/

#define IWDG_WRITE_ENABLE      Iwdg_Key(0x5555)
#define IWDG_RESET              Iwdg_Key(0xAAAA)
#define IWDG_START              Iwdg_Key(0xCCCC)



/* VARIABLES -----------------------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/

int Iwdg_Init(IwdgPrescale_typedef __PRESCALE, unsigned short __VALUE);
int Iwdg_Prescaler(IwdgPrescale_typedef __PRESCALE);
int Iwdg_Reload(unsigned short __VALUE);
int Iwdg_Key(unsigned int __KEY);




#ifdef __cplusplus
}
#endif

#endif /* __IWDG_H */
