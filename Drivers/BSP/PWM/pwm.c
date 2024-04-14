#include "./BSP/PWM/pwm.h"
/**
 * @brief     ��ʱ��TIM3�ĳ�ʼ������
 * @param     arr���Զ���װ��ֵ��psc��Ԥ��Ƶϵ����
 * @retval    ��
 */
TIM_HandleTypeDef btim_pwm_handle; /* ��ʱ����� */ 
 
 void btim_pwm_init(uint16_t arr,uint16_t psc)
 {
   
   btim_pwm_handle.Instance=TIM3;/* ��ʱ������ַ */ 
   btim_pwm_handle.Init.Period=arr;  /* ����Ԥ�Զ���װ��ֵ */ 
   btim_pwm_handle.Init.Prescaler=psc; /* ����Ԥ��Ƶϵ�� */ 
   btim_pwm_handle.Init.CounterMode=TIM_COUNTERMODE_UP;   /* ���ü���ģʽ���ϼ��� */ 
    HAL_TIM_PWM_Init(&btim_pwm_handle);
     
     TIM_OC_InitTypeDef timx_oc_pwm_struct;
     timx_oc_pwm_struct.OCMode=TIM_OCMODE_PWM1; /* ���ñȽ����ģʽPWM1 */ 
     timx_oc_pwm_struct.Pulse=0;/* ���ò���/�ȽϼĴ�����ֵ�����滹����ݽǶ���������*/
     timx_oc_pwm_struct.OCPolarity=TIM_OCPOLARITY_LOW;/* ����Ƚϼ���Ϊ�� */
     HAL_TIM_PWM_ConfigChannel(&btim_pwm_handle,&timx_oc_pwm_struct,TIM_CHANNEL_1);/* ��ʱ���� PWM ͨ�����ó�ʼ������ */
     HAL_TIM_PWM_Start(&btim_pwm_handle, TIM_CHANNEL_1);/* ��ʱ���� PWM �����������������1Ϊ���������2Ϊͨ���� */
 
 }
 

/**
* @brief��ʱ���ײ�������ʱ��ʹ�ܣ��������ô˺����ᱻ HAL_TIM_PWM_Init()����
* @param       htim:��ʱ�����
* @retval��
*/ 
 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
 {
     if(htim->Instance==TIM3)/* �ж��Ƿ�Ϊ��ʱ��3 */
     {
      __HAL_RCC_TIM3_CLK_ENABLE();/* ʹ�ܶ�ʱ��ʱ�� */
      __HAL_RCC_GPIOA_CLK_ENABLE();/* ʹ�����ioʱ�� */
        GPIO_InitTypeDef gpio_init_struct;
        gpio_init_struct.Mode= GPIO_MODE_AF_PP;
        gpio_init_struct.Pin=GPIO_PIN_6;
        gpio_init_struct.Speed=GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
     }

 }

