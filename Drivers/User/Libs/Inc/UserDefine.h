/************************************************************************************************
 * 										[Tqk]_UserDefine.h									   *
 *																							   *
 *      									Author: [Tqk]									   *
*************************************************************************************************/

#ifndef __USERDEFINE_H_
#define __USERDEFINE_H_

#include "stm32f4xx_hal.h"
//#include "rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* PRIVATE MACRO -----------------------------------------------------------------
_________________________________________________________________________________*/

//#define SET(_register , _index, _pos)		(_register |= (_index << _pos))
//#define RST(_register , _index, _pos)		(_register &= ~(_index << _pos))
//
//#define VALUE(_register, _pos)				((_register >> _pos) & 0x01)

#define bitSET(_register , _index, _pos)		(_register |= (_index << _pos))
#define bitRST(_register , _index, _pos)		(_register &= ~(_index << _pos))
#define bitVALUE(_register, _pos)				((_register >> _pos) & 0x01)
#define regWRITE(_register, _data)				(_register = _data)



#ifdef __cplusplus
}
#endif

#endif /* __USERDEFINE_H_ */
