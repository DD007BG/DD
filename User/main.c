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
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
		usart_init(115200);                 /* ����1��ʼ��Ϊ115200 */
		atk_mw8266d_uart_init(115200); 			/* ����2��ʼ��Ϊ115200 */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */
		
		//as312_init();
		//Stepper_GPIOInit();
		//btim_pwm_init(200-1,7200-1);
		
		while(1){
		demo_run();
		//freertos_tasks();                    /* ����FreeRTOS���� */
		}
	
}

#if 0 
/*���º���Ϊ0-180�ȶ���Ƕȿ��Ʋ��Ժ���
	*	PWM �ź���0-180����Ĺ�ϵ��
	*	0.5ms ---------------- 0��
	*	1ms   ---------------- 45��
	*	1.5ms ---------------- 90��
	*	2ms   ---------------- 135��
	*	2.5ms ---------------- 180��
 
	*	���Ƶ����ռ�ձȵļ��㣺
	*	������Ƶ��Ϊ50HZ����PWM����Ϊ20ms��0�ȶ�Ӧ��ռ�ձ�Ϊ2.5%����0.05ms�ĸߵ�ƽ�����
 */
int main(void)
{
    HAL_Init();                              /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);      /* ����ʱ��, 72Mhz */
    delay_init(72);                          /* ��ʱ��ʼ�� */
    led_init();                              /* LED��ʼ�� */
    btim_pwm_init(200-1,7200-1);
    while(1)
    { 
      __HAL_TIM_SET_COMPARE(&btim_pwm_handle,TIM_CHANNEL_1,5); /* 0��*/
       delay_ms(1000);/* ��ʱһ��ʱ�䣬��֤�ܹ�ת����һ���ĽǶ� */
      __HAL_TIM_SET_COMPARE(&btim_pwm_handle,TIM_CHANNEL_1,25); /*180��*/
       delay_ms(1000);
       __HAL_TIM_SET_COMPARE(&btim_pwm_handle,TIM_CHANNEL_1,15); /* 90��*/
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