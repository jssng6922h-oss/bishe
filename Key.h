#ifndef __KEY_H
#define __KEY_H 

void key(void);
void Key_Init(void);

#define beep_io PBout(15)
#define jdq_io PAout(8) 
void key2(void);

extern u8 mod;
extern short menu1,set_f;
extern short menu2;

extern u8 Motor_on_b,Motor_off_b;
extern u8 run_b;
extern volatile uint8_t lightOn ;
extern int auto_flag;

extern int relay1_status ;
extern int relay3_status ;
extern int relay2_status ;
extern int relay4_status ;
extern int relay5_status ;

extern int temp_threshold ;
extern int light_threshold ;
#endif
