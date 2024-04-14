#include "./BSP/STEPPER/Stepper.h"

uint8_t STEP;	// 用于存储电机正在走过的整步编�?

/**
  * @brief  步进电机输出端GPIO初�?�化函数
  * @param  �?
  * @retval �?
  */
void Stepper_GPIOInit(void)
{
	// 选择PA0,PA1,PA2,PA3分别为相A,B,C,D的输�?
	Stepper_GPIO_CLK_ENABLE();
	GPIO_InitTypeDef gpio_init_struct;;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;	// 推挽输出
	gpio_init_struct.Pin = Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(Stepper_Output_GPIO, &gpio_init_struct);

	HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD, GPIO_PIN_RESET);
}



/**
  * @brief  电机停转函数
  * @param  �?
  * @retval �?
  */
void Stepper_Stop(void)
{
	HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD, GPIO_PIN_RESET);
}

/**
  * @brief  4拍单相整步驱动函�?
  * @param  StepNum 	整�?�编号，0~3对应A~D
  * @param	Delay_Time_xms 		每�?�旋�?后延时时间x ms，用于控制�?�进电机速度（一�?需大于等于2�?
  * @retval �?
  */
void Stepper_SingleStep(uint8_t StepNum, uint16_t Delay_Time_xms)
{
	switch (StepNum)
	{
	case 0:		// A
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LB | Stepper_LC | Stepper_LD, GPIO_PIN_RESET);
		break;
	case 1:		// B
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LB, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LC | Stepper_LD, GPIO_PIN_RESET);
		break;
	case 2:		// C
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LC, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LD, GPIO_PIN_RESET);
		break;
	case 3:		// D
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LD, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC, GPIO_PIN_RESET);
		break;
	default: break;
	}
	delay_ms(Delay_Time_xms);	// 延时，控制电机速度
	Stepper_Stop();				// �?电，防�?�电机过�?
}

/**
  * @brief  步进电机按�?�旋�?
  * @param  direction		电机旋转方向，可以是Foreward（�?�传）或者Reversal（反�?�?
  * @param	step			电机�?过的步数
  * @param	Delay_Time_xms	每�?�旋�?后延时时间x ms，用于控制�?�进电机速度（一�?需大于等于2�?
  * @retval �?
  */
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms)
{
	for (uint32_t i = 0; i < step; i++)
	{
		if (direction == Forward)	// 电机正传
		{
			STEP++;
			if (STEP > 3)
			{
				STEP = 0;
			}
		}
		else if (direction == Reversal)	// 电机反转
		{
			if (STEP < 1)
			{
				STEP = 4;
			}
			STEP--;
		}
		Stepper_SingleStep(STEP, Delay_Time_xms);
	}
}

/**
  * @brief  步进电机按整数圈旋转
  * @param  direction		电机旋转方向，可以是Foreward（�?�传）或者Reversal（反�?�?
  * @param  Loop			电机旋转的圈�?
  * @param  Delay_Time_xms	每�?�旋�?后延时时间x ms，用于控制�?�进电机速度（一�?需大于等于2�?
  * @retval
  */
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms)
{
	Stepper_RotateByStep(direction, Loop * 2048, Delay_Time_xms);
}
