/************************************************************************************
 *
 *									                  [MAIN - TqK]
 *
 ************************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

#define __runTask_1         1               //    Blink Blue led with f = 0.5 Hz
#define __runTask_2         1               //    Blink Red led with f = 1/3 Hz
#define __runTask_3         0               //    Print log via uart
#define __runTask_4         0               //    Get MCU temperature value with ADC
#define __runTask_5         1               //    Test function with multi purpose


#define Task1_STACK         512
#define Task1_PRIORITY      2

#define Task2_STACK         512
#define Task2_PRIORITY      1

#define Task3_STACK         512
#define Task3_PRIORITY      1

#define Task4_STACK         512
#define Task4_PRIORITY      1

#define Task5_STACK         512
#define Task5_PRIORITY      0


#define Func1_Delay         1000
#define Func2_Delay         1500
#define Func3_Delay         1000
#define Func4_Delay         100
#define Func5_Delay         500


#define bit_1               (1 << 1)

#define queueTemp_Lenght     20

/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
QueueHandle_t Queue_Temp = NULL;
EventGroupHandle_t Event_Temp = NULL;
SemaphoreHandle_t Semphr_Uart = NULL;

TaskHandle_t Task1_Data = NULL;
TaskHandle_t Task2_Data = NULL;
TaskHandle_t Task3_Data = NULL;
TaskHandle_t Task4_Data = NULL;
TaskHandle_t Task5_Data = NULL;

bool LgreenState = 0;


/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  

#if ( __Use_FreeRTOS == 1)
    //--- RTOS | Create task 1
    // TaskHandle_t Task1_Data = NULL;

  #if ( __runTask_1 == 1)
    xTaskCreate(func_1, "task_1", Task1_STACK, NULL, Task1_PRIORITY, &Task1_Data);
  #endif

    //--- RTOS | Create task 2
    // TaskHandle_t Task2_Data = NULL;
  #if ( __runTask_2 == 1)
    xTaskCreate(func_2, "task_2", Task2_STACK, NULL, Task2_PRIORITY, &Task2_Data);
  #endif

    //--- RTOS | Create task 3
    // TaskHandle_t Task3_Data = NULL;
  #if ( __runTask_3 == 1)
    xTaskCreate(func_3, "task_3", Task3_STACK, NULL, Task3_PRIORITY, &Task3_Data);
  #endif

    //--- RTOS | Create task 4
    // TaskHandle_t Task4_Data = NULL;
  #if ( __runTask_4 == 1)
    xTaskCreate(func_4, "task_4", Task4_STACK, NULL, Task4_PRIORITY, &Task4_Data);
  #endif

    //--- RTOS | Create task 5
    // TaskHandle_t Task5_Data = NULL;
  #if ( __runTask_5 == 1)
    xTaskCreate(func_5, "task_5", Task5_STACK, NULL, Task5_PRIORITY, &Task5_Data);
  #endif

    //--- RTOS | Queue for MCU temperature
    Queue_Temp = xQueueGenericCreate(queueTemp_Lenght, sizeof(float), queueQUEUE_TYPE_BASE);

    //--- RTOS | Event for MCU temperature
    Event_Temp = xEventGroupCreate();

    //--- RTOS | Semaphore create
    Semphr_Uart = xSemaphoreCreateMutex();
    // Semphr_Uart = xSemaphoreCreateBinary();
    while(Semphr_Uart == NULL);
    xSemaphoreGive(Semphr_Uart);

    //--- RTOS | Schedule tasks
    vTaskStartScheduler();

#endif

  


  while (1)
  {

  }
}


#if ( __Use_FreeRTOS == 1)

  /*    
  *  FUNCTION 1
  *  Blink Blue led with f = 0.5 Hz
  */
  // [ FUNCTION 1 ] Define ---------------------------------------------


  // [ FUNCTION 1 ] Code -----------------------------------------------

  void func_1(void *pvParameters)
  {
    //--- Init for func 1
    LED_BLUE_INIT;
    EXTI0_Pa0Init();

    for( ;; )
    {
      LED_BLUE_ON;
      vTaskDelay(Func1_Delay);
      LED_BLUE_OFF;
      vTaskDelay(Func1_Delay);

      if(++__exti0Flag >= 4)
      {
        __exti0Flag = 0;
        SYSTICK_DISABLE;
        SYSTICK_INTERRUPT_DISABLE;
        StopMode();
      }
    }
  }

  /*    
  *  FUNCTION 2
  *  Blink Red led with f = 1/3 Hz
  */
  // [ FUNCTION 2 ] Define ---------------------------------------------


  // [ FUNCTION 2 ] Code -----------------------------------------------

  void func_2(void *pvParameters)
  {
    //--- Init for func 2
    LED_RED_INIT;

    for( ;; )
    {
      LED_RED_ON;
      vTaskDelay(Func2_Delay);
      LED_RED_OFF;
      vTaskDelay(Func2_Delay);
    }
  }


  /*    
  *  FUNCTION 3
  *  Print log via uart
  */
  // [ FUNCTION 3 ] Define ---------------------------------------------

  #if (readADC_USE_TIMING == 0)
    #define eventTemp_bitWAIT       bit_1
  #endif

  #define readADC_USE_TIMING        0
  #define useSemphr_UART            1

  // [ FUNCTION 3 ] Code -----------------------------------------------

  void func_3(void *pvParameters)
  {
    //--- Init for func 3
    Uart1_init();

    for( ;; )
    {

  #if (readADC_USE_TIMING == 0)
      xEventGroupSync(Event_Temp, 0, eventTemp_bitWAIT, portMAX_DELAY);
  #endif

  #if (useSemphr_UART == 1)
      xSemaphoreTake(Semphr_Uart, portMAX_DELAY);
  #endif

      float _tmp = 0.0;
      Uart1_printf(BoldRedColor);
      Uart1_printf("\r\n[ Task 3 | MCU temperature ]\t");
      Uart1_printf(ResetColor);

      while(uxQueueMessagesWaiting(Queue_Temp) > 0)
      {
        xQueueReceive(Queue_Temp, &_tmp, 0);
        Uart1_printf("%.3f\t\t", _tmp);
      }
      Uart1_printf("\r\n");

  #if (readADC_USE_TIMING == 0)
      xEventGroupClearBits(Event_Temp, eventTemp_bitWAIT);
  #endif

  #if (useSemphr_UART == 1)
      xSemaphoreGive(Semphr_Uart);
  #endif

  #if (readADC_USE_TIMING == 1)
      vTaskDelay(Func3_Delay);
  #endif
    }
  }


  /*    
  *  FUNCTION 4
  *  Get MCU temperature value with ADC
  */
  // [ FUNCTION 4 ] Define ---------------------------------------------

  #define queueTemp_TicksToWait    10000


  // [ FUNCTION 4 ] Code -----------------------------------------------

  void func_4(void *pvParameters)
  {
    //--- Init for func 4
    CortexTemp_init();

    unsigned short _evCnt = 0;

    for( ;; )
    {
      float _temp = GetCortexTemp();

      xQueueGenericSend(Queue_Temp, &_temp, queueTemp_TicksToWait, queueSEND_TO_BACK);
      vTaskDelay(Func4_Delay);

  #if (readADC_USE_TIMING == 0)
      if(++_evCnt >= 10)
      {
        _evCnt = 0;
        xEventGroupSetBits(Event_Temp, eventTemp_bitWAIT);
      }
  #endif   
    }
  }

  /*    
  *  FUNCTION 5
  *  Test function with multi purpose
  */
  // [ FUNCTION 5 ] Declare ---------------------------------------------

  unsigned char sttFunc5 = 0;

  // [ FUNCTION 5 ] Code -----------------------------------------------

  void func_5(void *pvParameters)
  {
    //--- Init for func 5
    LED_GREEN_INIT;

    for( ;; )
    {
      LED_GREEN_ON;
      vTaskDelay(Func5_Delay);
      LED_GREEN_OFF;
      vTaskDelay(Func5_Delay);
    }
  }

  //------------------------------------------------------------------------
  void vApplicationTickHook()
  {

  }


  void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                          char * pcTaskName ){}

  void vApplicationMallocFailedHook(){}

  void vApplicationIdleHook()
  {

  }

  // void vTaskSwitchContext(){}

  // void xTaskIncrementTick(){}
#endif
