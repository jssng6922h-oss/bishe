#include "main.h"

uint overcount=0;

void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructer;
   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   
    NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStructer.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;
   
    NVIC_Init(&NVIC_InitStructer);
}

void CH_SR04_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructer;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;
   
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructer.GPIO_Pin=GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructer);
   
    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_InitStructer.GPIO_Pin=GPIO_Pin_4;
    GPIO_Init(GPIOA, & GPIO_InitStructer);
   
    TIM_DeInit(TIM2);
    TIM_TimeBaseInitStructer.TIM_Period=999;
    TIM_TimeBaseInitStructer.TIM_Prescaler=71;
    TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructer);
   
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    NVIC_Config();
    TIM_Cmd(TIM2,DISABLE);
}
