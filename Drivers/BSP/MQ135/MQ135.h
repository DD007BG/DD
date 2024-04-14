#ifndef __MQ135_H
#define __MQ135_H

#include "./SYSTEM/sys/sys.h"
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "freertos_tasks.h"

uint8_t MQ135_Get(void);

#endif
