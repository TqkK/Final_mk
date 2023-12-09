/************************************************************************************
 *
 *								[I2C - TqK]
 *
 ************************************************************************************/


#ifndef __I2C_H_
#define __I2C_H_



#ifdef __cplusplus
extern "C" {
#endif

/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/
#include "UserDefine.h"



/* PRIVATE MACRO --------------------------------------------------------------
_________________________________________________________________________________*/

#define cmdI2cWrite		0
#define cmdI2cRead		1

/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/

typedef struct
{
	unsigned char txFlagDone;
	unsigned char rxFlagDone;

	unsigned char rxByte;
}__i2c1_typedef;

/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/

/*[GPIO] -----------------------------------------------------------*/
/*__________________________________________________________________*/

int PB6_i2c1SCLinit();
int PB9_i2c1SDAinit();


/*[I2C] -----------------------------------------------------------*/
/*__________________________________________________________________*/

int I2C1_init();
int I2C1_enable();
int I2C1_disable();
int I2C1_masterTransmit(char __addrSLAVE, char __addrREG, unsigned char *__DATA);
int I2C1_masterReceive(char __addrSLAVE, char __addrREG, char *__retDATA);

/* [DMA 1] -------------------------------------------*/

// [I2C1_rx | Stream 5 | Channel 1] ----------

int I2C1_rxDmaInit(__i2c1_typedef *__i2c1);
int I2C1_rxDMAenable();
int DMA1_Stream5_ClearPending();
void DMA1_Stream5_IRQHandler();

/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/

extern unsigned char _i2c1RxByte;

#ifdef __cplusplus
}
#endif


#endif /* __I2C_H_ */
