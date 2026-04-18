#include "main.h"

u8 b_1s, bee_num;
u16 sys_time, sys_time2;
char str[32];

int mode_change_flag = 0;

u32 begin_code[21] = {
    00, 00,
    00, 00, 00,
    00, 00, 00,
    00, 00, 00,
    40, 50, 32, 00,
    00, 40, 00, 00, 40
};

u32 set_code[21];

int food_weight = 0;      
int feeding_state = 1;    
int light_state = 0;      
int mode = 1;              

void setup() {
    Light_LED_Init();
    TIM3_Int_Init(999, 71);
    AD_Init();	
    AD_Init2();
    DelayInit();
    DelayMs(1000);
    Key_Init();

    DHT11_Init();
    TIM2_Int_Init(10000, 3600);
    TIM_Cmd(TIM2, ENABLE);
   
    OLED_Init();
    OLED_CLS();

    mod = 0;
    Readflash(set_code, 0, 20);
}

void loop() {
    uint16_t ADValue = AD_GetValue();
    uint16_t filteredValue = Sliding_Average_Filter(ADValue);
    lightIntensity = Get_Light_Intensity(filteredValue);
	
	display();
	key();
    key2();
	IR_People_Count();
	DHT11_Read_Data();
	
	if (auto_flag==1) {
	Light_Control(lightIntensity);
	Control_Relays();
	}
}
