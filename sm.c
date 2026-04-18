#include "main.h"

void SM_DelayMs(unsigned int i)
{
    unsigned int j,k;

    for(j=i; j>0; j--)
        for(k=114; k>0; k--);
}

void SM_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
  GPIO_InitStructure.GPIO_Pin = 0xFF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
