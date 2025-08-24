#include "dht22.h"
#include "Delay.h"
#include <stdio.h>  

#define delay_ms Delay_ms
#define delay_us Delay_us
   
//DHT22 起始信号
void DHT22_Rst(void)	   
{ 
  DHT22_DQ_OUT=0; 	//拉低
  delay_ms(10);    	
  DHT22_DQ_OUT=1; 	//拉高 
	delay_us(30);     
}
//等待DHT22响应
//1:失败   0:成功
u8 DHT22_Check(void) 	   
{   
	u8 y=100;
  while ((!DHT22_DQ_IN) && y)//DHT22低过程
	{
		y--;
		delay_us(1);
	};	 
	if(y<1) return 1;
	else y=100;
    while (DHT22_DQ_IN && y)//DHT22高过程
	{
		y--;
		delay_us(1);
	};
	if(y<1) return 1;	    
	return 0;
}
//读取一位    1/0
u8 DHT22_Read_Bit(void) 			 
{
	u8 bit;
 	u8 y=100;
	while((!DHT22_DQ_IN) && y)//等待高
	{
		y--;
		delay_us(1);
	}
	y=100;	
	bit=0;
	delay_us(30);	
	if(DHT22_DQ_IN)
		bit=1;
		while(DHT22_DQ_IN && y)//等待变低
	{
		y--;
		delay_us(1);
	}
	 return bit;		
}
//一个字节
u8 DHT22_Read_Byte(void)    
{        
    u8 i,byt;
    byt=0;
	for (i=0;i<8;i++) 
	{
   		byt<<=1; 
	    byt|=DHT22_Read_Bit();
    }						    
    return byt;
}
//一次数据
//temp:温度
//hum:湿度
//1成功，0失败

u8 DHT22_Read_Data(u8 *hum1,u8 *hum2,u8 *temp1,u8 *temp2)    
{        
 	u8 buf[5];
	u8 i;
	
	DHT22_Rst();
	if(DHT22_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT22_Read_Byte();
		}	
		if((unsigned char)(buf[0]+buf[1]+buf[2]+buf[3])==buf[4]) 
		{
			*hum1=buf[0];
			*hum2=buf[1];
			*temp1=buf[2];
			*temp2=buf[3];		
			return 1;	
		}
	}
	return 0;   
}
//初始化
//0成，1败
 	 
u8 DHT22_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 	
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
	DHT22_Rst();
	return DHT22_Check();
}





