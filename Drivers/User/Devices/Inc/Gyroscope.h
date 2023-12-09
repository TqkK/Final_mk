/************************************************************************************
 *
 *								[GYROSCOPE - TqK]
 *
 ************************************************************************************/

#ifndef __GYROSCOPE_H_
#define __GYROSCOPE_H_


#ifdef __cplusplus
extern "C" {
#endif

/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/

#include "spi.h"


/* PRIVATE MACRO --------------------------------------------------------------
_________________________________________________________________________________*/

#define gyroReadCMD(_cmd)		bitSET(_cmd , 1, 7)
#define gyroWriteCMD(_cmd)		bitRST(_cmd , 1, 7)
#define gyroIncreAddress(_cmd)	bitSET(_cmd , 1, 6)

#define gyroWHO_AM_I		0x0F
#define gyroCTRL_REG1		0x20

#define gyroReadIndex		spiReadIndex
#define gyroWriteIndex		spiWriteIndex

/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/




/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/
int Gyroscope_init();
char Gyroscope_ReadData(char __REG);
int Gyroscope_WriteData(char __REG, char __DATA);

/* [For INTERRUPT] __________________________________*/
int Gyroscope_intReadData(char __REG);
int Gyroscope_intWriteData(char __REG, char __DATA);
void SPI1_IRQHandler();

/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/

extern __Spi1_typedef gyroData;


#ifdef __cplusplus
}
#endif

#endif /* __GYROSCOPE_H_ */
