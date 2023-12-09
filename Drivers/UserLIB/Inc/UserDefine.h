/************************************************************************************
 *
 *									[USERDEFINE - TqK]
 *
 ************************************************************************************/

#ifndef __USERDEFINE_H_
#define __USERDEFINE_H_

/* INCLUDES ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* TYPEDEF ---------------------------------------------------------------------*/

typedef enum
{
	Disable = 0,
	Enable,
} Ctrl_Typedef;

/* MACRO ---------------------------------------------------------------------*/

#define bitSET(_register, _index, _pos)			(_register |= (_index << _pos))
#define bitRST(_register, _index, _pos)			(_register &= ~(_index << _pos))
#define bitVALUE(_register, _pos)				((_register >> _pos) & 0x01)
#define regWRITE(_register, _data)				(_register = _data)


#define __Use_FreeRTOS			1

#define __use_HSE				1

// #define __Use_ManSysTick

#endif /* __USERDEFINE_H_ */
