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

//ALIENTEK 探索者STM32F407开发板 实验47_2
//DSP FFT测试实验   -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


#define FFT_LENGTH		4096 		//FFT长度，默认是1024点FFT

float fft_inputbuf[FFT_LENGTH*2];	//FFT输入数组
float fft_outputbuf[FFT_LENGTH];	//FFT输出数组

u8 timeout;//定时器溢出次数
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	LED_Init();					//初始化LED
	KEY_Broad_Init();   //初始化按键				
  My_ADC_IO_Init();
	My_DMA_Init();
	My_Adc_Init();
  LCD_Init();					//初始化LCD
	LCD_DisplayNumber(0,24,0,5) ;   // 显示十进制数		
	TIM3_Int_Init(65535,84-1);	//1Mhz计数频率,最大计时65ms左右超出

	arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);//初始化scfft结构体，设定FFT相关参数
 	while(1)
	{
		key=SKEY_SCAN();	
		LCD_SetColor(LCD_WHITE);
    LCD_DisplayNumber(0,24,key,5) ;   // 显示十进制数		
		
			for(i=0;i<FFT_LENGTH;i++)//生成信号序列
			{
	    	fft_inputbuf[2*i]=ADC_ConvertedValue[i]/256 ;	
				fft_inputbuf[2*i+1]=0;//虚部全部为0
			}
			TIM_SetCounter(TIM3,0);//重设TIM3定时器的计数器值
			timeout=0;
			arm_cfft_radix4_f32(&scfft,fft_inputbuf);	//FFT计算（基4）
			time=TIM_GetCounter(TIM3)+(u32)timeout*65536; 			//计算所用时间						
			arm_cmplx_mag_f32(fft_inputbuf,fft_outputbuf,FFT_LENGTH);	//把运算结果复数求模得幅值 	
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
				LCD_DrawLine(x,y,i/2+30,290-ADC_ConvertedValue[i]/13);		// 画线
				x=i/2+30;y=290-ADC_ConvertedValue[i]/13;
			}
}

void drowkuang(float time)
{	
	u8 buf[50]; 
	sprintf((char*)buf,"%d point FFT runtime:%0.3fms",FFT_LENGTH,time/1000);
	LCD_SetColor(LCD_WHITE);	
  LCD_DisplayString(0,0,buf);//显示所用时间
	LCD_SetColor(LCD_WHITE);	
	
  LCD_DisplayNumber(24+30,296,10,2) ;  
  LCD_DisplayNumber(48+30,296,20,2) ;  
}	

