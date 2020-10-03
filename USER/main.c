#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd_3.5tft.h"
#include "timer.h" 
#include "BLE_Key.h"
#include "math.h" 
#include "arm_math.h"  
#include "adc.h"
#include "dac.h"
#include "dma.h"

//ALIENTEK ̽����STM32F407������ ʵ��47_2
//DSP FFT����ʵ��   -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


#define FFT_LENGTH		4096 		//FFT���ȣ�Ĭ����1024��FFT

float fft_inputbuf[FFT_LENGTH*2];	//FFT��������
float fft_outputbuf[FFT_LENGTH];	//FFT�������

u8 timeout;//��ʱ���������
u16 hc=0;
void drowfft(void);
void drowadc(void);
void drowkuang(float time);
	

int main(void)
{ 
  arm_cfft_radix4_instance_f32 scfft;
 	u16 key;
	float time; 
	u16 i; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED
	KEY_Broad_Init();   //��ʼ������				
  My_ADC_IO_Init();
	My_DMA_Init();
	My_Adc_Init();
  LCD_Init();					//��ʼ��LCD
	LCD_DisplayNumber(0,24,0,5) ;   // ��ʾʮ������		
	TIM3_Int_Init(65535,84-1);	//1Mhz����Ƶ��,����ʱ65ms���ҳ���

	arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);//��ʼ��scfft�ṹ�壬�趨FFT��ز���
 	while(1)
	{
		key=SKEY_SCAN();	
		LCD_SetColor(LCD_WHITE);
    LCD_DisplayNumber(0,24,key,5) ;   // ��ʾʮ������		
		
			for(i=0;i<FFT_LENGTH;i++)//�����ź�����
			{
	    	fft_inputbuf[2*i]=ADC_ConvertedValue[i]/256 ;	
				fft_inputbuf[2*i+1]=0;//�鲿ȫ��Ϊ0
			}
			TIM_SetCounter(TIM3,0);//����TIM3��ʱ���ļ�����ֵ
			timeout=0;
			arm_cfft_radix4_f32(&scfft,fft_inputbuf);	//FFT���㣨��4��
			time=TIM_GetCounter(TIM3)+(u32)timeout*65536; 			//��������ʱ��						
			arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);	//��������������ģ�÷�ֵ 	
			drowfft();     	
			drowkuang(time);
			drowadc();
			delay_ms(100);	 
	}
}
 


void drowfft(void)
{		

	int i,j;
	for(i=0;i<FFT_LENGTH/2;i+=5)
			{
				for(j=0;j<5;j++)
				{				hc+=fft_outputbuf[i+j];				}
				hc/=64;		
				LCD_SetColor(LCD_BLACK);
				LCD_DrawLine(30+i/5,290,30+i/5,60);	
				LCD_SetColor(LCD_WHITE);	
				if(hc>193)
				hc=193;
				LCD_DrawLine(30+i/5,290,30+i/5,290-hc*1.5);					
			}
}

void drowadc(void)
{
	LCD_SetColor(LCD_BLUE);
	int i,x=30,y=290-ADC_ConvertedValue[i]/13;
	for(i=0;i<FFT_LENGTH/5;i+=2)
			{					
				LCD_DrawLine(x,y,i/2+30,290-ADC_ConvertedValue[i]/13);		// ����
				x=i/2+30;y=290-ADC_ConvertedValue[i]/13;
			}
}

void drowkuang(float time)
{	
	u8 buf[50]; 
	sprintf((char*)buf,"%d point FFT runtime:%0.3fms",FFT_LENGTH,time/1000);
	LCD_SetColor(LCD_WHITE);	
  LCD_DisplayString(0,0,buf);//��ʾ����ʱ��
	LCD_SetColor(LCD_WHITE);	
	
  LCD_DisplayNumber(24+30,296,10,2) ;  
  LCD_DisplayNumber(48+30,296,20,2) ;  
}	

