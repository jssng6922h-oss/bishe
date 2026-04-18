#ifndef __LED_H
#define __LED_H	 

void PWM_Init2(void);
void PWM_SetCompare22(uint16_t Compare);

#define Sun   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)

extern int auto_flag;
extern uint8_t light_status ;
void KEY_Init(void);
void KEY_Scan(void);
void LED_Init(void);
void IR_People_Count(void);
void Light_Control(uint8_t light_percent);
void Light_LED_Init(void);
extern int people_count;

#endif
