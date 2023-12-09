/************************************************************************************
 *
 *								[SPI - TqK]
 *
 ************************************************************************************/

#ifndef __SPI_H_
#define __SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PRIVATE INCLUDE --------------------------------------------------------------
_________________________________________________________________________________*/
#include "UserDefine.h"



/* PRIVATE MACRO --------------------------------------------------------------
_________________________________________________________________________________*/

#define spiReadIndex		1
#define spiWriteIndex		0

/* PRIVATE TYPEDEF --------------------------------------------------------------
_________________________________________________________________________________*/

typedef struct
{
	char rxByte;
	char rxBuff[2];
	char txByte;

	unsigned char rxFlagDone;
	unsigned char txFlagDone;

	unsigned char cntRx;
	unsigned char cntTx;

	unsigned char cmdIndex;
} __Spi1_typedef;

//__Spi1_typedef _spi1;

/* PRIVATE ROUTINES DECLARE -----------------------------------------------------
_________________________________________________________________________________*/

/*[SPI1] -----------------------------------------------------------*/
/*__________________________________________________________________*/
int Spi1_init();
int Spi1_txByte(__Spi1_typedef *_spi1, char __DATA);
int Spi1_rxByte(__Spi1_typedef *_spi1);


/*[SPI1]__INTERRUPT ---------------------------*/
int Spi1_interruptInit();
int Spi1_interruptTx(unsigned char __STATE);
int Spi1_interruptRx(unsigned char __STATE);

int Spi1_intRxByte();
int Spi1_intTxByte(__Spi1_typedef *_spi1, char __DATA);

/*[GPIO] -----------------------------------------------------------*/
/*__________________________________________________________________*/
int PA5_spi1CLKinit();
int PA6_spi1MISOinit();
int PA7_spi1MOSIinit();
int PE3_spi1SSinit();
int PE3_spi1write(unsigned char __STATE);


/* PRIVATE VARIABLES DECLARE ----------------------------------------------------
_________________________________________________________________________________*/


#ifdef __cplusplus
}
#endif

#endif /* __SPI_H_ */
