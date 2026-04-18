#include "main.h"

u8 mod;
short menu1,set_f;	
short menu2;
int feedingCounts = 0;
int auto_flag=1;

int relay1_status = 0;
int relay2_status = 0;
int relay3_status = 0;
int relay4_status = 0;
int relay5_status = 0;

int temp_threshold = 32;
int light_threshold = 40;

u8 run_b;
volatile uint8_t lightOn = 1;

void key(void)
{
	if(PAin(0)==0) 
	{
		DelayMs(5);
		if(PAin(0)==0)
		{
			while(PAin(0)==0);
			
			switch(mod)
			{
				case 0:
						mod = 1 ;
						OLED_CLS();
						menu1 = 1;
						menu2 = 0;
				break;
				case 1:
						mod = menu1 + 1 ;
						OLED_CLS();
				break;
				
				case 2:
					set_f++;
				    if (set_f > 3) set_f = 0;
					break;
			}
		}
	}
}
