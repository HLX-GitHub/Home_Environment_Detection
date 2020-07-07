#include "key.h"

extern int flag;

//KEY������ʼ������
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOB Peripheral clock enable ʹ��GPIOAʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Configure PB0 in input  PullUp mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;          //���ű�ţ�0��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       //GPIOģʽ������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       //ʹ����������:��IOһ��ȷ���ĵ�ƽ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
}

void EXTILine_Config(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	//��ʼ������
	KEY_Init();
	
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Connect EXTI Line0 to PB0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);

	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3;               //�ж��߱��
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;      //ģʽѡ��
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;   //�����ش��� �ӵ͵�ƽ���ߵ�ƽ������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/*��ռ���Ⱥ���Ӧ���ȼ��������жϵ�ִ��˳��
		1���ж���жϴ���ʱ��ռ���ȼ��ߵ��ж���ִ��
		2������ռ���ȼ�����ͬʱ��Ӧ���ȼ���ߵ��ж���ִ��
		3����ռ���ȼ���ߵ��жϿɴ����ռ���ȼ���͵��ж�
		4����Ӧ���ȼ���ߵ��жϲ��ɴ����Ӧ���ȼ���͵��ж�
	*/
	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		     //�ж���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //��ռ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;		     //�ж���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //��ռ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;		     //�ж���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;    //��ռ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;           //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;		     //�ж���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;    //��ռ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;           //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//��ִ�к����в�Ҫ����ʱ���������ҹ��ܲ�Ҫд̫����
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		//printf("KEY1\r\n");
		flag = 1;
		/* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		//printf("KEY2\r\n");
		flag = 2;
		/* Clear the EXTI line 0 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

//���վ���
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		//printf("KEY3\r\n");
		flag = 3;
		/* Clear the EXTI line 2 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

//����
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		//printf("KEY4\r\n");
		flag = 4;
		/* Clear the EXTI line 1 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
