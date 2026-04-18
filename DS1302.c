
#include "main.h"


 uchar year,mon,day,hour,min,sec;
 
/*BCD码转十进制*/
uint8_t BCD_DEC(uint8_t BCD)
{
	uint8_t DEC;
	DEC= BCD / 16;
	BCD %= 16;
	BCD += DEC * 10;

	return BCD;
}

/*十进制转BCD*/
uint8_t DEC_BCD(uint8_t DEC)
{
	uint8_t BCD;
	BCD = DEC / 10;
	DEC %= 10;
	DEC += BCD * 16;

	return DEC;
} 
 
void DS1302_GPIOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructre;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);            /*open GPIO  clock*/
  GPIO_InitStructre.GPIO_Pin= GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructre.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructre);
}

 /*****************************************
 * 函数名：void DS1302_IO_GPIO(void)
 * 描述  ：    DS1302 之 IO GPIO 输入输出配置
 * 输入  ：FLAG标志位
 * 输出  ：无
 * 调用  ：OUT:表示输出，IN:表示输入
          FLAG：
 *************************************/
void DS1302_IO_GPIO(uchar FLAG)
{
  GPIO_InitTypeDef GPIO_InitStructre;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);            /*open GPIO  clock*/
    /**********配置数据IO端口 输出 **********/
    if(FLAG==0x01)
  {
    GPIO_InitStructre.GPIO_Pin= GPIO_Pin_13;//配置IO_GPIO
  GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructre.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructre);
  }
    /**********配置数据IO端口 输入**********/
    else if(FLAG==0x00)
  {
     GPIO_InitStructre.GPIO_Pin= GPIO_Pin_13;//配置IO_GPIO
   GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;  //配置上拉输入
   GPIO_Init(DS1302_PORT, &GPIO_InitStructre);
   }
}
  /*****************************************
 * 函数名：void DS1302_delay(u8 dd)
 * 描述  ：简单延时
 * 输入  ：
 * 输出  ：无
 * 调用  ：
 *************************************/

void DS1302_delay(u8 dd)
{
    u8 i;
    for(;dd>0;dd--)
  for(i=110;i>0;i--);
}

  /*****************************************
 * 函数名：void DS1302_Write(uchar add,uchar dat)
 * 描述  ：DS1302写指令和数据
*  输入  ：add:发送地址，dat：所在数据
 * 输出  ：无
 * 调用  ：
 *************************************/

 void DS1302_Write(uchar add,uchar dat)
 {
 uchar i,temp1,temp2;
 temp1=add;
 temp2=dat;
 RES_Set_1;//RET=1;
//发送地址
for(i=0;i<8;i++)
 {
        if(temp1&0x01)
         {IO_Set_1;  }     //IO=1;
        else
        { IO_Reset_0;}   //IIO=0;
        temp1=temp1>>1;
        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
  }

//发送数据
for(i=0;i<8;i++)
    {
        /*IO=(temp2>>i)&0x01;这一句代替下面屏蔽的内容  */
        if(temp2&0x01)
         {IO_Set_1;  }     //IO=1;
        else
         { IO_Reset_0;}    //IIO=0;
            temp2=temp2>>1;
            CLK_Set_1;            //CLK=1;
            DS1302_delay(2);
            CLK_Reset_0;    //CLK=0;
    }
RES_Reset_0;// RET=0;
 }




/*****************************************
 * 函数名：uchar DS1302_Read(uchar add)
 * 描述  ：DS1302读数据
 *  输入  ：add:发送所在地址
 * 输出  ：
 * 调用  ：
 *************************************/
uchar DS1302_Read(uchar add)
{
  uchar i,suf,temp,mm,nn,value;
   temp=add;
   RES_Set_1;//RET=1;
    //写地址
  for(i=0;i<8;i++)
      {
       if(temp&0x01)
       {IO_Set_1;  }     //IO=1;
      else
         { IO_Reset_0;}    //IO=0;
      temp=temp>>1;
        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
      }
 //读数据

DS1302_IO_GPIO(IN);//配置IO为输入
  for(i=0;i<8;i++)
    {
     suf=suf>>1;//读数据变量
     if(IO_Read)    //IO=1
     {
         suf=suf|0x80;
     }
     else     //IO=0
     {
     suf=suf&0x7f;
     }

        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
    }
    RES_Reset_0;    // RET=0;

DS1302_IO_GPIO(OUT);//配置IO为输出
 return suf;
}


/*****************************************
 * 函数名：void DS1302_Read_Time(void)
 * 描述  ：DS1302读出年月日，分秒时时间
 *  输入  ：
 * 输出  ：
 * 调用  ：
 *************************************/
void DS1302_Read_Time(void)
{
  sec = BCD_DEC(DS1302_Read(0x81));
  min = BCD_DEC(DS1302_Read(0x83));
  hour = BCD_DEC(DS1302_Read(0x85));
  day = BCD_DEC(DS1302_Read(0x87));
  mon = BCD_DEC(DS1302_Read(0x89));
  year = BCD_DEC(DS1302_Read(0x8d));
}

/*****************************************
 * 函数名：void DS1302_Write_Time(void)
 * 描述  ：DS1302写入时间
 *  输入  ：
 * 输出  ：
 * 调用  ：
 *************************************/
void DS1302_Write_Time(uchar year,uchar mon,uchar day,uchar hour,uchar min,uchar sec)
{
	DS1302_Write(0x8E,0x00);//关闭写保护
	DS1302_Write(0x80,DEC_BCD(sec));
	DS1302_Write(0x82,DEC_BCD(min));
	DS1302_Write(0x84,DEC_BCD(hour));
	DS1302_Write(0x86,DEC_BCD(day));
	DS1302_Write(0x88,DEC_BCD(mon));
	DS1302_Write(0x8C,DEC_BCD(year));
	DS1302_Write(0x8E,0x80);//打开写保护
}
