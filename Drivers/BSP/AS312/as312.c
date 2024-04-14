#include "./BSP/AS312/as312.h"


/*
 * @brief       初始化AS312相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void as312_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    AS312_GPIO_CLK_ENABLE();                                /* AS312时钟使能 */

    gpio_init_struct.Pin = AS312_GPIO_PIN;                  /* AS312引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(AS312_GPIO_PORT, &gpio_init_struct);      /* 初始化AS312引脚 */

}

