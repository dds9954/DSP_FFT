#include "adc.h"

//作者-——星语
void My_ADC_IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	  //先初始化ADC1通道5 IO口
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;						//PA5 通道5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;																	//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;															//不带上下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);																				//初始化  
}

void My_Adc_Init(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;				//禁止DMA直接访问
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;											//ADC独立模式
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;										//4分频
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //采样时间间隔
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;														//连续转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;												//右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;				//禁止外部触发
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConv_T1_CC1;			//随便填
	ADC_InitStructure.ADC_NbrOfConversion = 1;																		//2个通道
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;												//12位ADC
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;																	//多通道采集开启
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);			//配置ADC通道转换顺序
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_28Cycles);

  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);															//使能MDA请求
	ADC_DMACmd(ADC1, ENABLE);																											//使能DMA
  ADC_Cmd(ADC1, ENABLE);  																											//使能ADC
  ADC_SoftwareStartConv(ADC1);																									//开启软件转换

}

