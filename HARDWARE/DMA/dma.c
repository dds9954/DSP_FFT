#include "dma.h"
//作者-——星语
__IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0};

void My_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); //F1X的是AHB使用能
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;							//外设ACD的源基地址
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;							//存放数据的寄存器地址就是最上面定义的数ADC_ConvertedValue变量
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	//方向从外设到寄存器这里与F1X系列的区别是F1X是选择哪个源这里是哪到哪
	DMA_InitStructure.DMA_BufferSize = RHEOSTAT_NOFCHANEL;												//数据大小
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;								//DMA通道0	 /
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设基地址不变 F1X的理解是地址是否增加一般不以用选择禁止
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//同F1XX一样存放数据寄存器地址增加对应多通道的这里选增加
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;						//目的的数据大小就是16位半字两个字节
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;		//同上就是源数据大小半字两个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;																//DMA循环模式这个一般情况都是循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;			//传输通道优先级别一般都是为高 如果是单的就无所谓了
	/////////////下面关于FIFO待查
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;												//不用FIFO用直接模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;							//半字两个字节
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;										//FIFO禁止不需要配置
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;						//没有FIFO不需要配置这里
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	//////////////////////////////////////配置完成只是如果是单通道的DMA_MemoryIn的也选择不增加禁止
	DMA_Cmd(DMA2_Stream0, ENABLE);																			//使能DMA流

}

