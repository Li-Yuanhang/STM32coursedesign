/***********************************************/
//ʵ�����ƣ�����ʵ��
//����˵������
//ʵ������ͨ���������ַ������ݣ���������
/***********************************************/
#include "config.h"


int main(void)
{				  
	u16 t,m;
	u16 len;
	u16 times=0;  					 
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();
	
 	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			printf("\r\n�������������:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				m=USART_RX_BUF[t];
		   	USART1->DR=USART_RX_BUF[t];
			}
			m=m-0x30;
			  m=m<<12;
			m=~m;
			GPIOE->ODR=m;
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nSTM32���İ崮��ʵ��\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);
		}
	}	  
}


