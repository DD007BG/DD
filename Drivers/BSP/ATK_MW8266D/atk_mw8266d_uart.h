/**
 ****************************************************************************************************
 * @file        atk_mw8266d_uart.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266Dģ��UART�ӿ���������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * ������?:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_MW8266D_UART_H
#define __ATK_MW8266D_UART_H

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
 /* ���Ŷ��� */
#define ATK_MW8266D_UART_TX_GPIO_PORT           GPIOA
#define ATK_MW8266D_UART_TX_GPIO_PIN            GPIO_PIN_2
#define ATK_MW8266D_UART_TX_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA��ʱ��ʹ�� */

#define ATK_MW8266D_UART_RX_GPIO_PORT           GPIOA
#define ATK_MW8266D_UART_RX_GPIO_PIN            GPIO_PIN_3
#define ATK_MW8266D_UART_RX_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)     /* PA��ʱ��ʹ�� */

#define ATK_MW8266D_UART_INTERFACE              USART2
#define ATK_MW8266D_UART_IRQn                   USART2_IRQn
#define ATK_MW8266D_UART_IRQHandler             USART2_IRQHandler
#define ATK_MW8266D_UART_CLK_ENABLE()           do{ __HAL_RCC_USART2_CLK_ENABLE(); }while(0)    /* USART2 ʱ��ʹ�� */

/* UART�շ�������? */
#define ATK_MW8266D_UART_RX_BUF_SIZE            600
#define ATK_MW8266D_UART_TX_BUF_SIZE            600

extern uint8_t USART2_RX_BUF[ATK_MW8266D_UART_RX_BUF_SIZE];
extern uint8_t  USART2_TX_BUF[ATK_MW8266D_UART_TX_BUF_SIZE];
extern uint16_t USART2_RX_STA ;

/* �������� */
void atk_mw8266d_uart_printf(char *fmt, ...);       /* ATK-MW8266D UART printf */
void atk_mw8266d_uart_rx_restart(void);             /* ATK-MW8266D UART���¿�ʼ�������� */
uint8_t *atk_mw8266d_uart_rx_get_frame(void);       /* ��ȡATK-MW8266D UART���յ���һ֡���� */
uint16_t atk_mw8266d_uart_rx_get_frame_len(void);   /* ��ȡATK-MW8266D UART���յ���һ֡���ݵĳ��� */
void atk_mw8266d_uart_init(uint32_t baudrate);      /* ATK-MW8266D UART��ʼ�� */


extern  UART_HandleTypeDef huart2;
#endif
