#include "main.h"

u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error = 0;

#define GapValue 381.5

void Init_HX711pin(void)
{
	
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC , ENABLE);
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

     GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

u32 HX711_Read(void)
{
        unsigned long count;
        unsigned char i;
          HX711_DOUT=1;
					DelayUs(1);
          HX711_SCK=0;
          count=0;
          while(HX711_DOUT);
          for(i=0;i<24;i++)
        {
                  HX711_SCK=1;
                  count=count<<1;
                DelayUs(1);
                HX711_SCK=0;
                  if(HX711_DOUT)
                        count++;
                DelayUs(1);
        }
         HX711_SCK=1;
    count=count^0x800000;
        DelayUs(1);
        HX711_SCK=0;  
        return(count);
}

void Get_Maopi(void)
{
        Weight_Maopi = HX711_Read();        
}
