#include "stm32f4xx.h"
#include "BLE_Key.h"
#include "delay.h"
#include "lcd_3.5tft.h"
//作者-——星语
void KEY_Broad_Init(void)
{GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_3;//PC0~3推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;//推挽方式
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;//带上拉
	GPIO_Init(GPIOC,&GPIO_InitStruct);

GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//PC4~7上拉输入
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;//输入模式
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;//带上拉
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//GPIOC->ODR=0x00FF;//GPIOC全置高
	
}

u16 SKEY_SCAN(void)
{
	u16 number=0;
	u8 key,flag=1;
	key=BKEY_Scan();
	if(key==99) flag=0;
	while(flag)
  {

	switch(key)
		{
		case 20:   number=65535; flag=0;  break;
		case 30:   number=65534; flag=0; break;
		case 40:   number=65533; flag=0; break;
		case 50:   number=65532; flag=0; break;
		case 60:   number=65531; flag=0;  break;
		case 70:   flag=0;  break;
		case 99:   break;
		default : number=number*10+key;
		}
		LCD_DisplayNumber(0,290,number,5) ; 
		if(flag)key=BKEY_Scan();
	}
return number;
}


u8 BKEY_Scan(void)
{
u16 temp;
u8 key=99;
GPIOC->ODR=0x01fe;//PB口输出  1111 1110
temp=GPIOC->IDR;//读取PB口的数据
temp=temp&0x01fd;
if(temp!=0x01fc)
{
delay_ms(5);
temp=GPIOC->IDR;//去抖操作后再次读取PB口的数据
temp=temp&0x01fd;
	if(temp!=0x01fc)
	{
	switch(temp)
	{
		case 0x01dc:key=1;break;
		case 0x01bc:key=2;break;
		case 0x017c:key=3;break;
	  case 0x00fc:key=20;break;
	}
	while(temp!=0x01e0)
	{temp=GPIOC->IDR;
		temp=temp&0x01e0;
	}
	}
}



GPIOC->ODR=0x01fD;//PB口输出******
temp=GPIOC->IDR;//读取PB口的数据
temp=temp&0x01fB;
if(temp!=0x01f9)
{
delay_ms(5);
temp=GPIOC->IDR;//去抖操作后再次读取PB口的数据
temp=temp&0x01fB;
	if(temp!=0x01f9)
	{
	switch(temp)
	{
		case 0x01d9:key=4;break; 
		case 0x01b9:key=5;break;
		case 0x0179:key=6;break;
	  case 0x00F9:key=30;break;
	
	}
	while(temp!=0x01e0)
	{temp=GPIOC->IDR;
		temp=temp&0x01e0;
	}
	}
}




GPIOC->ODR=0x01f5;//PB口输出
temp=GPIOC->IDR;//读取PB口的数据
temp=temp&0x01fd;
if(temp!=0x01f5)
{
delay_ms(5);
temp=GPIOC->IDR;//去抖操作后再次读取PB口的数据
temp=temp&0x01fd;
	if(temp!=0x01F5)
	{
	switch(temp)
	{
		case 0x01D5:key=7;break;
		case 0x01B5:key=8;break;
		case 0x0175:key=9;break;
	  case 0x00F5:key=40;break;
	
	}
	while(temp!=0x01e0)
	{temp=GPIOC->IDR;
		temp=temp&0x01e0;
	}
	}
}



GPIOC->ODR=0x01ED;//PB口输出
temp=GPIOC->IDR;//读取PB口的数据
temp=temp&0x01fd;
if(temp!=0x01ED)/**************************/
{
delay_ms(5);
temp=GPIOC->IDR;//去抖操作后再次读取PB口的数据
temp=temp&0x01fd;
	if(temp!=0x01ED)
	{
	switch(temp)
	{
		case 0x01CD:key=50;break;
		case 0x01AD:key=0;break;
		case 0x016D:key=60;break;
	  case 0x00ED:key=70;break;
	}
	while(temp!=0x01e0)
	{temp=GPIOC->IDR;
		temp=temp&0x01e0;
	}
	}
}
return key;
}
