/************************************************************************************
 *
 *										[RCC - TqK]
 *
 ************************************************************************************/

#ifndef __RCC_H
#define __RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"


/* DEFINES -------------------------------------------------------------------*/
#define RCC_AddBase			0x40023800




/* TYPEDEFS ---------------------------------------------------------------------*/

typedef enum
{
	CR 			= 0x00,				// RCC clock control register
	PLLCFGR 	= 0x04,				// RCC PLL configuration register
	CFGR 		= 0x08,				// RCC clock configuration register
	CIR 		= 0x0C,				// RCC clock interrupt register
	AHB1RSTR 	= 0x10,				// RCC AHB1 peripheral reset register
	AHB2RSTR 	= 0x14,				// RCC AHB2 peripheral reset register
	APB1RSTR 	= 0x20,				// RCC APB1 peripheral reset register
	APB2RSTR 	= 0x24,				// RCC APB2 peripheral reset register
	AHB1ENR 	= 0x30,				// RCC AHB1 peripheral clock enable register
	AHB2ENR 	= 0x34,				// RCC AHB2 peripheral clock enable register
	APB1ENR 	= 0x40,				// RCC APB1 peripheral clock enable register
	APB2ENR 	= 0x44,				// RCC APB2 peripheral clock enable register
	AHB1LPENR 	= 0x50,				// RCC AHB1 peripheral clock enable in low power mode register
	AHB2LPENR 	= 0x54,				// RCC AHB2 peripheral clock enable in low power mode register
	APB1LPENR 	= 0x60,				// RCC APB1 peripheral clock enable in low power mode register
	APB2LPENR 	= 0x64,				// RCC APB2 peripheral clock enabled in low power mode register
	BDCR 		= 0x70,				// RCC Backup domain control register
	CSR 		= 0x74,				// RCC clock control & status register
	SSCGR 		= 0x80,				// RCC spread spectrum clock generation register
	PLLI2SCFGR 	= 0x84,				// RCC PLLI2S configuration register
	DCKCFGR 	= 0x8C,				// RCC Dedicated Clocks Configuration Register
} Rcc_Typedef;


typedef enum
{
	PllSrc_HSI = 0,
	PllSrc_HSE,
} PllSrc_Typedef;


typedef enum
{
	SysSrc_HSI = 0b00,
	SysSrc_HSE = 0b01,
	SysSrc_PLL = 0b10,
} SysSrc_Typedef;


typedef enum
{
	GpioA = 0,
	GpioB,
	GpioC,
	GpioD,
	GpioE,
	GpioH = 7,
} GpioClock_Typdef;


typedef enum
{
	Dma1 = 21,
	Dma2,
} DmaClock_Typedef;


typedef enum
{
	TIMER2 = 0,
	TIMER3,
	TIMER4,
	TIMER5,

	TIMER1 = 16,
	TIMER9 = 32,
	TIMER10,
	TIMER11,
} TimerClock_Typedef;


typedef enum
{
	Usart2 = 17,
	Usart1 = 4,
	Usart6,
} UsartClock_Typdef;


typedef enum
{
	I2c1 = 21,
	I2c2,
	I2c3,
} I2cClock_Typedef;


typedef enum
{
	Spi2 = 14,
	Spi3,
	Spi1 = 12,
	Spi4,
	Spi5 = 20
} SpiClock_Typedef;

typedef enum
{
	Disable = 0,
	Enable,
} Ctrl_Typedef;


/* VARIABLES | CONSTANTS -----------------------------------------------------*/




/* VARIABLES -----------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/
int Rcc_Init(unsigned char __PLLM, unsigned short __PLLN, unsigned char __PLLP);
int PLL_Disable();
int PLL_Enable();
int PLL_SRC(PllSrc_Typedef __SRCCLK);
int PLL_setPLLM(unsigned char __PLLM);
int PLL_setPLLN(unsigned short __PLLN);
int PLL_setPLLP(unsigned char __PLLP);
int SysClockSwitch(SysSrc_Typedef __SRCCLK);
int HSE_Enable();
int HSE_Disable();
int HSI_Enable();
int HSI_Disable();

int FlashAccessTime(unsigned char __WAITSTATE);

// [GPIO CLOCK SET UP] --------------------------------------------
int GpioClock(GpioClock_Typdef __GPIO, Ctrl_Typedef __STATE);

// [DMA CLOCK SET UP] --------------------------------------------
int DmaClock(DmaClock_Typedef __DMA, Ctrl_Typedef __STATE);

// [CRC CLOCK SET UP] --------------------------------------------
int CrcClock(Ctrl_Typedef __STATE);

// [USB OTG CLOCK SET UP] --------------------------------------------
int UsbOtgClock(Ctrl_Typedef __STATE);

// [TIMER CLOCK SET UP] --------------------------------------------
int TimerClock(TimerClock_Typedef __TIM, Ctrl_Typedef __STATE);

// [USART CLOCK SET UP] --------------------------------------------
int UsartClock(UsartClock_Typdef __USART, Ctrl_Typedef __STATE);

// [I2C CLOCK SET UP] --------------------------------------------
int I2cClock(I2cClock_Typedef __I2C, Ctrl_Typedef __STATE);

// [SPI CLOCK SET UP] --------------------------------------------
int SpiClock(SpiClock_Typedef __SPI, Ctrl_Typedef __STATE);

// [WWDG CLOCK SET UP] --------------------------------------------
int WwdgClock(Ctrl_Typedef __STATE);

// [PWR CLOCK SET UP] --------------------------------------------
int PwrClock(Ctrl_Typedef __STATE);

// [ADC CLOCK SET UP] --------------------------------------------
int AdcClock(Ctrl_Typedef __STATE);

// [SDIO CLOCK SET UP] --------------------------------------------
int SdioClock(Ctrl_Typedef __STATE);

// [SYSCFG CLOCK SET UP] --------------------------------------------
int SysCfgClock(Ctrl_Typedef __STATE);


#ifdef __cplusplus
}
#endif

#endif /* __RCC_H */
