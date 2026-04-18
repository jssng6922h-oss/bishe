#ifndef __DHT11_H
#define __DHT11_H 

#define DHT11_IO_IN()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}
#define DHT11_IO_OUT() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;}

#define DHT11_DQ_OUT PBout(3)
#define DHT11_DQ_IN  PBin(3)
#define DHT11_DQ_GPIO  GPIO_Pin_3

u8 DHT11_Init(void);
u8 DHT11_Read_Data(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Check(void);
void DHT11_Rst(void);

extern u8 DHT11_RH,DHT11_temp;
extern uint8_t feedingState2,lightState,modeInfo;

#endif
