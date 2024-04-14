#ifndef __PWM_H
#define __PWM_H

#include "stm32f1xx.h"
#include "./SYSTEM/sys/sys.h"
 void btim_pwm_init(uint16_t arr,uint16_t psc);
  extern TIM_HandleTypeDef btim_pwm_handle; 
#endif
