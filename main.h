#ifndef __MAIN_H
#define	__MAIN_H

#include <stdio.h>
#include "stm32f10x.h"
#include "GPIOLIKE51.h"
#include "delay.h"
#include "stdarg.h"	 	 	 
#include "string.h"	
#include "timer.h"
#include "OLED_I2C.h"
#include "Steppermotor.h"
#include "flash.h"
#include "USART.h"
#include "dht11.h"
#include "Key.h"
#include "display.h"
#include "stdio.h"	
#include "esp8266.h"	
#include "sys.h"
#include "adc.h"
#include "run.h"
#include "led.h"


extern u8 b_1s,bee_num;
extern u32 set_code[21];//设置参数
extern int light_state;       // 灯状态：0-关，1-开
void uploadStatusToCloud(void);
extern int mode;
void uploadStatusToCloud2(void);
extern int mode_change_flag;  // 新增标志位

#endif
