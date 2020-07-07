#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"

#include "sys.h"
#include <stdio.h>

#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "dht11.h"
#include "timer.h"
#include "ADC_LDR.h"
#include "display.h"
#include "SR04.h"
#include "beep_init.h"

uint32_t SR04_Getdis(void);

int menu = 1;
int flag = 0;

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
	return ch;
}


int main(void)
{
	//ȷ��ϵͳ��ʱ����ʱ��Դ 84MHz
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//ȷ�����ȼ�����飺ѡ�����2 2λ��ʾ��ռ���ȼ� 2λ��ʾ��Ӧ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//�����ⲿ�ж�
	EXTILine_Config();
	//���ô���
	USART_Config();
	//�������ʾ��ʼ��
	display_Init();
	//��������ʼ��
	beep_init();
	
	
	while(1)
	{
		switch(flag)
		{
			case 1:
				//��ȡ�¶�ֵ������
				Read_DHT11_Data();
				break;
				
			case 2:
				//��ȡʪ��ֵ
				Read_DHT11_Data();
				break;
				
			case 3:
				//������
				GETdis();
				
				//��ȡ����ֵ
				ADC_EXE(1);
				break;
				
			case 4:
				//��ȡ����ֵ
				ADC_EXE(2);
				break;
				
			default:
				if(menu == 1)
				{
					printf("����������������������������������\r\n");
					printf("******KEY1:����¶�******\r\n");
					printf("******KEY2:���ʪ��******\r\n");
					printf("******KEY3:������******\r\n");
					printf("******KEY4:�������******\r\n");
					menu = 0;
				}
				break;
		}
	}
}

