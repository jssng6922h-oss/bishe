#include "main.h"

// 全局变量定义，初始设置为0，可根据需要调整
int AD_Offset = 0;
int AD_Offset2 = 500;
uint8_t lightIntensity=0;
uint8_t smokeIntensity=0;
// 滑动平均滤波参数
#define WINDOW_SIZE 10
uint16_t slidingWindow[WINDOW_SIZE];
uint8_t windowIndex = 0;

void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

uint16_t Sliding_Average_Filter(uint16_t newValue)
{
    slidingWindow[windowIndex] = newValue;
    windowIndex = (windowIndex + 1) % WINDOW_SIZE;

    uint32_t sum = 0;
    for (uint8_t i = 0; i < WINDOW_SIZE; i++) {
        sum += slidingWindow[i];
    }
    return (uint16_t)(sum / WINDOW_SIZE);
}

uint8_t Get_Light_Intensity(uint16_t ADValue)
{
    uint16_t maxADC = 4090;
    uint16_t minADC = 59;

    if (ADValue >= maxADC) {
        return 0;
    } else if (ADValue <= minADC) {
        return 100;
    } else {
        return (uint8_t)((maxADC - ADValue) * 100 / (maxADC - minADC));
    }
}

void AD_Init2(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue2(void)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

uint8_t Get_Smoke_Intensity(uint16_t ADValue)
{
    uint16_t minADC = 200;   // 无烟 ≈ 0%
    uint16_t maxADC = 750;   // 浓烟 ≈ 100%

    if (ADValue >= maxADC) {
        return 100;
    } 
    else if (ADValue <= minADC) {
        return 0;
    } 
    else {
        return (uint8_t)((ADValue - minADC) * 100 / (maxADC - minADC));
    }
}

void Smoke_beep(void)
{
	if (smokeIntensity > set_code[12]) {
        bee_num = 2;
    } else {
//        beep_io = 1; // 关闭蜂鸣器
    }
}
