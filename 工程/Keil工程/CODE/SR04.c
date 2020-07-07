#include "SR04.h"

void HCSR04_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOA Peripheral clock enable ʹ��GPIOAʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;   //���ű�ţ�6��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���ģʽ������
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��ʹ����/��������
	GPIO_Init(GPIOD, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;   //���ű�ţ�6��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��ʹ����/��������
	GPIO_Init(GPIOD, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
	
}

uint32_t SR04_Getdis(void)
{
	uint32_t dis;
	uint32_t tmp=0;

	//���������ģ���ʼ��
	HCSR04_Init();
	
	PDout(6) = 1;
	delay_us(10);
	
	while(PDin(7) == 0);//���׿�ס
	
	while(PDin(7) == 1)
	{
		delay_us(8); //Լ 3mm
		tmp++;
	}

	dis = tmp*3/2;
	
	return dis;
}	

void GETdis(void)
{
	uint32_t dis;
	
	dis = SR04_Getdis();

	printf("����������������������������������\r\n");
	printf("����ֵ�ǣ�%d \r\n",dis);
	
}
