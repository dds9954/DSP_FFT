#include "dma.h"
//����-��������
__IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0};

void My_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); //F1X����AHBʹ����
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;							//����ACD��Դ����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;							//������ݵļĴ�����ַ���������涨�����ADC_ConvertedValue����
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	//��������赽�Ĵ���������F1Xϵ�е�������F1X��ѡ���ĸ�Դ�������ĵ���
	DMA_InitStructure.DMA_BufferSize = RHEOSTAT_NOFCHANEL;												//���ݴ�С
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;								//DMAͨ��0	 /
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�������ַ���� F1X������ǵ�ַ�Ƿ�����һ�㲻����ѡ���ֹ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//ͬF1XXһ��������ݼĴ�����ַ���Ӷ�Ӧ��ͨ��������ѡ����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;						//Ŀ�ĵ����ݴ�С����16λ���������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;		//ͬ�Ͼ���Դ���ݴ�С���������ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;																//DMAѭ��ģʽ���һ���������ѭ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;			//����ͨ�����ȼ���һ�㶼��Ϊ�� ����ǵ��ľ�����ν��
	/////////////�������FIFO����
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;												//����FIFO��ֱ��ģʽ
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;							//���������ֽ�
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;										//FIFO��ֹ����Ҫ����
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;						//û��FIFO����Ҫ��������
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	//////////////////////////////////////�������ֻ������ǵ�ͨ����DMA_MemoryIn��Ҳѡ�����ӽ�ֹ
	DMA_Cmd(DMA2_Stream0, ENABLE);																			//ʹ��DMA��

}

