#include "main.h"

unsigned char Property_Data[2];  // 数据保存数组
void send_AT_cmd(const char *cmd); // 提前声明函数

void ESP8266_Init(void)
{
    send_AT_cmd("AT+RST");
	
    send_AT_cmd("AT+CWMODE=3");  // 配置WiFi工作模式为Station模式

    send_AT_cmd("AT+CWJAP=\"CMCC-cC5e\",\"3b9fz6xz\"");  // 修改为你的WiFi名称和密码
	DelayMs(5000);  // 简单延时，等待应答
    send_AT_cmd(MQTT_set);
    send_AT_cmd(MQTT_Client);
    send_AT_cmd(MQTT_Pass);
}

void send_AT_cmd(const char *cmd)
{
    strcpy((char*)USART3_TX_BUF, cmd);
    strcat((char*)USART3_TX_BUF, "\r\n");
    USART3_DMA_Send(USART3_TX_BUF, strlen((char*)USART3_TX_BUF));
    DelayMs(2000);  // 简单延时，等待应答

}

void send_AT_cmd2(const char *cmd)
{
    strcpy((char*)USART3_TX_BUF, cmd);
    strcat((char*)USART3_TX_BUF, "\r\n");
    USART3_DMA_Send(USART3_TX_BUF, strlen((char*)USART3_TX_BUF));
   
	DelayMs(500);  // 简单延时，等待应答

}


//ESP8266发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果;其他,期待应答结果的位置(str的位置)
// 检测接收到的应答
u8 *esp8266_check_cmd(char *str)
{
    char *strx = 0;
    uint16_t received_data_length = USART3_DMA_GetReceivedDataLength();  // 获取接收到的数据长度

    if (received_data_length > 0)  // 如果接收到数据
    {
        USART3_RX_BUF[received_data_length] = '\0';  // 添加结束符
        strx = strstr((const char *)USART3_RX_BUF, (const char *)str);  // 搜索期望的应答字符串
    }
    return (u8 *)strx;
}


// 向云端发送数据
void ESP8266_Send(const char *property, int Data)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "AT+MQTTPUB=0,\"/sys/a1GZbHGcPVj/ESP8266001/thing/event/property/post\",\"{\\\"params\\\":{\\\"%s\\\":%d}}\",1,0\r\n", property, Data);
    USART3_DMA_Send((uint8_t *)cmd, strlen(cmd));  // 使用DMA发送数据
    DelayMs(70);
}

// 发送文本类报警
void ESP8266_Send2(const char *property, const char *data)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd),
             "AT+MQTTPUB=0,\"/sys/a1GZbHGcPVj/ESP8266001/thing/event/property/post\",\"{\\\"params\\\":{\\\"%s\\\":\\\"%s\\\"}}\",1,0\r\n",
             property, data);
    USART3_DMA_Send((uint8_t *)cmd, strlen(cmd));
    DelayMs(70);
}
