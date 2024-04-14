#include "./BSP/MQ135/MQ135.h"




extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0,未完成; 1, 已完成 */
extern uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];



uint8_t MQ135_Get(void)
{
    uint16_t i;
    uint16_t adcx;
    uint32_t sum;
    float temp;
		uint16_t j = 1;//channel1
	
    adc_nch_dma_init((uint32_t)&g_adc_dma_buf); /* 初始化ADC DMA采集 */

    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "ADC DMA TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
		lcd_show_string(30, 140, 200, 16, 16, "ADC1_CH1_VAL:", BLUE);
    lcd_show_string(30, 152, 200, 16, 16, "ADC1_CH1_VOL:0.000V", BLUE); /* 先在固定位置显示小数点 */

    adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA采集 */

		while(1){
        if (g_adc_dma_sta == 1)
        {
            /* 计算DMA 采集到的ADC数据的平均值 */
            sum = 0;

            for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++)  /* 每个通道采集了10次数据,进行10次累加 */
            {
                sum += g_adc_dma_buf[(6 * i) + j];      /* 相同通道的转换数据累加 */
                //Channel1
            }

            adcx = sum / (ADC_DMA_BUF_SIZE / 6);        /* 取平均值 */

            adcx = 1000 * adcx / 4096;
            /* 显示结果 */
                lcd_show_xnum(108, 110 + (j * 30), adcx, 4, 12, 0, BLUE);   /* 显示ADCC采样后的原始值 */

                temp = (float)adcx * (3.3 / 4096);  /* 获取计算后的带小数的实际电压值，比如3.1111 */
                adcx = temp;                        /* 赋值整数部分给adcx变量，因为adcx为u16整形 */
                lcd_show_xnum(108, 122 + (j * 30), adcx, 1, 12, 0, BLUE);   /* 显示电压值的整数部分，3.1111的话，这里就是显示3 */

                temp -= adcx;                       /* 把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111 */
                temp *= 1000;                       /* 小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。 */
                lcd_show_xnum(120, 122 + (j * 30), temp, 3, 12, 0X80, BLUE);/* 显示小数部分（前面转换为了整形显示），这里显示的就是111. */

            g_adc_dma_sta = 0;                                  /* 清除DMA采集完成状态标志 */
            adc_dma_enable(ADC_DMA_BUF_SIZE);                   /* 启动下一次ADC DMA采集 */
        }

        LED0_TOGGLE();
        delay_ms(100);
    }
}

