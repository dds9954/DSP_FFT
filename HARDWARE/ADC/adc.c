#include "adc.h"

//����-��������
void My_ADC_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;						//PA5 ͨ��5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;																	//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;															//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);																				//��ʼ��  
}

void My_Adc_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;				//��ֹDMAֱ�ӷ���
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;											//ADC����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;										//4��Ƶ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //����ʱ����
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;														//����ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;												//�Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;				//��ֹ�ⲿ����
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConv_T1_CC1;			//�����
	ADC_InitStructure.ADC_NbrOfConversion = 1;																		//2��ͨ��
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;												//12λADC
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;																	//��ͨ���ɼ�����
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);			//����ADCͨ��ת��˳��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_28Cycles);

  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);															//ʹ��MDA����
	ADC_DMACmd(ADC1, ENABLE);																											//ʹ��DMA
  ADC_Cmd(ADC1, ENABLE);  																											//ʹ��ADC
  ADC_SoftwareStartConv(ADC1);																									//�������ת��

}

