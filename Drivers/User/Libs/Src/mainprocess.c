/************************************************************************************
 *
 *								[MainProcess - TqK]
 *
 ************************************************************************************/

#include "mainprocess.h"

unsigned char gyroID = 0, gyroCTRL1 = 0, _gyroCTRL1 = 0;
unsigned char state = 0;
unsigned int PwmARR = 0;
unsigned int PwmPulseWidth = 0;

/* PRIVATE MACRO --------------------------------------------------------------
_________________________________________________________________________________*/
#define PD12_ON			PD12_outWrite(1)
#define PD12_OFF		PD12_outWrite(0)


//--- [TEST] uart1
//#define RamVttbAdr	0x20000000

//--- [TEST] spi1


//--- [TEST] i2c1



/* PRIVATE VARIABLES --------------------------------------------------------------
_________________________________________________________________________________*/

//--- [TEST] uart1
//unsigned int *uart1_handler_address = 0;
//unsigned int sizeBin = 0;
//char recvData[10] = {0};
//unsigned int uartDR = 0;

//--- [TEST] i2c1
//unsigned char acc_WHOAMI = 0;
//unsigned char data[7] = {0};

//--- [TEST] timer1

//SoftTimer_typedef usrTimer1;
//Timer1Data _timer1;


//--- [TEST] PWM
unsigned int duty = 0;


/* PRIVATE DECLARE --------------------------------------------------------------
_________________________________________________________________________________*/
void MainProcessInit()
{
	//--- [SYSTEM CLOCK]
	unsigned char __PLLM = 8;
	unsigned short __PLLN = 32;
	unsigned char __PLLP = 0;
	Rcc_Init(__PLLM, __PLLN, __PLLP);

	//--- [TEST] gpio
	PD12_outInit();
//	PA0_inInit();

	//--- [TEST] exti0
//	Exti0_Init();

	//--- [TEST] vttb
//	CopyVttbToRam(RamVttbAdr, 0x198);
//	ModifyAddressFunction(RamVttbAdr, 0x00000058, (unsigned int)Exti0_Handler);


	//--- [TEST] uart1
	Uart1_init();
//	Uart1_ISRinit();
//	ModifyAddressFunction(RamVttbAdr, 0x000000D4, (unsigned int)Uart1_Handler);

//	ModifyAddressFunction(RamVttbAdr, 0x00000150, (unsigned int)Dma2Str5_Handler);
//	uart1_handler_address = (unsigned int)USART1_IRQHandler;

//	Uart1_printf("----------- UPDATE FIRM MODE -----------\r\n");
//	Uart1_printf("1. SIZE OF BIN FILE: \r\n");
//
//	int i = 0;
//	while(strstr(recvData, "\r\n") == NULL)
//	{
//	  recvData[i++] = Uart1_rxByte();
//	}
//	sscanf(recvData, "%d", &sizeBin);
//	Uart1_printf("%d", sizeBin);
//	Uart1_printf("tsts");


	//--- [TEST] spi1
//	Gyroscope_init();

//	gyroID = Gyroscope_ReadData(gyroWHO_AM_I);
//	Gyroscope_intReadData(gyroWHO_AM_I);
//	while(!gyroData.rxFlagDone);
//	gyroData.rxFlagDone = 0;
//	gyroID = gyroData.rxByte;
//
//	Gyroscope_intReadData(gyroCTRL_REG1);
//	while(!gyroData.rxFlagDone);
//	gyroData.rxFlagDone = 0;
//	gyroCTRL1 = gyroData.rxByte;
//
//
//	Gyroscope_intWriteData(gyroCTRL_REG1, 0x0F);
//	while(!gyroData.txFlagDone);
//	gyroData.txFlagDone = 0;
//
//	Gyroscope_intReadData(gyroCTRL_REG1);
//	while(!gyroData.rxFlagDone);
//	gyroData.rxFlagDone = 0;
//	_gyroCTRL1 = gyroData.rxByte;

//	Accelero_Init();
//	Accelero_ReadData(ACC_ADDR, ACC_WHO_AM_I, &acc_WHOAMI);
//	HAL_Delay(500);
//	unsigned char _ctrlREG1 = 0b00010111;
//	Accelero_WriteData(ACC_ADDR, ACC_CTRL_REG_1, &_ctrlREG1);

	//--- [TEST] timer1
	/* f = 16Mhz
	 * ARR = 999, PSC = 15
	 * --> delay 1s
	 */

//	Timer1_init(1000, 16);
//	Timer1_interruptInit();
//	Timer1_enable();


//	SoftTimer_init();


	//--- [TEST] PWM
//	Pwm_Init(75);

//	CountPwm_Init();
}


void MainProcessRun()
{
//	Accelero_ReadData(ACC_ADDR, 0x28, data);
//	Accelero_ReadData(ACC_ADDR, 0x29, (data+1));
//
//	Accelero_ReadData(ACC_ADDR, 0x2A, (data+2));
//	Accelero_ReadData(ACC_ADDR, 0x2B, (data+3));
//
//	Accelero_ReadData(ACC_ADDR, 0x2C, (data+4));
//	Accelero_ReadData(ACC_ADDR, 0x2D, (data+5));



//	if(Timer1_delay(&usrTimer1, 1000))
//	{
//		PD12_outWrite(stt);
//			stt = !stt;
//	}

	PD12_ON;
	Uart1_txByte('g');
//	while(!SoftTimer(&usrTimer1, 500));

	PD12_OFF;
//	while(!SoftTimer(&usrTimer1, 500));

//	if(duty++ >= 100)
//	{
//		duty = 0;
//	}
//	PWM_PulseWidth(duty);
//	while(!SoftTimer(&usrTimer1, 1000));

//	PwmARR = CountPwm_frequency();
//	PwmPulseWidth = CountPwm_pulseWidth();
//	while(!SoftTimer(&usrTimer1, 1000));
}
