#include "stm32f10x.h"    
#include "Delay.h"
#include "sys.h"
#include "usart.h"
#include "dht22.h"
#include "OLED.h"
#include "JDQ.h"
#include "AD.h"

#define delay_ms Delay_ms
#define delay_us Delay_us

u8 hum1;
u8 hum2;
u8 temp1;
u8 temp2;
float a;
float b;
int showtem;
int showhum;
int MyTemp = 0;
int Target;
int main(void)
 {	
	OLED_Init(); 
	JDQ_Init(); 
    AD_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	//串口1 9600波特率
	printf("******* Waveshare! ******\r\n");
	delay_ms(1000);
	delay_ms(1000);
	/*while(1)
	{
		JDQ1_ON();
		delay_ms(1000);
		JDQ1_OFF();
		delay_ms(1000);
	}*/
	int chk = DHT22_Init();//DHT22的初始化
	 while(chk==1)
	 {
		 chk = DHT22_Init(); 
		 printf("chk=%d \n",chk);
		 OLED_ShowString(1,1,"DHT22-OK");
		 Delay_ms(1000);
	 }
	OLED_Clear();
	OLED_ShowString(1,1,"QSQ's Fridge");	
    OLED_ShowString(2,1,"Temp:");	
    OLED_ShowString(3,1,"Humi:");
    OLED_ShowString(2,9," C");
    OLED_ShowString(3,9," %");
	OLED_ShowString(3,14,"Sta");
	OLED_ShowString(4,1,"Target:");	
    OLED_ShowString(4,11,"C");	 
	printf("chk=%d",chk);
  while(1)
		{		
		DHT22_Read_Data(&hum1,&hum2,&temp1,&temp2);	
		a=(hum1*256+hum2)/10;
		b=(temp1*256+temp2)/10;			  
		printf("temp: %f\n",b);
		printf("humi: %f\n",a);
        showtem = b;
        showhum = a;
		Target = SetTemp(MyTemp);
		MyTemp=AD_GetSetTemp();
        OLED_ShowNum(2,7,showtem,2);
	    OLED_ShowNum(3,7,showhum,2);
		OLED_ShowSignedNum(4,8,Target,2);
	    if(showtem>=Target) 
        {
		    JDQ1_ON();
			OLED_ShowString(4,14," ON");
		}
		else 
		{
			JDQ1_OFF();
			OLED_ShowString(4,14,"OFF");
		}
		delay_ms(2000);		
        }
}