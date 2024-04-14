/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 任务创建与删除实验(动态方法)
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 精英F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_tasks.h"


extern unsigned int rec_data[4];
/******************************************************************************************************/
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

/* Read_DHT11_Data 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define Read_DHT11_Data_PRIO      2                   /* 任务优先级 */
#define Read_DHT11_Data_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Read_DHT11_DataTask_Handler;  /* 任务句柄 */
void Read_DHT11_Data(void *pvParameters);             /* 任务函数 */

/* TASK2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO      3                   /* 任务优先级 */
#define TASK2_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
void task2(void *pvParameters);             /* 任务函数 */

/* TASK3 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK3_PRIO      4                   /* 任务优先级 */
#define TASK3_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task3Task_Handler;  /* 任务句柄 */
void task3(void *pvParameters);             /* 任务函数 */

/* TASK4 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK4_PRIO      5                 /* 任务优先级 */
#define TASK4_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task4Task_Handler;  /* 任务句柄 */
void task4(void *pvParameters);             /* 任务函数 */

/******************************************************************************************************/



/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_tasks(void)
{

    xTaskCreate((TaskFunction_t)start_task,            /* 任务函数 */
        (const char *)"start_task",          /* 任务名称 */
        (uint16_t)START_STK_SIZE,        /* 任务堆栈大小 */
        (void *)NULL,                  /* 传入给任务函数的参数 */
        (UBaseType_t)START_TASK_PRIO,       /* 任务优先级 */
        (TaskHandle_t *)&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t)Read_DHT11_Data,                 /* 任务函数 */
        (const char *)"Read_DHT11_Data",               /* 任务名称 */
        (uint16_t)Read_DHT11_Data_STK_SIZE,        /* 任务堆栈大小 */
        (void *)NULL,                  /* 传入给任务函数的参数 */
        (UBaseType_t)Read_DHT11_Data_PRIO,            /* 任务优先级 */
        (TaskHandle_t *)&Read_DHT11_DataTask_Handler);   /* 任务句柄 */
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t)task2,                 /* 任务函数 */
        (const char *)"task2",               /* 任务名称 */
        (uint16_t)TASK2_STK_SIZE,        /* 任务堆栈大小 */
        (void *)NULL,                  /* 传入给任务函数的参数 */
        (UBaseType_t)TASK2_PRIO,            /* 任务优先级 */
        (TaskHandle_t *)&Task2Task_Handler);   /* 任务句柄 */
    /* 创建任务3 */
    xTaskCreate((TaskFunction_t)task3,                 /* 任务函数 */
        (const char *)"task3",               /* 任务名称 */
        (uint16_t)TASK3_STK_SIZE,        /* 任务堆栈大小 */
        (void *)NULL,                  /* 传入给任务函数的参数 */
        (UBaseType_t)TASK3_PRIO,            /* 任务优先级 */
        (TaskHandle_t *)&Task3Task_Handler);   /* 任务句柄 */
				
		/* 创建任务4 */
    xTaskCreate((TaskFunction_t)task4,                 /* 任务函数 */
        (const char *)"task4",               /* 任务名称 */
        (uint16_t)TASK4_STK_SIZE,        /* 任务堆栈大小 */
        (void *)NULL,                  /* 传入给任务函数的参数 */
        (UBaseType_t)TASK4_PRIO,            /* 任务优先级 */
        (TaskHandle_t *)&Task4Task_Handler);   /* 任务句柄 */
				
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

/**
 * @brief       Read_DHT11_Data
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void Read_DHT11_Data(void *pvParameters)
{
    uint32_t Read_DHT11_Data_num = 0;

    while (1)
    {
        delay_ms(1000);
        DHT11_REC_Data(); 
        printf("temp:%d\r\n", rec_data[2]);
        printf("Humidity:%d\r\n", rec_data[0]);
        printf("\r\n\n");

        vTaskDelay(500);
    }
}

/**
 * @brief       task2
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task2(void *pvParameters)
{
    uint32_t task2_num = 0;

    while (1)
    {
        LightSensor_Get();
			
        vTaskDelay(500);
    }
}

/**
 * @brief       task3
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task3(void *pvParameters)
{
    uint8_t key = 0;

    while (1)
    {

			uint8_t value;
			value=HAL_GPIO_ReadPin(AS312_GPIO_PORT, AS312_GPIO_PIN);
			if(value == 0)
			{
				printf("0");   
			}
			else
				printf("1"); 

        vTaskDelay(10);
    }
}

void task4(void *pvParameters)
{
    uint32_t task4_num = 0;

    while (1)
    {
        MQ135_Get();
			
        vTaskDelay(500);
    }
}