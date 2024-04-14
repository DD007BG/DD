#include "./BSP/PWM/pwm.h"
/**
 * @brief     定时器TIM3的初始化函数
 * @param     arr：自动重装载值；psc：预分频系数；
 * @retval    无
 */
TIM_HandleTypeDef btim_pwm_handle; /* 定时器句柄 */ 
 
 void btim_pwm_init(uint16_t arr,uint16_t psc)
 {
   
   btim_pwm_handle.Instance=TIM3;/* 定时器基地址 */ 
   btim_pwm_handle.Init.Period=arr;  /* 设置预自动重装载值 */ 
   btim_pwm_handle.Init.Prescaler=psc; /* 设置预分频系数 */ 
   btim_pwm_handle.Init.CounterMode=TIM_COUNTERMODE_UP;   /* 设置计数模式向上计数 */ 
    HAL_TIM_PWM_Init(&btim_pwm_handle);
     
     TIM_OC_InitTypeDef timx_oc_pwm_struct;
     timx_oc_pwm_struct.OCMode=TIM_OCMODE_PWM1; /* 设置比较输出模式PWM1 */ 
     timx_oc_pwm_struct.Pulse=0;/* 设置捕获/比较寄存器的值，后面还会根据角度重新设置*/
     timx_oc_pwm_struct.OCPolarity=TIM_OCPOLARITY_LOW;/* 输出比较极性为低 */
     HAL_TIM_PWM_ConfigChannel(&btim_pwm_handle,&timx_oc_pwm_struct,TIM_CHANNEL_1);/* 定时器的 PWM 通道设置初始化函数 */
     HAL_TIM_PWM_Start(&btim_pwm_handle, TIM_CHANNEL_1);/* 定时器的 PWM 输出启动函数，参数1为句柄，参数2为通道数 */
 
 }
 

/**
* @brief定时器底层驱动，时钟使能，引脚配置此函数会被 HAL_TIM_PWM_Init()调用
* @param       htim:定时器句柄
* @retval无
*/ 
 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
 {
     if(htim->Instance==TIM3)/* 判断是否为定时器3 */
     {
      __HAL_RCC_TIM3_CLK_ENABLE();/* 使能定时器时钟 */
      __HAL_RCC_GPIOA_CLK_ENABLE();/* 使能输出io时钟 */
        GPIO_InitTypeDef gpio_init_struct;
        gpio_init_struct.Mode= GPIO_MODE_AF_PP;
        gpio_init_struct.Pin=GPIO_PIN_6;
        gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
     }

 }

