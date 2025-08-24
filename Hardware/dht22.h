#ifndef __DHT22_H
#define __DHT22_H	 
#include "sys.h"	

#define	DHT22_DQ_OUT PAout(0)  
#define	DHT22_DQ_IN  PAin(0)  

u8 DHT22_Init(void);			
u8 DHT22_Read_Data(u8 *hum1,u8 *hum2,u8 *temp1,u8 *temp2);	
u8 DHT22_Read_Byte(void);		
u8 DHT22_Read_Bit(void);		
u8 DHT22_Check(void);			
void DHT22_Rst(void);			 

#endif


















