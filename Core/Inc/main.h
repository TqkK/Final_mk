/************************************************************************************
 *
 *									                  [MAIN - TqK]
 *
 ************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "UserDefine.h"

#include "System.h"
#include "Gpio.h"
#include "Uart.h"
#include "CortexTemp.h"
#include "Exti.h"
#include "LpMode.h"

#if ( __Use_FreeRTOS == 1 )
    #include "FreeRTOS.h"
    #include "task.h"
    #include "queue.h"
    #include "semphr.h"
    #include "event_groups.h"
#endif

/* Private includes ----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void vApplicationTickHook();
void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName);

void func_1(void *pvParameters);
void func_2(void *pvParameters);
void func_3(void *pvParameters);
void func_4(void *pvParameters);
void func_5(void *pvParameters);

/* Private defines -----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
