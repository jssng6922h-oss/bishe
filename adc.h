#ifndef __ADC_H
#define __ADC_H 
// 头文件中的校准系数声明
extern float calibrationFactor;
extern uint8_t lightIntensity;
extern uint8_t smokeIntensity;
void AD_Init(void);
void AD_Init2(void);
void Smoke_beep(void);

uint16_t AD_GetValue(void);
uint16_t AD_GetValue2(void);
uint16_t AD_GetAverageValue(uint8_t samples);
void displayWaterLevel(uint16_t ADValue);

uint16_t convertADValueToWaterLevel(uint16_t ADValue);

uint16_t Get_Water_Level(void);

uint16_t Sliding_Average_Filter(uint16_t newValue);

uint8_t Get_Light_Intensity(uint16_t ADValue);
uint8_t Get_Smoke_Intensity(uint16_t ADValue);
void Set_LED_Brightness(uint8_t lightIntensity);

#endif
