#ifndef __RUN_H
#define	__RUN_H

void run(void);
extern char motor_pos;	
extern int feeding_active;
extern uint8_t beepTriggered ;  // 蜂鸣器触发标志
extern int feeding_amount;
void run_1(void);

void startFeedingProcess(void);

void stopFeedingProcess(void);

void checkFoodWeight(void);

// 更新蜂鸣器状态的统一函数
void updateAlarmStatus(void);
#endif
