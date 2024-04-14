#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "freertos_tasks.h"
#include "./BSP/DHT11/DHT11.h"
#include "./BSP/LightSensor/LightSensor.h"
#include "./BSP/AS312/as312.h"
#include "./BSP/MQ135/MQ135.h"
#include "./BSP/STEPPER/Stepper.h"
#include "./BSP/PWM/pwm.h"
#include <stdio.h>
#include "main.h"
#include "./BSP/ATK_MW8266D/atk_mw8266d.h"
#include "./BSP/ATK_MW8266D/atk_mw8266d_uart.h"
#include "demo.h"

#define WIFI_SSID          "ddd"
#define WIFI_PWD           "123456789"
#define WEATHER_TCP_SERVER_IP      "api.seniverse.com"
#define WEATHER_TCP_SERVER_PORT    "80"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
		usart_init(115200);                 /* 串口1初始化为115200 */
		atk_mw8266d_uart_init(115200); 			/* 串口2初始化为115200 */
    led_init();                         /* 初始化LED */
    lcd_init();                         /* 初始化LCD */
    key_init();                         /* 初始化按键 */
    my_mem_init(SRAMIN);                /* 初始化内部SRAM内存池 */
		
		//as312_init();
		//Stepper_GPIOInit();
		//btim_pwm_init(200-1,7200-1);
		
		while(1){
		demo_run();
		//freertos_tasks();                    /* 运行FreeRTOS例程 */
		}
	
}

#if 0 
/*以下函数为0-180度舵机角度控制测试函数
	*	PWM 信号与0-180舵机的关系：
	*	0.5ms ---------------- 0度
	*	1ms   ---------------- 45度
	*	1.5ms ---------------- 90度
	*	2ms   ---------------- 135度
	*	2.5ms ---------------- 180度
 
	*	舵机频率与占空比的计算：
	*	设舵机的频率为50HZ，则PWM周期为20ms，0度对应的占空比为2.5%，即0.05ms的高电平输出。
 */
int main(void)
{
    HAL_Init();                              /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* 设置时钟, 72Mhz */
    delay_init(72);                          /* 延时初始化 */
    led_init();                              /* LED初始化 */
    btim_pwm_init(200-1,7200-1);
    while(1)
    { 
      __HAL_TIM_SET_COMPARE(&btim_pwm_handle,TIM_CHANNEL_1,5); /* 0°*/
       delay_ms(1000);/* 延时一定时间，保证能够转动到一定的角度 */
      __HAL_TIM_SET_COMPARE(&btim_pwm_handle,TIM_CHANNEL_1,25); /*180°*/
       delay_ms(1000);
       __HAL_TIM_SET_COMPARE(&btim_pwm_handle,TIM_CHANNEL_1,15); /* 90°*/
        delay_ms(1000);     
    }
}
#endif

//stepper
#if 0
		
		uint8_t key;
		while(1){			
		key = key_scan(0);
		
		if (key)
        {
            switch (key)
            {
                case KEY0_PRES:            
                    Stepper_RotateByLoop(Forward, 1, 3);
                    break;

                case KEY1_PRES:             
                    Stepper_RotateByLoop(Reversal, 1, 3);
                    break;
								case WKUP_PRES:             
                    Stepper_Stop();
                    break;
            } 
        }
	}

#endif

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}