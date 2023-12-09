/************************************************************************************
 *
 *									[FLASH - TqK]
 *
 ************************************************************************************/

#include "Flash.h"

/*
 * @Brief	: Flash memory access time
 */
int FlashAccessTime(unsigned char __WAITSTATE)
{
	unsigned int *FLASH_ACR = (unsigned int *)(FLASH_AddBase + flash_ACR);
	bitRST(*FLASH_ACR, 0x0F, 0);

	bitSET(*FLASH_ACR, __WAITSTATE, 0);

	return 0;
}