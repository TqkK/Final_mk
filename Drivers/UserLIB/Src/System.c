/************************************************************************************
 *
 *									[SYSTEM - TqK]
 *
 ************************************************************************************/


/*
 * INCLUDES ------------------------------------------------------------------
 _____________________________________________________________________________*/
// #include "../Inc/System.h"
#include "System.h"



/*
 * VARIABLES ------------------------------------------------------------------
 _____________________________________________________________________________*/



/*
 * FUNCTIONS ------------------------------------------------------------------
 _____________________________________________________________________________*/

/*
 * @brief	: System initialize
 * @param	: None
 * @retval	: None
 */
void SystemInit(void)
{


	//--- Set HSE for system clock with 16 Mhz

		// ### Set AHB, APB1, APB2 prescaler
		AHBprescaler(AHB_Div4);
		APB2prescaler(APB_Div1);
		APB1prescaler(APB_Div1);

#if ( __use_HSE == 1 )
	unsigned char __PLLM = 4;
	unsigned short __PLLN = 64;

	Rcc_Init(__PLLM, __PLLN, PLLP_Div2);
#endif

	//--- Set ratio of the CPU clock period to the Flash memory access time
	FlashAccessTime(0);

	//--- Power interface clock enable
	PWR_CLK_ENABLE;

	//--- System configuration controller clock enable
	SYSCFG_CLK_ENABLE;


	//--- Enable clock Serial Wire (GPIO A)
	GPIOA_CLK_ENABLE;

	
#if ( __use_SYSTICK == 1 )
	//--- Initialize SysTick	|	F = 16Mhz
	unsigned int __ReloadVALUE = 16000;
	SysTick_Init(__ReloadVALUE);
	SYSTICK_ENABLE;
#endif

}

void _close(void){}
void _lseek(void){}
void _read(void){}
void _write(void){}

void _kill(void){}
void _isatty(void){}
void _getpid(void){}
void _fstat(void){}

// __attribute__((weak)) void _close(void){}
// __attribute__((weak)) void _lseek(void){}
// __attribute__((weak)) void _read(void){}
// __attribute__((weak)) void _write(void){}