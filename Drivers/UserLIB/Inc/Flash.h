/************************************************************************************
 *
 *									[FLASH - TqK]
 *
 ************************************************************************************/

#ifndef __FLASH_H
#define __FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"


/* DEFINES -------------------------------------------------------------------*/
#define FLASH_AddBase     0x40023C00


/* TYPEDEF -------------------------------------------------------------------*/
typedef enum
{
    flash_ACR = 0,
    flash_KEYR = 0x04,
    flash_OPTKEYR = 0x08,
    flash_SR = 0x0C,
    flash_CR = 0x10,
    flash_OPTCR = 0x14,
    
} FlashReg_typedef;


/* MACRO ---------------------------------------------------------------------*/




/* VARIABLES -----------------------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/
int FlashAccessTime(unsigned char __WAITSTATE);





#ifdef __cplusplus
}
#endif

#endif /* __FLASH_H */
