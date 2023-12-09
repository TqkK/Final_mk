/************************************************************************************
 *
 *								[Cortex Temperature - TqK]
 *
 ************************************************************************************/

#include "CortexTemp.h"

/*
*   Brief: Cortex temperature Measurement init
*/
int CortexTemp_init()
{
    //--- ADC init
    Adc_Init();

    //--- Power On Cortex temperature measurement
    CortexTempOn();
    
    //--- ADC Power on mode
    Adc_Enable();

    return 0;
}

/*
*   Brief: Cortex temperature Measurement is on
*/
int CortexTempOn()
{
    //--- Turn on Temperature Sensor
    unsigned int *ADC_CCR = (unsigned int *)(ADC1_AddBase + adc_CCR);
    bitSET(*ADC_CCR, 1, 23);

    return 0;
}


/*
*   Brief: Cortex temperature Measurement is off
*/
int CortexTempOff()
{
    //--- Turn on Temperature Sensor
    unsigned int *ADC_CCR = (unsigned int *)(ADC1_AddBase + adc_CCR);
    bitRST(*ADC_CCR, 1, 23);

    return 0;
}


/*
*   Brief: Get Cortex temperature 
*/
float GetCortexTemp()
{
    Adc_StartInjected(1);
    float _Vin = ((float)Adc_InjectedData(1) *3000.0)/4095.0;
    float _temp = ((_Vin - 760.0) / 2.5) + 25.0;

    return _temp;
}