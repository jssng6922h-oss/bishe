#include "main.h"

void DS18B20_Rst(void)	   
{                 
	DS18B20_IO_OUT(); //SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; //拉低DQ
    DelayUs(750);    //拉低750us
    DS18B20_DQ_OUT=1; //DQ=1 
	DelayUs(15);     //15US
}

u8 DS18B20_Check(void) 	   
{   
	u8 retry=0;
	DS18B20_IO_IN();//SET PA0 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		DelayUs(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		DelayUs(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}

u8 DS18B20_Read_Bit(void)
{
    u8 data;
	DS18B20_IO_OUT();
    DS18B20_DQ_OUT=0; 
	DelayUs(2);
    DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();
	DelayUs(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    DelayUs(50);           
    return data;
}

u8 DS18B20_Read_Byte(void)
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }					    
    return dat;
}
