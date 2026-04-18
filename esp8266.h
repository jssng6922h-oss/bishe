#ifndef	__ESP8266_H
#define	__ESP8266_H
#include "sys.h"
/*MQTT 连接参数*/
#define post "/sys/a1mMqoF2s21/ESP8266197/thing/event/property/post"
#define post_name "Feeding2"

#define MQTT_set	"AT+MQTTUSERCFG=0,1,\"NULL\",\"ESP8266197&a1mMqoF2s21\",\"bbf2cd9f4d5d9d83377ba549d4e4925c242af999c294b148de45ba5466b33d0e\",0,0,\"\""
#define MQTT_Client   "AT+MQTTCLIENTID=0,\"a1mMqoF2s21.ESP8266197|securemode=2\\,signmethod=hmacsha256\\,timestamp=1773921067642|\""
#define MQTT_Pass    "AT+MQTTCONN=0,\"a1mMqoF2s21.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1"

_Bool BlueCmd(char *res, u16 time);
extern unsigned char Property_Data[];		//数据保存数组
void ESP8266_Init(void); 
unsigned char ESP8266_Re(unsigned char *ACK_AT);
void ESP8266_Send(const char *property, int Data);
void ESP8266_Send2(char *property, char *Data);
void Send_Status_Notification(void);

void ESP8266_Received(char *PRO);
u8 esp8266_send_cmd(char *cmd,char *ack,u16 waittime);
u8* esp8266_check_cmd(char *str);


void send_AT_cmd(const char *cmd);
void send_AT_cmd2(const char *cmd);
void extract_values(void);

#endif
