/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ���񴴽���ɾ��ʵ��(��̬����)
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ��ӢF103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_tasks.h"


extern unsigned int rec_data[4];
/******************************************************************************************************/
/*FreeRTOS����*/

/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            StartTask_Handler;  /* ������ */
void start_task(void *pvParameters);        /* ������ */

/* Read_DHT11_Data ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define Read_DHT11_Data_PRIO      2                   /* �������ȼ� */
#define Read_DHT11_Data_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Read_DHT11_DataTask_Handler;  /* ������ */
void Read_DHT11_Data(void *pvParameters);             /* ������ */

/* TASK2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK2_PRIO      3                   /* �������ȼ� */
#define TASK2_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task2Task_Handler;  /* ������ */
void task2(void *pvParameters);             /* ������ */

/* TASK3 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK3_PRIO      4                   /* �������ȼ� */
#define TASK3_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task3Task_Handler;  /* ������ */
void task3(void *pvParameters);             /* ������ */

/* TASK4 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK4_PRIO      5                 /* �������ȼ� */
#define TASK4_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task4Task_Handler;  /* ������ */
void task4(void *pvParameters);             /* ������ */

/******************************************************************************************************/



/**
 * @brief       FreeRTOS������ں���
 * @param       ��
 * @retval      ��
 */
void freertos_tasks(void)
{

    xTaskCreate((TaskFunction_t)start_task,            /* ������ */
        (const char *)"start_task",          /* �������� */
        (uint16_t)START_STK_SIZE,        /* �����ջ��С */
        (void *)NULL,                  /* ������������Ĳ��� */
        (UBaseType_t)START_TASK_PRIO,       /* �������ȼ� */
        (TaskHandle_t *)&StartTask_Handler);   /* ������ */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */
    /* ��������1 */
    xTaskCreate((TaskFunction_t)Read_DHT11_Data,                 /* ������ */
        (const char *)"Read_DHT11_Data",               /* �������� */
        (uint16_t)Read_DHT11_Data_STK_SIZE,        /* �����ջ��С */
        (void *)NULL,                  /* ������������Ĳ��� */
        (UBaseType_t)Read_DHT11_Data_PRIO,            /* �������ȼ� */
        (TaskHandle_t *)&Read_DHT11_DataTask_Handler);   /* ������ */
    /* ��������2 */
    xTaskCreate((TaskFunction_t)task2,                 /* ������ */
        (const char *)"task2",               /* �������� */
        (uint16_t)TASK2_STK_SIZE,        /* �����ջ��С */
        (void *)NULL,                  /* ������������Ĳ��� */
        (UBaseType_t)TASK2_PRIO,            /* �������ȼ� */
        (TaskHandle_t *)&Task2Task_Handler);   /* ������ */
    /* ��������3 */
    xTaskCreate((TaskFunction_t)task3,                 /* ������ */
        (const char *)"task3",               /* �������� */
        (uint16_t)TASK3_STK_SIZE,        /* �����ջ��С */
        (void *)NULL,                  /* ������������Ĳ��� */
        (UBaseType_t)TASK3_PRIO,            /* �������ȼ� */
        (TaskHandle_t *)&Task3Task_Handler);   /* ������ */
				
		/* ��������4 */
    xTaskCreate((TaskFunction_t)task4,                 /* ������ */
        (const char *)"task4",               /* �������� */
        (uint16_t)TASK4_STK_SIZE,        /* �����ջ��С */
        (void *)NULL,                  /* ������������Ĳ��� */
        (UBaseType_t)TASK4_PRIO,            /* �������ȼ� */
        (TaskHandle_t *)&Task4Task_Handler);   /* ������ */
				
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
}

/**
 * @brief       Read_DHT11_Data
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
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
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
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
 * @param       pvParameters : �������(δ�õ�)
 * @retval      ��
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