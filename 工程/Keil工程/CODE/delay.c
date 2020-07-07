#include "delay.h"

void delay_us(uint32_t nus) //���ʱʱ��199728us
{
	SysTick->CTRL = 0;      // ���ƼĴ�����ʧ�ܶ�ʱ��
	SysTick->LOAD = 84*nus; // װ�üĴ�����װ��ֵ - 1
	SysTick->VAL = 0;       // �����Ĵ�������ռ����� 
	SysTick->CTRL = 1;      // ʹ�ܶ�ʱ����ʱ����
	while ((SysTick->CTRL & 0x00010000)==0);// ������ֵ�Ƿ񵽴�0
	SysTick->CTRL = 0;      // �رն�ʱ��
}

void delay_ms(uint32_t nms)
{
	for(;nms>0; nms--)
	{
		delay_us(1000);
	}
}
