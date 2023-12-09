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
	rcc_CR 			= 0x00,				// RCC clock control register
	rcc_PLLCFGR 	= 0x04,				// RCC PLL configuration register
	rcc_CFGR 		= 0x08,				// RCC clock configuration register
	rcc_CIR 		= 0x0C,				// RCC clock interrupt register
	rcc_AHB1RSTR 	= 0x10,				// RCC AHB1 peripheral reset register
	rcc_AHB2RSTR 	= 0x14,				// RCC AHB2 peripheral reset register
	rcc_APB1RSTR 	= 0x20,				// RCC APB1 peripheral reset register
	rcc_APB2RSTR 	= 0x24,				// RCC APB2 peripheral reset register
	rcc_AHB1ENR 	= 0x30,				// RCC AHB1 peripheral clock enable register
	rcc_AHB2ENR 	= 0x34,				// RCC AHB2 peripheral clock enable register
	rcc_APB1ENR 	= 0x40,				// RCC APB1 peripheral clock enable register
	rcc_APB2ENR 	= 0x44,				// RCC APB2 peripheral clock enable register
	rcc_AHB1LPENR 	= 0x50,				// RCC AHB1 peripheral clock enable in low power mode register
	rcc_AHB2LPENR 	= 0x54,				// RCC AHB2 peripheral clock enable in low power mode register
	rcc_APB1LPENR 	= 0x60,				// RCC APB1 peripheral clock enable in low power mode register
	rcc_APB2LPENR 	= 0x64,				// RCC APB2 peripheral clock enabled in low power mode register
	rcc_BDCR 		= 0x70,				// RCC Backup domain control register
	rcc_CSR 		= 0x74,				// RCC clock control & status register
	rcc_SSCGR 		= 0x80,				// RCC spread spectrum clock generation register
	rcc_PLLI2SCFGR 	= 0x84,				// RCC PLLI2S configuration register
	rcc_DCKCFGR 	= 0x8C,				// RCC Dedicated Clocks Configuration Register
} RccReg_Typedef;


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
	Timer2 = 0,
	Timer3,
	Timer4,
	Timer5,

	Timer1 = 16,
	Timer9 = 32,
	Timer10,
	Timer11,
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
	AHB_Div1 = 0,
	AHB_Div2 = 0b1000,
	AHB_Div4 = 0b1001,
	AHB_Div8 = 0b1010,
	AHB_Div16 = 0b1011,
	AHB_Div64 = 0b1100,
	AHB_Div128 = 0b1101,
	AHB_Div256 = 0b1110,
	AHB_Div512 = 0b1111,
} AHBprescaler_Typedef;

typedef enum
{
	APB_Div1 = 0,
	APB_Div2 = 0b100,
	APB_Div4 = 0b101,
	APB_Div8 = 0b110,
	APB_Div16 = 0b111,
} APBprescaler_Typedef;

typedef enum
{
	PLLP_Div2 = 0,
	PLLP_Div4 = 0b01,
	PLLP_Div6 = 0b10,
	PLLP_Div8 = 0b11,
} PLLPdiv_typedef;

/* MACRO ---------------------------------------------------------------------*/

#define GPIOA_CLK_ENABLE		GpioClock(GpioA, Enable)
#define GPIOB_CLK_ENABLE		GpioClock(GpioB, Enable)
#define GPIOC_CLK_ENABLE		GpioClock(GpioC, Enable)
#define GPIOD_CLK_ENABLE		GpioClock(GpioD, Enable)
#define GPIOE_CLK_ENABLE		GpioClock(GpioE, Enable)
#define GPIOH_CLK_ENABLE		GpioClock(GpioH, Enable)

#define GPIOA_CLK_DISABLE		GpioClock(GpioA, Disable)
#define GPIOB_CLK_DISABLE		GpioClock(GpioB, Disable)
#define GPIOC_CLK_DISABLE		GpioClock(GpioC, Disable)
#define GPIOD_CLK_DISABLE		GpioClock(GpioD, Disable)
#define GPIOE_CLK_DISABLE		GpioClock(GpioE, Disable)
#define GPIOH_CLK_DISABLE		GpioClock(GpioH, Disable)


#define PWR_CLK_ENABLE			PwrClock(Enable)
#define PWR_CLK_DISABLE			PwrClock(Disable)

#define SYSCFG_CLK_ENABLE		SysCfgClock(Enable)
#define SYSCFG_CLK_DISABLE		SysCfgClock(Disable)


#define DMA1_CLK_ENABLE			DmaClock(Dma1, Enable)
#define DMA2_CLK_ENABLE			DmaClock(Dma2, Enable)

#define DMA1_CLK_DISABLE		DmaClock(Dma1, Disable)
#define DMA2_CLK_DISABLE		DmaClock(Dma2, Disable)

#define CRC_CLK_ENABLE			CrcClock(Enable)
#define CRC_CLK_DISABLE			CrcClock(Disable)

#define USB_OTG_CLK_ENABLE		UsbOtgClock(Enable)
#define USB_OTC_CLK_DISABLE		UsbOtgClock(Disable)

#define Timer1_CLK_ENABLE		TimerClock(Timer1, Enable)
#define Timer2_CLK_ENABLE		TimerClock(Timer2, Enable)
#define Timer3_CLK_ENABLE		TimerClock(Timer3, Enable)
#define Timer4_CLK_ENABLE		TimerClock(Timer4, Enable)
#define Timer5_CLK_ENABLE		TimerClock(Timer5, Enable)
#define Timer9_CLK_ENABLE		TimerClock(Timer9, Enable)
#define Timer10_CLK_ENABLE		TimerClock(Timer10, Enable)
#define Timer11_CLK_ENABLE		TimerClock(Timer11, Enable)

#define Timer1_CLK_DISABLE		TimerClock(Timer1, Disable)
#define Timer2_CLK_DISABLE		TimerClock(Timer2, Disable)
#define Timer3_CLK_DISABLE		TimerClock(Timer3, Disable)
#define Timer4_CLK_DISABLE		TimerClock(Timer4, Disable)
#define Timer5_CLK_DISABLE		TimerClock(Timer5, Disable)
#define Timer9_CLK_DISABLE		TimerClock(Timer9, Disable)
#define Timer10_CLK_DISABLE		TimerClock(Timer10, Disable)
#define Timer11_CLK_DISABLE		TimerClock(Timer11, Disable)

#define USART1_CLK_ENABLE		UsartClock(Usart1, Enable)
#define USART2_CLK_ENABLE		UsartClock(Usart2, Enable)
#define USART6_CLK_ENABLE		UsartClock(Usart6, Enable)

#define USART1_CLK_DISABLE		UsartClock(Usart1, Disable)
#define USART2_CLK_DISABLE		UsartClock(Usart2, Disable)
#define USART6_CLK_DISABLE		UsartClock(Usart6, Disable)

#define ADC1_CLK_ENABLE			AdcClock(Enable)
#define ADC1_CLK_DISABLE		AdcClock(Disable)

#define SDIO_CLK_ENABLE			SdioClock(Enable)
#define SDIO_CLK_DISABLE		SdioClock(Disable)


#define SPI1_CLK_ENABLE			SpiClock(Spi1, Enable)
#define SPI2_CLK_ENABLE			SpiClock(Spi2, Enable)
#define SPI3_CLK_ENABLE			SpiClock(Spi3, Enable)
#define SPI4_CLK_ENABLE			SpiClock(Spi4, Enable)
#define SPI5_CLK_ENABLE			SpiClock(Spi5, Enable)

#define SPI1_CLK_DISABLE		SpiClock(Spi1, Disable)
#define SPI2_CLK_DISABLE		SpiClock(Spi2, Disable)
#define SPI3_CLK_DISABLE		SpiClock(Spi3, Disable)
#define SPI4_CLK_DISABLE		SpiClock(Spi4, Disable)
#define SPI5_CLK_DISABLE		SpiClock(Spi5, Disable)


#define WWDG_CLK_ENABLE			WwdgClock(Enable)
#define WWDG_CLK_DISABLE		WwdgClock(Disable)

#define USART1_CLK_ENABLE		UsartClock(Usart1, Enable)
#define USART2_CLK_ENABLE		UsartClock(Usart2, Enable)
#define USART6_CLK_ENABLE		UsartClock(Usart6, Enable)

#define USART1_CLK_DISABLE		UsartClock(Usart1, Disable)
#define USART2_CLK_DISABLE		UsartClock(Usart2, Disable)
#define USART6_CLK_DISABLE		UsartClock(Usart6, Disable)

#define I2C1_CLK_ENABLE			I2cClock(I2c1, Enable)
#define I2C2_CLK_ENABLE			I2cClock(I2c2, Enable)
#define I2C3_CLK_ENABLE			I2cClock(I2c3, Enable)

#define I2C1_CLK_DISABLE		I2cClock(I2c1, Disable)
#define I2C2_CLK_DISABLE		I2cClock(I2c2, Disable)
#define I2C3_CLK_DISABLE		I2cClock(I2c3, Disable)

/* VARIABLES ------------------------------------------------------------------*/



/* VARIABLES | CONSTANTS -------------------------------------------*/



/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/
int Rcc_Init(unsigned char __PLLM, unsigned short __PLLN, unsigned char __PLLP);
int PLL_Disable();
int PLL_Enable();
int PLL_SRC(PllSrc_Typedef __SRCCLK);
int PLL_setPLLM(unsigned char __PLLM);
int PLL_setPLLN(unsigned short __PLLN);
int PLL_setPLLP(PLLPdiv_typedef __PLLP);
int SysClockSwitch(SysSrc_Typedef __SRCCLK);
int HSE_Enable();
int HSE_Disable();
int HSI_Enable();
int HSI_Disable();

int LSI_Enable();
int LSI_Disable();

int GpioClock(GpioClock_Typdef __GPIO, Ctrl_Typedef __STATE);
int DmaClock(DmaClock_Typedef __DMA, Ctrl_Typedef __STATE);
int CrcClock(Ctrl_Typedef __STATE);
int UsbOtgClock(Ctrl_Typedef __STATE);
int TimerClock(TimerClock_Typedef __TIM, Ctrl_Typedef __STATE);
int UsartClock(UsartClock_Typdef __USART, Ctrl_Typedef __STATE);
int I2cClock(I2cClock_Typedef __I2C, Ctrl_Typedef __STATE);
int SpiClock(SpiClock_Typedef __SPI, Ctrl_Typedef __STATE);
int WwdgClock(Ctrl_Typedef __STATE);
int PwrClock(Ctrl_Typedef __STATE);
int AdcClock(Ctrl_Typedef __STATE);
int SdioClock(Ctrl_Typedef __STATE);
int SysCfgClock(Ctrl_Typedef __STATE);
int AHBprescaler(AHBprescaler_Typedef __DIV);
int APB1prescaler(APBprescaler_Typedef __DIV);
int APB2prescaler(APBprescaler_Typedef __DIV);



#ifdef __cplusplus
}
#endif

#endif /* __RCC_H */
