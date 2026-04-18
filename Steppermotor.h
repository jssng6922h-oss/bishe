#ifndef __Steppermotor_h__
#define __Steppermotor_h__

extern int feedingCounts;		//投喂次数

void Motor(int Motor_speed,int Motor_angle,char Motor_dir);
void motor_io_Init(void) ;
#endif
