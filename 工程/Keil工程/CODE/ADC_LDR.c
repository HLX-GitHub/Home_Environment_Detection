#include "ADC_LDR.h"

extern int flag;

void LDR_Init1(void)
{
	//����ṹ��
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
	
	//ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
	
	/* Configure ADC1 Channel5 pin as analog input ******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;     //ģ�����빦��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//����ADC����ṹ��
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;       //ADCģʽ������ģʽ
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;    //ʱ�ӷ�Ƶ2��Ƶ 84/2=42MHz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //��ֹDMA����
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //�������
	ADC_CommonInit(&ADC_CommonInitStructure);

	/* ADC1 Init ****************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;      //12λ���ȣ�������Χ0~4095
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;								      //����ɨ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;      					//ת��������,����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //�޴�����ʽ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 						//��λ���룬�Ҷ���
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                  //��ȡ1�����
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel5 configuration **************************************/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_3Cycles); //ADC1ͨ��5û3��ʱ�Ӳ���1��

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

}

void LDR_Init2(void)
{
	//����ṹ��
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;
	
	//ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
	
	/* Configure ADC1 Channel5 pin as analog input ******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;     //ģ�����빦��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//����ADC����ṹ��
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;       //ADCģʽ������ģʽ
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;    //ʱ�ӷ�Ƶ2��Ƶ 84/2=42MHz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //��ֹDMA����
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //�������
	ADC_CommonInit(&ADC_CommonInitStructure);

	/* ADC1 Init ****************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;      //12λ���ȣ�������Χ0~4095
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;								      //����ɨ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;      					//ת��������,����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //�޴�����ʽ
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 						//��λ���룬�Ҷ���
	ADC_InitStructure.ADC_NbrOfConversion = 1;                                  //��ȡ1�����
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel5 configuration **************************************/
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_3Cycles); //ADC1ͨ��5û3��ʱ�Ӳ���1��

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

}

void ADC_EXE(uint16_t num)
{
	  
		switch(num)
		{
			case 1:
					LDR_Init1();
					uint16_t	LDR_tmp, LDR_value;
					
					/* Start ADC1 Software Conversion */ 
					ADC_SoftwareStartConv(ADC1);

					while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//�ȴ�ת������

					LDR_tmp = ADC_GetConversionValue(ADC1); //��ȡת��ֵ
					LDR_value = LDR_tmp * 3300/4096;
					
					//����Խǿ��ѹԽС������Խ����ѹԽ��
					printf("ת��ֵ�ǣ�%d ʵ�ʵ�ѹ��%dmv \r\n",LDR_tmp, LDR_value);
					
					//ʧ��ADC1
					ADC_Cmd(ADC1, DISABLE);
					//ѭ���������ʾ��ѹ
					while(flag == 3)
					{
						display(1,LDR_value/1000%10);
						delay_ms(20);
						display(2,LDR_value/100%10);
						delay_ms(20);
						display(3,LDR_value/10%10);
						delay_ms(20);
						display(4,LDR_value%10);
						delay_ms(20);
					}
					break;
			
			case 2:
					LDR_Init2();
					uint16_t GAS_tmp, GAS_value;
			
					/* Start ADC1 Software Conversion */ 
					ADC_SoftwareStartConv(ADC1);

					while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//�ȴ�ת������

					GAS_tmp = ADC_GetConversionValue(ADC1) ; //��ȡת��ֵ
					GAS_value = GAS_tmp * 10000/4096;
			
					printf("����������������������������������\r\n");
					//����Խǿ��ѹԽС������Խ����ѹԽ��
					printf("��������Ϊ��%d  \r\n",GAS_value);
					
					//ʧ��ADC1
					ADC_Cmd(ADC1, DISABLE);
					//ѭ���������ʾ��������
					while(flag == 4)
					{
						display(1,GAS_value/1000%10);
						delay_ms(20);
						display(2,GAS_value/100%10);
						delay_ms(20);
						display(3,GAS_value/10%10);
						delay_ms(20);
						display(4,GAS_value%10);
						delay_ms(20);
					}
					break;
		}
}
