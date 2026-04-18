#include "main.h"

u8 DHT11_RH,DHT11_temp;
uint8_t feedingState2,lightState,modeInfo;	

// 全局标志变量

uint8_t temp_humidity_alarm = 0;
// 温度调整
int AdjustedTemperature(int raw_temp) {
    const int temperature_offset = 3;  // 固定的温度调整值
    return raw_temp - temperature_offset;  // 返回调整后的温度
}

// 湿度调整
int AdjustedHumidity(int raw_humidity) {
    const int humidity_offset = 3;  // 固定的湿度调整值
    return raw_humidity - humidity_offset;  // 返回调整后的湿度
}
//复位DHT11
//初始化DHT11通信，
//通过设置数据线为输出，
//然后拉低20ms（表示开始信号），
//之后拉高30us，准备读取数据。
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//拉低DQ
    DelayMs(20);    	//拉低至少18ms
    DHT11_DQ_OUT=1; 	//DQ=1 
	DelayUs(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		DelayUs(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		DelayUs(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		DelayUs(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		DelayUs(1);
	}
	DelayUs(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }					    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
//u8 DHT11_Read_Data(u8 *temp,u8 *humi) 
u8 DHT11_Read_Data(void) 
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			DHT11_RH=buf[0];
			DHT11_temp=(u8)buf[2];
		}
	}else return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = DHT11_DQ_PIN;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 	 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	 			 //初始化IO口
 	GPIO_SetBits(GPIOB,DHT11_DQ_PIN);					 //PG11 输出高
					 
	DHT11_Rst();
	return DHT11_Check();
}
