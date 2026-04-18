#include "main.h"

u8 USART2_RX_BUF[400];
u8 USART2_TX_BUF[400];
vu16 USART2_RX_STA=0;

void USART2_IRQHandler(void)
{
    // 中断处理（原样）
}

void usart2_init(u32 bound)
{
    // 初始化代码（原样）
}
