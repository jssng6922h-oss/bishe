#ifndef __DS18B20_H
#define __DS18B20_H 

#define DS18B20_IO_IN()  {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=8<<4;}
#define DS18B20_IO_OUT() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=3<<4;}
#define	DS18B20_DQ_OUT PBout(1)
#define	DS18B20_DQ_IN  PBin(1)

u8 DS18B20_Init(void);
short DS18B20_Get_Temp(void);
void DS18B20_Start(void);
void DS18B20_Write_Byte(u8 dat);
u8 DS18B20_Read_Byte(void);
u8 DS18B20_Read_Bit(void);
u8 DS18B20_Check(void);
void DS18B20_Rst(void);
#endif
