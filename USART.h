#ifndef __USART__H
#define __USART__H
extern unsigned char relayFlag;
extern int Feeding; 
#define USART3_RX_BUF_SIZE  165
#define USART3_TX_BUF_SIZE  600
extern uint8_t USART3_RX_BUF[USART3_RX_BUF_SIZE];
extern uint8_t USART3_TX_BUF[USART3_TX_BUF_SIZE];
void USART3_DMA_Init(void);
void USART3_DMA_Send(uint8_t *data, uint16_t len);
uint16_t USART3_DMA_GetReceivedDataLength(void);
void USART3_DMA_ClearBuffer(void);
extern int Reverse_Trigger;
#endif
