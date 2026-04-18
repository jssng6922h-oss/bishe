#include "main.h"
#include "codetab.h"

void IIC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(OLED_SCL_RCC|OLED_SDA_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = OLED_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(OLED_SCL_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = OLED_SDA_PIN;
	GPIO_Init(OLED_SDA_GPIO_PORT, &GPIO_InitStructure);

	IIC_Stop();
}

static void IIC_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 10; i++);
}

void IIC_Start(void)
{
	OLED_SDA=1;
	OLED_SCL=1;
	IIC_Delay();
	OLED_SDA=0;
	IIC_Delay();
	OLED_SCL=0;
	IIC_Delay();
}

void IIC_Stop(void)
{
	OLED_SDA=0;
	OLED_SCL=1;
	IIC_Delay();
	OLED_SDA=1;
}

uint8_t IIC_WaitAck(void)
{
	uint8_t re;

	OLED_SDA=1;
	IIC_Delay();
	OLED_SCL=1;
	IIC_Delay();
	if (OLED_IIC_SDA_READ())
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	OLED_SCL=0;
	IIC_Delay();
	return re;
}

void Write_IIC_Byte(uint8_t _ucByte)
{
  uint8_t i;
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			OLED_SDA=1;
		}
		else
		{
			OLED_SDA=0;
		}
		IIC_Delay();
		OLED_SCL=1;
		IIC_Delay();	
		OLED_SCL=0;
		if (i == 7)
		{
			 OLED_SDA=1;
		}
		_ucByte <<= 1;
		IIC_Delay();
	}
}

void WriteCmd(unsigned char I2C_Command)
{
	IIC_Start();
	Write_IIC_Byte(OLED_ADDRESS);
	IIC_WaitAck();
	Write_IIC_Byte(0x00);
	IIC_WaitAck();
	Write_IIC_Byte(I2C_Command);
	IIC_WaitAck();
	IIC_Stop();
}

void WriteDat(unsigned char I2C_Data)
{
	IIC_Start();
	Write_IIC_Byte(OLED_ADDRESS);
	IIC_WaitAck();
	Write_IIC_Byte(0x40);
	IIC_WaitAck();
	Write_IIC_Byte(I2C_Data);
	IIC_WaitAck();
	IIC_Stop();
}
