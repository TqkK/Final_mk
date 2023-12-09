/************************************************************************************
 *
 *									    [ADC - TqK]
 *
 ************************************************************************************/


#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* INCLUDES ------------------------------------------------------------------*/

#include "UserDefine.h"
#include "Rcc.h"


/* DEFINES -------------------------------------------------------------------*/
#define ADC1_AddBase        0x40012000


/* TYPEDEF -------------------------------------------------------------------*/
typedef enum
{
    adc_SR = 0,                         // ADC status register
    adc_CR1 = 0x04,                     // ADC control register 1
    adc_CR2 = 0x08,                     // ADC control register 2
    adc_SMPR1 = 0x0C,                   // ADC sample time register 1
    adc_SMPR2 = 0x10,                   // ADC sample time register 2
    adc_JOFR1 = 0x14,                   // ADC injected channel data offset register 1
    adc_JOFR2 = 0x18,                   // ADC injected channel data offset register 2
    adc_JOFR3 = 0x1C,                   // ADC injected channel data offset register 3
    adc_JOFR4 = 0x20,                   // ADC injected channel data offset register 4
    adc_HTR = 0x24,                     // ADC watchdog higher threshold register
    adc_LTR = 0x28,                     // ADC watchdog lower threshold register
    adc_SQR1 = 0x2C,                    // ADC regular sequence register 1
    adc_SQR2 = 0x30,                    // ADC regular sequence register 2
    adc_SQR3 = 0x34,                    // ADC regular sequence register 3
    adc_JSQR = 0x38,                    // ADC injected sequence register
    adc_JDR1 = 0x3C,                    // ADC injected data register 1
    adc_JDR2 = 0x40,                    // ADC injected data register 2
    adc_JDR3 = 0x44,                    // ADC injected data register 3
    adc_JDR4 = 0x48,                    // ADC injected data register 4
    adc_DR = 0x4C,                      // ADC regular data register
    adc_CCR = 0x300 + 0x04,             // ADC common control register
} Adc1Reg_typedef;


typedef enum
{
    adc_12bit = 0,
    adc_10bit,
    adc_8bit,
    adc_6bit,
} Adc1Resolution_typedef;


typedef enum
{
    adc_Div2 = 0,
    adc_Div4,
    adc_Div6,
    adc_Div8,
} AdcPrescaler_typedef;

typedef enum
{
    adc_RightAlignment = 0,
    adc_LeftAlignment,
} Adc1DataAlignment_typedef;

typedef enum
{
    adc_SingleMode = 0,
    adc_ContinuousMode,
} Adc1ConversionMode_typedef;


typedef enum
{
    adc_3cycles = 0,
    adc_15cycles,
    adc_28cycles,
    adc_56cycles,
    adc_84cycles,
    adc_112cycles,
    adc_144cycles,
    adc_480cycles,
} Adc1SampleTime_typedef;
/* MACRO ---------------------------------------------------------------------*/





/* VARIABLES -----------------------------------------------------------------*/




/* FUNCTIONS PROTOTYPES ------------------------------------------------------*/
int Adc_Init();
int Adc_Enable();
int Adc_Disable();
int Adc_Prescaler(AdcPrescaler_typedef __PRESCALE);
int Adc_Resolution(Adc1Resolution_typedef __RESOLUTION);
int Adc_StartInjected(Ctrl_Typedef __STATE);
int Adc_DataAlignment(Adc1DataAlignment_typedef __VALUE);
int Adc_SampleTime(unsigned char __CHANNEL, Adc1SampleTime_typedef __VALUE);
int Adc_ConversionMode(Adc1ConversionMode_typedef __MODE);
int Adc_InjectedSequenceLength(unsigned char __LENGTH, unsigned char __CHANNEL);
unsigned short Adc_InjectedData(unsigned char __NUMERICAL);


#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */
