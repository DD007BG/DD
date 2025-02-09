/**
 ****************************************************************************************************
 * @file        freertos.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 实验
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
