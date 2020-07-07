#include "led.h"

//LED��ʼ������
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOA Peripheral clock enable ʹ��GPIOAʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure PA0 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;   //���ű�ţ�0�� 1��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���ģʽ������
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��ʹ����/��������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);//����ߵ�ƽ ����
}
