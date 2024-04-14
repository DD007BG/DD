#ifndef __DHT11_H
#define __DHT11_H

#include "./SYSTEM/sys/sys.h"

/* 引脚 定义 */

#define dht11_GPIO_PORT                  GPIOF
#define dht11_GPIO_PIN                   GPIO_PIN_15
#define dht11_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define dht11_high HAL_GPIO_WritePin(dht11_GPIO_PORT, dht11_GPIO_PIN, GPIO_PIN_SET)
#define dht11_low HAL_GPIO_WritePin(dht11_GPIO_PORT, dht11_GPIO_PIN, GPIO_PIN_RESET);
#define Read_Data HAL_GPIO_ReadPin(dht11_GPIO_PORT, dht11_GPIO_PIN)

void DHT11_GPIO_Init_OUT(void);
void DHT11_GPIO_Init_IN(void);
void DHT11_Start(void);
unsigned char DHT11_REC_Byte(void);
void DHT11_REC_Data(void);

#endif


















