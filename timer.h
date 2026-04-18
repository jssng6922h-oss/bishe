#ifndef __TIMER_H
#define __TIMER_H
extern unsigned int Time_1ms;
extern unsigned int Time_1s;
extern unsigned int Time_11s;
extern unsigned int Time_111s;
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
void TIM2_Init(void);   
void TIM2_Int_Init(u16 arr,u16 psc);
extern u32 frequence;
extern u16 num;
#endif
