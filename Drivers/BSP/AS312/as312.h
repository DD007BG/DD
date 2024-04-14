
#ifndef _AS312_H
#define _AS312_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* 引脚 定义 */

#define AS312_GPIO_PORT                  GPIOF
#define AS312_GPIO_PIN                   GPIO_PIN_14
#define AS312_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)             /* PF口时钟使能 */

/******************************************************************************************/
/* 外部接口函数*/
void as312_init(void);                                                                            /* 初始化 */

#endif
