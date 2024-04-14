#ifndef __STEPPER_H_
#define __STEPPER_H_

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LCD/lcd.h"
#include "freertos_tasks.h"

// 电机的旋�?方向
typedef enum
{
	Forward = 0,
	Reversal = 1
} RotDirection;

#define 	Stepper_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)
#define		Stepper_Output_GPIO		GPIOF
#define 	Stepper_LA				GPIO_PIN_1
#define 	Stepper_LB				GPIO_PIN_2
#define 	Stepper_LC				GPIO_PIN_3
#define 	Stepper_LD				GPIO_PIN_4

void Stepper_GPIOInit(void);
void Stepper_Stop(void);
void Stepper_SingleStep(uint8_t StepNum, uint16_t Delay_Time_xms);
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms);
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms);

#endif
