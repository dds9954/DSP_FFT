#ifndef __DMA_H
#define __DMA_H
#include "sys.h"
#define RHEOSTAT_NOFCHANEL      4096
// ADC DR�Ĵ����궨�壬ADCת���������ֵ����������
#define RHEOSTAT_ADC_DR_ADDR    ((u32)ADC1+0x4c)
extern __IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

void My_DMA_Init(void);

#endif

