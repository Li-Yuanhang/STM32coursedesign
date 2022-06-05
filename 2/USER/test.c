/***********************************************/
//实验名称：串口实验
//接线说明：无
//实验现象：通过串口助手发送数据，返回数据
/***********************************************/
#include "config.h"


int main(void)
{				  
	u16 t,m;
	u16 len;
	u16 times=0;  					 
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();
	
 	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			printf("\r\n您输入的数字是:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				m=USART_RX_BUF[t];
		   	USART1->DR=USART_RX_BUF[t];
			}
			m=m-0x30;
			  m=m<<12;
			m=~m;
			GPIOE->ODR=m;
				while((USART1->SR&0X40)==0);//等待发送结束
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nSTM32核心板串口实验\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);
		}
	}	  
}


