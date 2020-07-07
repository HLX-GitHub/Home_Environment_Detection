#include "timer.h"

void TIM2_OutPWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	//ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//��ʼ���ṹ���Ա
	TIM_TimeBaseStructure.TIM_Period = 100-1;         //ʱ������ 0x0000-0xffff 1ms
	TIM_TimeBaseStructure.TIM_Prescaler = 840-1;          //Ԥ��Ƶֵ 0x0000-0xffff 84000000/840=100000hz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӵڶ��η�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //������ʽ���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʱ������ṹ���ʼ��
	
	/*ͨ����ʼ�����PWM��*/
	/* Channel 1 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //��ʱ��ģʽѡ��PWM1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;								//�Ƚ�ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;        //��Ч��ƽ���͵�ƽ��Ч
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//����ͨ��1
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//ͨ��1�Զ����أ��������
	
	//�Ƚ���ʹ��
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	/* TIM2 counter enable */
	TIM_Cmd(TIM2, ENABLE);
	
	/* GPIOA Peripheral clock enable ʹ��GPIOAʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure PA0 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   //���ű�ţ�0�� 1��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���ģʽ������
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��ʹ����/��������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2); //���Ÿ���ӳ��
}


void TIM4_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	//��ʼ���ṹ���Ա
	TIM_TimeBaseStructure.TIM_Period = 10000/10-1;         //ʱ������ 0x0000-0xffff 100ms
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;          //Ԥ��Ƶֵ 0x0000-0xffff 84000000/8400=10000hz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӵڶ��η�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //������ʽ���ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	//����NVIC
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;		         //�ж���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //��ռ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable TIM2 Update interrupts *///��������ж�
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	/* TIM2 enable counters *///ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4, ENABLE);

}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		PAout(1) ^= 1;
		/* Clear TIM4 COM pending bit */
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
	
}


