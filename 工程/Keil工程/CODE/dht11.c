#include "dht11.h"

uint8_t DHT11_data[5];
extern int flag;

void DHT11_IOout(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOD Peripheral clock enable ʹ��GPIODʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PA0 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   //���ű�ţ�12��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;      //GPIOģʽ�����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���ģʽ������
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��ʹ����/��������
	GPIO_Init(GPIOD, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
	
	GPIO_SetBits(GPIOD, GPIO_Pin_12);//����ߵ�ƽ 
	delay_ms(20);//�����߿���һ���
}

void DHT11_IOin(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ṹ�� 
	
	/* GPIOD Peripheral clock enable ʹ��GPIODʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PA0 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   //���ű�ţ�12��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;      //GPIOģʽ������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;   //IO�ٶȣ�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       //����
	GPIO_Init(GPIOD, &GPIO_InitStructure); //����ʼ���ṹ���Ҫ���GPIO���г�ʼ��
}

void DHT11_Start(void)
{
	//GPIO���ģʽ
	DHT11_IOout();
	//����͵�ƽ����18ms
	PDout(12) = 0;
	delay_ms(20);
	//����ߵ�ƽ20-40us
	PDout(12) = 1;
	delay_us(30);
}


int DHT11_Response(void)
{
	int t1=0,t2=0,t3=0;
	//GPIO����ģʽ
	DHT11_IOin();
	//�ȴ�80us�͵�ƽ����
	while(1)
	{
		delay_us(10);
		if(PDin(12) == 0)
			break;
		if(++t1>100)
		{
			printf("����������������������������������\r\n");
			printf("����DHT11ʧ��1\r\n");
			return -1;
		}
	}
	//�ȴ�80us�ߵ�ƽ����
	while(1)
	{
		delay_us(10);
		if(PDin(12) == 1)
			break;
		if(++t2>100)
		{
			printf("����������������������������������\r\n");
			printf("����DHT11ʧ��2\r\n");
			return -1;
		}
	}
	//�ȴ�����ʱ϶�͵�ƽ����
	while(1)
	{
		delay_us(10);
		if(PDin(12) == 0)
			break;
		if(++t3>100)
		{
			printf("����������������������������������\r\n");
			printf("����DHT11ʧ��3\r\n");
			return -1;
		}
	}
	return 0;
}

uint8_t Read_DHT11_DataByte(void)
{
	//���屣�����ݱ���
	uint8_t i,tmpe = 0; //0000 0000
	
	for(i=0; i<8; i++)
	{
		//�ȴ�ʱ϶��ƽ����
		while(PDin(12) == 0);
		delay_us(30);
		if(PDin(12) == 1)
		{
			//��ȡ����1 ����8bit��
			tmpe |= 1<<(7-i);//tmpe = tmpe | (1<<(7-i));
			while(PDin(12) == 1); //�ȴ��ߵ�ƽ����ʱ�����
		}
	}
	//��������
	return tmpe;
}

void Read_DHT11_Data(void)
{
	uint8_t ret,i,DHT11_data[5];

	//1������������ʼ�ź�
	DHT11_Start();
	//2���ӻ�Ӧ��
	ret = DHT11_Response();
	if(ret == 0)
	{
		//3����ȡ����(��5��)
		for(i=0; i<5; i++)
		{
			DHT11_data[i] = Read_DHT11_DataByte();
		}
		//4��У������
		if(DHT11_data[0]+DHT11_data[1]+DHT11_data[2]+DHT11_data[3] == DHT11_data[4])
		{	
			if(flag == 1)
			{
				printf("����������������������������������\r\n");
				printf("��ǰ�����¶ȣ�%d ��\r\n", DHT11_data[2]);
				while(flag == 1)
				{
					//�¶ȳ���28�����18����������
					if( !(18<=DHT11_data[2] && DHT11_data[2]<=28) )
					{
						PDout(0) = 1;
					}
					
					display(1,DHT11_data[2]/10);
					delay_ms(20);
					display(2,DHT11_data[2]%10);
					delay_ms(20);
					display(3,DHT11_data[3]/10);
					delay_ms(20);
					display(4,DHT11_data[3]%10);
					delay_ms(20);
				}
				PDout(0) = 0;
			}
			
			if(flag == 2)
			{
				printf("����������������������������������\r\n");
				printf("��ǰ����ʪ�ȣ�%d %%\r\n", DHT11_data[0]);
				while(flag == 2)
				{
					//ʪ�ȸ���70%�����30%����������
					if( !(30<=DHT11_data[0]&&DHT11_data[0]<=70) )
					{
						PDout(0) = 1;
					}
					
					display(1,DHT11_data[0]/10);
					delay_ms(20);
					display(2,DHT11_data[0]%10);
					delay_ms(20);
					display(3,DHT11_data[1]/10);
					delay_ms(20);
					display(4,DHT11_data[1]%10);
					delay_ms(20);
				}
				PDout(0) = 0;
			}
		}
		else
		{
			printf("����������������������������������\r\n");
			printf("DHT11���ݲ���ȷ\r\n");
		}
			
	}
	//6������������--���߱�Ϊ����ģʽ
	DHT11_IOout();
	PDout(12)=1;
	
}
