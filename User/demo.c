/**
 ****************************************************************************************************
 * @file        demo.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266D模块TCP透传实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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

#define TIME_PORTNUM			"80"					//?±????????
#define TIME_SERVERIP			"www.beijing-time.org"	//?±??·????÷IP
char serverIPStr[16]; // ????????IP??????
char portNumStr[6];   // ???????????????
Results results[] = {{0}};

//月份数据表											 
uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; 		//月修正数据表	  
//平年的月份日期表
uint8_t const mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/**
 * @brief       进入透传时，将接收自TCP Server的数据发送到串口调试助手
 * @param       is_unvarnished: 0，未进入透传
 *                              1，已进入透传
 * @retval      无
 */
 




 /**
 * @brief       显示IP地址
 * @param       无
 * @retval      无
 */
static void WEATHER_show_ip(char *buf)
{
    printf("IP: %s\r\n", buf);
    lcd_show_string(60, 151, 128, 16, 16, buf, BLUE);
}




/**
 * @brief       例程演示入口函数
 * @param       无
 * @retval      无
 */
void demo_run(void)
{
    uint8_t ret;
    char ip_buf[16];
    uint8_t key;
    uint8_t is_unvarnished = 0;

    /* 初始化ATK-MW8266D */
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
    ret = atk_mw8266d_restore();                               /* 恢复出厂设置 */
    ret += atk_mw8266d_at_test();                               /* AT测试 */
    ret += atk_mw8266d_set_mode(1);                             /* Station模式 */
    ret += atk_mw8266d_sw_reset();                              /* 软件复位 */
    ret += atk_mw8266d_ate_config(0);                           /* 关闭回显功能 */
    ret += atk_mw8266d_join_ap(WIFI_SSID, WIFI_PWD);  /* 连接WIFI */
    ret += atk_mw8266d_get_ip(ip_buf);                          /* 获取IP地址 */
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

    /* 连接TCP服务器 */
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
