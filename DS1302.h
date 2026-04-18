#ifndef __DS1302_H__
#define __DS1302_H__
#include <stm32f10x.h>
#define uchar unsigned char
#define uint unsigned int
#define OUT   0x01
#define IN    0x00
extern uchar year,mon,day,hour,min,sec;
#define DS1302_PORT   GPIOB
#define CLK_Reset_0  GPIOB->BRR=GPIO_Pin_14
#define CLK_Set_1    GPIOB->BSRR=GPIO_Pin_14
#define IO_Reset_0   GPIOB->BRR=GPIO_Pin_13
#define IO_Set_1     GPIOB->BSRR=GPIO_Pin_13
#define RES_Reset_0  GPIOB->BRR=GPIO_Pin_12
#define RES_Set_1    GPIOB->BSRR=GPIO_Pin_12
#define IO_Read   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
void DS1302_GPIOInit(void);
void DS1302_IO_GPIO(uchar FLAG);
void DS1302_delay(u8 dd);
void DS1302_Write(uchar add,uchar dat);
uchar DS1302_Read(uchar add);
void DS1302_Read_Time(void);
void DS1302_Write_Time(uchar year,uchar mon,uchar day,uchar hour,uchar min,uchar sec);
#endif
