#include "usart.h"

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* Enable GPIOA clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable UART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	/* Connect PA9 to USART1_Tx*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	/* Connect PA10 to USART1_Rx*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);	
	/* Configure USART Tx and Rx as alternate function  */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;     //����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;     //���ù���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	 /* USARTx configured as follows:
          - BaudRate = 9600 baud    ��λ��bit/s
          - Word Length = 8 Bits    ����λ
          - One Stop Bit            ֹͣλ
          - No parity               У��λ
          - Hardware flow control disabled (RTS and CTS signals) Ӳ������
          - Receive and transmit enabled ģʽѡ��
    */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); //��Ч���Ĵ���
	
	//��������ʱ���ڲ�֪���Է����ʱ�������� --> �����жϵķ�ʽ������
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		     //�����ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    //��ռ����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//�������ڽ��������жϼ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	/* Enable USART1 */
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
	uint16_t data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		 /* Read one byte from the receive data register */
		 data = USART_ReceiveData(USART1);
		 
		 USART_SendData(USART1, data);
		 if(data == '1')
		 {
			 PAout(2) = 0;
		 }
		 else
		 {
			 PAout(2) = 1;
		 }
		/* Clears the USART1 interrupt pending bits */
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}

}

