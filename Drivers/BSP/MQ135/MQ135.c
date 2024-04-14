#include "./BSP/MQ135/MQ135.h"




extern uint8_t g_adc_dma_sta;               /* DMA����״̬��־, 0,δ���; 1, ����� */
extern uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];



uint8_t MQ135_Get(void)
{
    uint16_t i;
    uint16_t adcx;
    uint32_t sum;
    float temp;
		uint16_t j = 1;//channel1
	
    adc_nch_dma_init((uint32_t)&g_adc_dma_buf); /* ��ʼ��ADC DMA�ɼ� */

    lcd_show_string(30, 50, 200, 16, 16, "STM32", RED);
    lcd_show_string(30, 70, 200, 16, 16, "ADC DMA TEST", RED);
    lcd_show_string(30, 90, 200, 16, 16, "ATOM@ALIENTEK", RED);
		lcd_show_string(30, 140, 200, 16, 16, "ADC1_CH1_VAL:", BLUE);
    lcd_show_string(30, 152, 200, 16, 16, "ADC1_CH1_VOL:0.000V", BLUE); /* ���ڹ̶�λ����ʾС���� */

    adc_dma_enable(ADC_DMA_BUF_SIZE);   /* ����ADC DMA�ɼ� */

		while(1){
        if (g_adc_dma_sta == 1)
        {
            /* ����DMA �ɼ�����ADC���ݵ�ƽ��ֵ */
            sum = 0;

            for (i = 0; i < ADC_DMA_BUF_SIZE / 6; i++)  /* ÿ��ͨ���ɼ���10������,����10���ۼ� */
            {
                sum += g_adc_dma_buf[(6 * i) + j];      /* ��ͬͨ����ת�������ۼ� */
                //Channel1
            }

            adcx = sum / (ADC_DMA_BUF_SIZE / 6);        /* ȡƽ��ֵ */

            adcx = 1000 * adcx / 4096;
            /* ��ʾ��� */
                lcd_show_xnum(108, 110 + (j * 30), adcx, 4, 12, 0, BLUE);   /* ��ʾADCC�������ԭʼֵ */

                temp = (float)adcx * (3.3 / 4096);  /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111 */
                adcx = temp;                        /* ��ֵ�������ָ�adcx��������ΪadcxΪu16���� */
                lcd_show_xnum(108, 122 + (j * 30), adcx, 1, 12, 0, BLUE);   /* ��ʾ��ѹֵ���������֣�3.1111�Ļ������������ʾ3 */

                temp -= adcx;                       /* ���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111 */
                temp *= 1000;                       /* С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС���� */
                lcd_show_xnum(120, 122 + (j * 30), temp, 3, 12, 0X80, BLUE);/* ��ʾС�����֣�ǰ��ת��Ϊ��������ʾ����������ʾ�ľ���111. */

            g_adc_dma_sta = 0;                                  /* ���DMA�ɼ����״̬��־ */
            adc_dma_enable(ADC_DMA_BUF_SIZE);                   /* ������һ��ADC DMA�ɼ� */
        }

        LED0_TOGGLE();
        delay_ms(100);
    }
}

