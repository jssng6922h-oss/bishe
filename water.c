#include "main.h"
int pumpState = 0;

void Check_Water_Level(void)
{
    uint8_t waterDetected = Sun;
    static uint8_t last_jdq_io = 1;
    if (waterDetected == 1)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);
        pumpState = 1;
        beepTriggered = 1;
    }
    else if (waterDetected == 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_8);
        pumpState = 0;
        beepTriggered = 0;
    }
}

void Relay_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
}
