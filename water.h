#ifndef __WATER_H
#define __WATER_H 
#define Sun   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
extern int pumpState;
uint16_t convertADValueToMM(uint16_t ADValue);
void Check_Water_Level(void);
void Relay_Init(void);
#endif
