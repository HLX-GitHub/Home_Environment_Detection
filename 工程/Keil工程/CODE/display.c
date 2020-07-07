#include "display.h"

//���֣�0-9����
uint8_t NUM[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void display_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOA Peripheral clock enable ʹ��GPIOCʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Configure PA0 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = 0x0fff; //0-11������  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���ģʽ������
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��ʹ����/��������
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
}


void display(int pos,int num)
{
	if(pos == 1)
	{
		PCout(8) = 0;
		GPIO_Write(GPIOC, NUM[num]); //��ѡ
		PCout(9) = 1;
		PCout(10) = 1;
		PCout(11) = 1;
	}	
	
	if(pos == 2)
	{
		PCout(9) = 0;
		GPIO_Write(GPIOC, NUM[num]); //��ѡ
		PCout(8) = 1;
		PCout(10) = 1;
		PCout(11) = 1;
	}	
	
	if(pos == 3)
	{
		PCout(10) = 0;
		GPIO_Write(GPIOC, NUM[num]); //��ѡ
		PCout(8) = 1;
		PCout(9) = 1;
		PCout(11) = 1;
	}	
	if(pos == 4)
	{
		PCout(11) = 0;
		GPIO_Write(GPIOC, NUM[num]); //��ѡ
		PCout(8) = 1;
		PCout(9) = 1;
		PCout(10) = 1;
	}	
}
