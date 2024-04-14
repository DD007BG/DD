/**
 ****************************************************************************************************
 * @file        freertos.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ʵ��
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

#ifndef __FREERTOS_DEMO_H
#define __FREERTOS_DEMO_H

#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/DHT11/DHT11.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LightSensor/LightSensor.h"
#include "./BSP/AS312/as312.h"
#include "./BSP/MQ135/MQ135.h"
 /*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"

void freertos_tasks(void);

#endif
