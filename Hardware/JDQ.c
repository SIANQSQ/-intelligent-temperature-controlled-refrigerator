#include "stm32f10x.h"                  // Device header

void JDQ_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //开漏
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);				
}


void JDQ1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);		
}


void JDQ1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_7);		
}
