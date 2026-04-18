#include "main.h"

void PWM_Init(void)
{
	GPIO_CFG();
	TIM2_PWM_Init(1799,1,75);
}
