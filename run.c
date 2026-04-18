#include "main.h"

char motor_pos = 1;	
u8 Motor_on_b, Motor_off_b;
float Angle;

uint8_t weight_alarm = 0;
uint8_t beepTriggered = 0;

void run(void)
{
    if (people_count == 0)
    {
        if (run_b != 0)
        {
            stopFeedingProcess();
        }
        return;
    }

    if (run_b == 0)
    {
        if (AdjustedTemperature(DHT11_temp) > set_code[13] || smokeIntensity > set_code[12])
        {
            startFeedingProcess();
        }
    }
    else
    {
        if (AdjustedTemperature(DHT11_temp) < set_code[13] && smokeIntensity < set_code[12])
        {
            stopFeedingProcess();
        }
    }
}

int feeding_active = 0;
int previous_Weight_Shiwu = 0;
int present_Weight_Shiwu = 0;
int feeding_amount = 0;

void startFeedingProcess(void) {
    feeding_active = 1;
    feedingState2 = 1;
    feedingCounts++;
    run_b = 1;
	ESP8266_Send2("warning15", "Open window.");
	Motor(3,900,0);
}

void stopFeedingProcess(void) {
    feeding_active = 0;
    feedingState2 = 0;
    run_b = 0;
	ESP8266_Send2("warning15", "Close window.");
	Motor(3,900,1);
}
