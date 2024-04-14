#include "./BSP/AS312/as312.h"


/*
 * @brief       ��ʼ��AS312���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void as312_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    AS312_GPIO_CLK_ENABLE();                                /* AS312ʱ��ʹ�� */

    gpio_init_struct.Pin = AS312_GPIO_PIN;                  /* AS312���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(AS312_GPIO_PORT, &gpio_init_struct);      /* ��ʼ��AS312���� */

}

