#include "config.h"  

void LED_Init(void)
{
	RCC->APB2ENR|=1<<6;    //ʹ��PORTEʱ��	
											  
	GPIOE->CRH&=0X0000ffff;
	GPIOE->CRH|=0X33330000;  
}






