#include "main.h"

uint8_t light_status = 0;
int people_count = 0;

void IR_People_Count(void)
{
    static uint8_t state = 0;
    static uint16_t timeout = 0;
    static int last_people_count = -1;

    uint8_t ir_out = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
    uint8_t ir_in  = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);

    switch(state)
    {
        case 0:
            if(ir_out == 0)
            {
                state = 1;
                timeout = 200;
            }
            else if(ir_in == 0)
            {
                state = 2;
                timeout = 200;
            }
            break;

        case 1:
            if(ir_in == 0)
            {
                people_count++;
                state = 3;
            }
            break;

        case 2:
            if(ir_out == 0)
            {
                if(people_count > 0)
                    people_count--;
                state = 3;
            }
            break;

        case 3:
            if(ir_out == 1 && ir_in == 1)
            {
                state = 0;
            }
            break;
    }

    if(state != 0)
    {
        if(timeout > 0)
            timeout--;
        else
            state = 0;
    }

    if(last_people_count != people_count)
    {
        last_people_count = people_count;
    }
}

void Light_Control(uint8_t light_percent)
{
    static uint8_t last_light_status = 255;

    if (people_count == 0)
    {
       GPIO_ResetBits(GPIOA, GPIO_Pin_7);
        light_status = 0;

        if (last_light_status != 0)
        {
            last_light_status = 0;
        }
        return;
    }

    if (light_percent < light_threshold)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
        light_status = 1;

        if (last_light_status != 1)
        {
            last_light_status = 1;
        }
    }
    else
    {
       GPIO_ResetBits(GPIOA, GPIO_Pin_7);
        light_status = 0;

        if (last_light_status != 0)
        {
            last_light_status = 0;
        }
    }
}

void Light_LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_ResetBits(GPIOA, GPIO_Pin_7);
}

void IR_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
