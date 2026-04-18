//屏幕显示程序，引脚设置在"OLED_I2C.h"
#include "main.h"

void display(void)
{		
   		uint16_t ADValue2 = AD_GetValue2();
	char d_code ;
	switch(mod)
	{
		case 0://待机界面
			

            sprintf(str, "湿度：%02d%%", DHT11_RH - 3);
			OLED_ShowCC(0, 0, (unsigned char *)str);

			sprintf(str, "%02d人",people_count);
			OLED_ShowCC(0, 4, (unsigned char *)str);
		
            sprintf(str, "温度：%02d℃", DHT11_temp-3); // 显示温度
            OLED_ShowCC(0, 2, (unsigned char *)str);

//           sprintf(str, "烟雾：%d%%  ", smokeIntensity); // 显示温度
//            OLED_ShowCC(0, 4, (unsigned char *)str);
			
			if(auto_flag == 1) {
                OLED_ShowCC(80, 4, " 自 动"); // 显示自动模式
            } else if(auto_flag == 0){
                OLED_ShowCC(80, 4, " 手 动"); // 显示手动模式
            } else if(auto_flag == 2){
                OLED_ShowCC(80, 4, " 设 置"); // 显示手动模式
            }
//		
		sprintf(str, "光强：%d%%  ", lightIntensity);
		OLED_ShowCC(0, 6, (unsigned char *)str);
		
		 switch (menu2)
        {
			case 0:
                OLED_ShowCC(80, 6, " 选择<");
                break;
//            case 1:
//                OLED_ShowCC(80, 6, " 窗户<");
//                break;
            case 1:
                OLED_ShowCC(80, 6, " 风扇<");
                break;
            case 2:
                OLED_ShowCC(80, 6, " 灯光<");
                break;
			case 3:
                OLED_ShowCC(80, 6, " 复位<");
                break;
            default:
                
                break;
        }
		
			break;
		///////////////////////////////////////////////////////////////////////////
		case 1:  // 菜单设置界面
            
            

            d_code = (menu1 == 1) ? '(' : ' ';
            sprintf(str, "    阈值设置 %c%c ", d_code, d_code);
            OLED_ShowCC(0, 4, (unsigned char *)str);
		
            break;
		//////////////////////////////////////////////////////////////
			
			/////////////////////////////////////////////////////////////
			
			/////////////////////////////////////////////////////////////
			
			
			case 2:  // 温湿度阈值设置界面
    sprintf(str, "Max Temp:%02d", temp_threshold);  // 温度最高阈值
    if (set_f == 0) {  // 当前行是温度最高阈值
        OLED_ShowStr_S(85, 0, "<");
    }
    OLED_ShowCC(0, 0, (unsigned char *)str);

    sprintf(str, "Light:%02d", light_threshold);  // 光照阈值
    if (set_f == 1) {  // 当前行是光照阈值
        OLED_ShowStr_S(85, 2, "<");
    }
    OLED_ShowCC(0, 2, (unsigned char *)str);

    break;
	}	
}
