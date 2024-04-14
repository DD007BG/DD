
#ifndef _AS312_H
#define _AS312_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ���� ���� */

#define AS312_GPIO_PORT                  GPIOF
#define AS312_GPIO_PIN                   GPIO_PIN_14
#define AS312_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)             /* PF��ʱ��ʹ�� */

/******************************************************************************************/
/* �ⲿ�ӿں���*/
void as312_init(void);                                                                            /* ��ʼ�� */

#endif
