#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

#include "stm32f10x.h"

#define OLED_ADDRESS	0x78

#define OLED_SCL PBout(6)
#define OLED_SDA PBout(7)

#define OLED_SCL_GPIO_PORT	GPIOB
#define OLED_SCL_RCC 	      RCC_APB2Periph_GPIOB
#define OLED_SCL_PIN		    GPIO_Pin_6

#define OLED_SDA_GPIO_PORT	GPIOB
#define OLED_SDA_RCC 	      RCC_APB2Periph_GPIOB
#define OLED_SDA_PIN		    GPIO_Pin_7

#define OLED_IIC_SDA_READ()  GPIO_ReadInputDataBit(OLED_SDA_GPIO_PORT, OLED_SDA_PIN)

void IIC_GPIO_Config(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_WaitAck(void);
void Write_IIC_Byte(uint8_t _ucByte);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowStr_S(unsigned char x, unsigned char y, unsigned char ch[], unsigned char size);

#endif
