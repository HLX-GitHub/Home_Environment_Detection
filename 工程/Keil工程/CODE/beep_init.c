#include "beep_init.h"

void beep_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOD Peripheral clock enable ʹ��GPIOAʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD0 in input  PullUp mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;          //���ű�ţ�0��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;       //ʹ����������:��IOһ��ȷ���ĵ�ƽ
	GPIO_Init(GPIOD, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
	
	PDout(0) = 0;
}
