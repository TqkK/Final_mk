/************************************************************************************
 *
 *										[GPIO - TqK]
 *
 ************************************************************************************/

/*
 * INCLUDES ------------------------------------------------------------------
 _____________________________________________________________________________*/
// #include "../Inc/Gpio.h"
 #include "Gpio.h"


/*
 * VARIABLES ------------------------------------------------------------------
 _____________________________________________________________________________*/



/*
 * FUNCTIONS ------------------------------------------------------------------
 _____________________________________________________________________________*/

// [PD12 ]	==================================

/*
 * @Brief	: PD12 | GREEN LED initialize
 */
int PD12_ouputInit()
{
	//--- Enable GPIO D clock
	// GpioClock(GpioD, Enable);
	GPIOD_CLK_ENABLE;

	//--- bitSET GPIO_MODER == output
	unsigned int *GPIOD_MODER = (unsigned int *)(0x40020c00);
	bitRST(*GPIOD_MODER, 0b11, 24);
	bitSET(*GPIOD_MODER, 0b01, 24);

	//--- bitSET GPIO_OTYPER == push-pull
	unsigned int *GPIOD_OTYPER = (unsigned int *)(0x40020c04);
	bitRST(*GPIOD_OTYPER, 1, 12);

	//--- bitSET GPIO_OPSEEDR == medium speed
	unsigned int *GPIOD_OSPEEDR = (unsigned int *)(0x40020c08);
	bitRST(*GPIOD_OSPEEDR, 0b11, 24);
	bitSET(*GPIOD_OSPEEDR, 0b01, 24);

	return 0;
}

/*
 * @Brief	: PD12 | GREEN LED output control
 */
int PD12_outputWrite(unsigned char __STATE)
{
	unsigned int *GPIOD_ODR = (unsigned int *)(0x40020c14);
	bitRST(*GPIOD_ODR, 0b1, 12);
	bitSET(*GPIOD_ODR, __STATE, 12);

	return 0;
}


// [PD14 ]	==================================

/*
 * @Brief	: PD14 | RED LED initialize
 */
int PD14_ouputInit()
{
	//--- Enable GPIO D clock
	// GpioClock(GpioD, Enable);
	GPIOD_CLK_ENABLE;

	//--- bitSET GPIO_MODER == output
	unsigned int *GPIOD_MODER = (unsigned int *)(0x40020c00);
	bitRST(*GPIOD_MODER, 0b11, 28);
	bitSET(*GPIOD_MODER, 0b01, 28);

	//--- bitSET GPIO_OTYPER == push-pull
	unsigned int *GPIOD_OTYPER = (unsigned int *)(0x40020c04);
	bitRST(*GPIOD_OTYPER, 1, 14);

	//--- bitSET GPIO_OPSEEDR == medium speed
	unsigned int *GPIOD_OSPEEDR = (unsigned int *)(0x40020c08);
	bitRST(*GPIOD_OSPEEDR, 0b11, 28);
	bitSET(*GPIOD_OSPEEDR, 0b01, 28);

	return 0;
}

/*
 * @Brief	: PD14 | RED LED output control
 */
int PD14_outputWrite(unsigned char __STATE)
{
	unsigned int *GPIOD_ODR = (unsigned int *)(0x40020c14);
	bitRST(*GPIOD_ODR, 0b1, 14);
	bitSET(*GPIOD_ODR, __STATE, 14);

	return 0;
}

// [PD15 ]	==================================

/*
 * @Brief	: PD15 | BLUE LED initialize
 */
int PD15_ouputInit()
{
	//--- Enable GPIO D clock
	// GpioClock(GpioD, Enable);
	GPIOD_CLK_ENABLE;

	//--- bitSET GPIO_MODER == output
	unsigned int *GPIOD_MODER = (unsigned int *)(0x40020c00);
	bitRST(*GPIOD_MODER, 0b11, 30);
	bitSET(*GPIOD_MODER, 0b01, 30);

	//--- bitSET GPIO_OTYPER == push-pull
	unsigned int *GPIOD_OTYPER = (unsigned int *)(0x40020c04);
	bitRST(*GPIOD_OTYPER, 1, 15);

	//--- bitSET GPIO_OPSEEDR == medium speed
	unsigned int *GPIOD_OSPEEDR = (unsigned int *)(0x40020c08);
	bitRST(*GPIOD_OSPEEDR, 0b11, 30);
	bitSET(*GPIOD_OSPEEDR, 0b01, 30);

	return 0;
}

/*
 * @Brief	: PD15 | BLUE LED output control
 */
int PD15_outputWrite(unsigned char __STATE)
{
	unsigned int *GPIOD_ODR = (unsigned int *)(0x40020c14);
	bitRST(*GPIOD_ODR, 0b1, 15);
	bitSET(*GPIOD_ODR, __STATE, 15);

	return 0;
}


// [PA0 ]	==================================

/*
 * @Brief	: PA0 | Button initialize
 */
int PA0_inputInit()
{
	//--- Enable GPIO A clock
	GPIOA_CLK_ENABLE;

	//--- bitSET GPIO_MODER == input
	unsigned int *moder = (unsigned int *)(0x40020000);
	bitRST(*moder, 0b11, 0);
	bitSET(*moder, 0b00, 0);

	//--- bitSET GPIO_PUPD == no PUPD
	unsigned int *pupd  = (unsigned int *)(0x4002000c);
	bitRST(*pupd, 0b11, 0);
	bitSET(*pupd, 0b00, 0);

	return 0;
}

/*
 * @Brief	: PA0 | Button state read
 */
unsigned char PA0_inputState()
{
	unsigned int *idr = (unsigned int *)(0x40020010);
	return bitVALUE(*idr, 0);
}