#include "main.h"
 int pumpState = 0;  // 初始化为0，代表水泵初始状态为关闭
 

void Check_Water_Level(void)
{
    // 读取红外对管传感器的状态
    uint8_t waterDetected = Sun;
	static uint8_t last_jdq_io = 1;  // 保存上一个继电器状态，初始为关（1）
    if (waterDetected == 1)  // 红外对管传感器输出 1，表示无水
    {
        // 水位低于，打开继电器，加水
        GPIO_ResetBits(GPIOB, GPIO_Pin_8);  // 低电平打开继电器
        pumpState = 1;  // 设置为缺水状态
        beepTriggered = 1;  // 触发蜂鸣器
		if (last_jdq_io == 1) {  // 状态改变
            ESP8266_Send("pumpState15", pumpState);
            last_jdq_io = 0;  // 更新状态
        }
    }
    else if (waterDetected == 0)  // 红外对管传感器输出 0，表示有水
    {
        // 水位高于，关闭继电器，停止加水
        GPIO_SetBits(GPIOB, GPIO_Pin_8);    // 高电平关闭继电器
        pumpState = 0;  // 设置为水位充足状态
        beepTriggered = 0;  // 停止蜂鸣器
		if (last_jdq_io == 0) {  // 状态改变
            ESP8266_Send("pumpState15", pumpState);
            last_jdq_io = 1;  // 更新状态
        }
    }
}


// 初始化继电器对应的GPIO
void Relay_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置PB8作为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 确保继电器最初关闭
    GPIO_SetBits(GPIOB, GPIO_Pin_8);  // 高电平关闭，PB8
}
