#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#include "./SYSTEM/sys/sys.h"
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "freertos_tasks.h"

uint8_t LightSensor_Get(void);

#endif
