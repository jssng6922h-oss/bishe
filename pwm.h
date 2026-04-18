#ifndef __PWM_H
#define	__PWM_H

void GPIO_CFG(void);
void TIM2_PWM_Init(uint16_t period, uint16_t prescaler,uint16_t Pulse);

#endif
