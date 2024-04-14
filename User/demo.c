/**
 ****************************************************************************************************
 * @file        demo.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266Dģ��TCP͸��ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "demo.h"
#include "./BSP/ATK_MW8266D/atk_mw8266d.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
#include "stdlib.h"
#include "malloc.h"

nt_calendar_obj nwt;

#define WIFI_SSID          "ddd"
#define WIFI_PWD           "123456789"
#define WEATHER_TCP_SERVER_IP      "api.seniverse.com"
#define WEATHER_TCP_SERVER_PORT    "80"

#define TIME_PORTNUM			"80"					//?��????????
#define TIME_SERVERIP			"www.beijing-time.org"	//?��??��????��IP
char serverIPStr[16]; // ????????IP??????
char portNumStr[6];   // ???????????????
Results results[] = {{0}};

//�·����ݱ�											 
uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 		//���������ݱ�	  
//ƽ����·����ڱ�
uint8_t const mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/**
 * @brief       ����͸��ʱ����������TCP Server�����ݷ��͵����ڵ�������
 * @param       is_unvarnished: 0��δ����͸��
 *                              1���ѽ���͸��
 * @retval      ��
 */
 




 /**
 * @brief       ��ʾIP��ַ
 * @param       ��
 * @retval      ��
 */
static void WEATHER_show_ip(char *buf)
{
    printf("IP: %s\r\n", buf);
    lcd_show_string(60, 151, 128, 16, 16, buf, BLUE);
}




/**
 * @brief       ������ʾ��ں���
 * @param       ��
 * @retval      ��
 */
void demo_run(void)
{
    uint8_t ret;
    char ip_buf[16];
    uint8_t key;
    uint8_t is_unvarnished = 0;

    /* ��ʼ��ATK-MW8266D */
    ret = atk_mw8266d_init(115200);
    printf("%d", ret);
    if (ret != 0)
    {
        printf("ATK-MW8266D init failed!\r\n");
        while (1)
        {
            LED0_TOGGLE();
            delay_ms(200);
        }
    }

    printf("Joining to AP...\r\n");
    ret = atk_mw8266d_restore();                               /* �ָ��������� */
    ret += atk_mw8266d_at_test();                               /* AT���� */
    ret += atk_mw8266d_set_mode(1);                             /* Stationģʽ */
    ret += atk_mw8266d_sw_reset();                              /* �����λ */
    ret += atk_mw8266d_ate_config(0);                           /* �رջ��Թ��� */
    ret += atk_mw8266d_join_ap(WIFI_SSID, WIFI_PWD);  /* ����WIFI */
    ret += atk_mw8266d_get_ip(ip_buf);                          /* ��ȡIP��ַ */
    if (ret != 0)
    {
        printf("Error to join ap!\r\n");
        while (1)
        {
            LED0_TOGGLE();
            delay_ms(200);
        }
    }
    WEATHER_show_ip(ip_buf);

    /* ����TCP������ */
    ret = atk_mw8266d_connect_tcp_server(WEATHER_TCP_SERVER_IP, WEATHER_TCP_SERVER_PORT);
    if (ret != 0)
    {
        printf("Error to connect tcp server!\r\n");
        while (1)
        {
            LED0_TOGGLE();
            delay_ms(200);
        }
    }
        delay_ms(10);
    
}
