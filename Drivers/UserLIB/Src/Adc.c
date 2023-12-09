/************************************************************************************
 *
 *									    [ADC - TqK]
 *
 ************************************************************************************/

#include "Adc.h"

/*
*   Brief: ADC init
*/
int Adc_Init()
{
    //--- ADC clock enable
    ADC1_CLK_ENABLE;

    //--- ADC Power down mode
    Adc_Disable();

    //--- Set ADC prescaler
    Adc_Prescaler(adc_Div2);

    //--- Set 12bit resolution
    Adc_Resolution(adc_12bit);

    //--- Set sampling cycle = 480 for channel 16
    Adc_SampleTime(16, adc_480cycles);

    //--- Set right alignment
    Adc_DataAlignment(adc_RightAlignment);

    //--- Set Injected sequence length == 1 conversion and choose channel 16
    Adc_InjectedSequenceLength(0, 16);

    return 0;
}

/*
*   Brief: ADC Converter ON / OFF
*/
int Adc_Enable()
{
    unsigned int *ADC_CR2 = (unsigned int *)(ADC1_AddBase + adc_CR2);

    bitSET(*ADC_CR2, 1, 0);

    return 0;
}
int Adc_Disable()
{
    unsigned int *ADC_CR2 = (unsigned int *)(ADC1_AddBase + adc_CR2);

    bitRST(*ADC_CR2, 1, 0);

    return 0;
}

/*
*   Brief: ADC prescaler
*/
int Adc_Prescaler(AdcPrescaler_typedef __PRESCALE)
{
    unsigned int *ADC_CCR = (unsigned int *)(ADC1_AddBase + adc_CCR);

    bitRST(*ADC_CCR, 0b11, 16);
    bitSET(*ADC_CCR, __PRESCALE, 16);

    return 0;
}

/*
*   Brief: Set ADC resolution
*/
int Adc_Resolution(Adc1Resolution_typedef __RESOLUTION)
{
    unsigned int *ADC_CR1 = (unsigned int *)(ADC1_AddBase + adc_CR1);

    bitRST(*ADC_CR1, 0b11, 24);
    bitSET(*ADC_CR1, __RESOLUTION, 24);

    return 0;
}

/*
*   Brief: Start conversion of injected channels
*/
int Adc_StartInjected(Ctrl_Typedef __STATE)
{
    unsigned int *ADC_CR2 = (unsigned int *)(ADC1_AddBase + adc_CR2);

    bitRST(*ADC_CR2, 1, 22);
    bitSET(*ADC_CR2, __STATE, 22);

    return 0;
}

/*
*   Brief: Data alignment
*/
int Adc_DataAlignment(Adc1DataAlignment_typedef __VALUE)
{
    unsigned int *ADC_CR2 = (unsigned int *)(ADC1_AddBase + adc_CR2);

    bitSET(*ADC_CR2, __VALUE, 11);

    return 0;
}

/*
*   Brief: sampling time selection
*/
int Adc_SampleTime(unsigned char __CHANNEL, Adc1SampleTime_typedef __VALUE)
{
    if(__CHANNEL >= 10 && __CHANNEL <= 18)
    {
        unsigned int *ADC_SMPR1 = (unsigned int *)(ADC1_AddBase + adc_SMPR1);

        bitRST(*ADC_SMPR1, 0b111, ((__CHANNEL - 10) * 3));
        bitSET(*ADC_SMPR1, __VALUE, ((__CHANNEL - 10) * 3));

        return 0;
    }

    if(__CHANNEL >= 0 && __CHANNEL <= 9)
    {
        unsigned int *ADC_SMPR2 = (unsigned int *)(ADC1_AddBase + adc_SMPR2);

        bitRST(*ADC_SMPR2, 0b111, ((__CHANNEL - 0) * 3));
        bitSET(*ADC_SMPR2, __VALUE, ((__CHANNEL - 0) * 3));

        return 0;
    }

    return -1;
}

/*
*   Brief: Continuous conversion
*/
int Adc_ConversionMode(Adc1ConversionMode_typedef __MODE)
{
    unsigned int *ADC_CR2 = (unsigned int *)(ADC1_AddBase + adc_CR2);

    bitRST(*ADC_CR2, 1, 1);
    bitSET(*ADC_CR2, __MODE, 1);

    return 0;
}

/*
*   Brief: Injected sequence length
*/
int Adc_InjectedSequenceLength(unsigned char __LENGTH, unsigned char __CHANNEL)
{
    if(__LENGTH < 0 || __LENGTH > 3)
    {
        return -1;
    }

    unsigned int *ADC_JSQR = (unsigned int *)(ADC1_AddBase + adc_JSQR);
    bitRST(*ADC_JSQR, 0b11, 20);
    bitSET(*ADC_JSQR, __LENGTH, 20);

    bitRST(*ADC_JSQR, 0b11111, 15);
    bitSET(*ADC_JSQR, __CHANNEL, 15);

    return 0;
}

/*
*   Brief: ADC injected data register 1
*/
unsigned short Adc_InjectedData(unsigned char __NUMERICAL)
{
    if(__NUMERICAL < 1 || __NUMERICAL > 4)
    {
        return -1;
    }
    
    unsigned int *ADC_JDRx = (unsigned int *)(ADC1_AddBase + (0x3C + ((__NUMERICAL - 1) * 4)));
    unsigned int *ADC_SR = (unsigned int *)(ADC1_AddBase + adc_SR);

    //--- Wait Injected channel end of conversion
    while(!bitVALUE(*ADC_SR, 2));
    bitRST(*ADC_SR, 1, 2);

    unsigned short _tmp = *ADC_JDRx;

    return _tmp;
}
