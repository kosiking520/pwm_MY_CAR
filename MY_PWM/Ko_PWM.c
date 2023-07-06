#include "KO_PWM.h"
///////////////////////////////////////////////////////////////////////////////
//KO_PWM由  KO_SIKING  于2023/7/6日在湖北工程学院开始撰写的库文件
//本库适用于stm32f103c8t6型号单片机适用于标准库
//联系方式qq：2482819249
///////////////////////////////////////////////////////////////////////////////


//功能：在TIM3时钟源中初始化通道 1 ，2 的pwm
//arr : 设置计数值上线
//psc : 设置预分频系数
float GPIO_6_zhanbi=0.5;
float GPIO_7_zhanbi=0.5;
float GPIO_8_zhanbi=0.5;
float GPIO_9_zhanbi=0.5;
int CH1_Flag=0;
int CH2_Flag=0;
int CH3_Flag=0;
int CH4_Flag=0;
int CCR1_Val=0;
int CCR2_Val=0;
int CCR3_Val=0;
int CCR4_Val=0;
void GPIOA_6_7_FY_Init()
{
	int arr=65535;
	int psc=7200;

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//TIM3通道2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//TIM3通道1
	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//TIM3通道3
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//TIM3通道4

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
	TIM_Cmd(TIM3, ENABLE);  
	
}


void Chnag_GPIOA_6_7_Zhankongbi(int GPIOX,float ZKB)
{
if(GPIOX==6)
{
GPIO_6_zhanbi=ZKB;
}
if(GPIOX==7)
{
GPIO_7_zhanbi=ZKB;
}
if(GPIOX==8)
{
GPIO_8_zhanbi=ZKB;
}
if(GPIOX==8)
{
GPIO_9_zhanbi=ZKB;
}
}

void Chnag_GPIOA_6_7_HZ(int GPIOX,int HZ)
{
if(GPIOX==6)
{
CCR1_Val=10000/HZ;
}
if(GPIOX==7)
{
CCR2_Val=10000/HZ;
}
if(GPIOX==8)
{
CCR3_Val=10000/HZ;
}
if(GPIOX==9)
{
CCR3_Val=10000/HZ;
}
}
void TIM3_IRQHandler(void)
{uint16_t capture = 0;
	float CH1_Duty = GPIO_6_zhanbi;
	float CH2_Duty = GPIO_7_zhanbi;
  float CH3_Duty = GPIO_8_zhanbi;
	float CH4_Duty = GPIO_9_zhanbi;
	
  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
    capture = TIM_GetCapture1(TIM3);
		if(CH1_Flag == 0)
		{
			TIM_SetCompare1(TIM3, capture +(uint16_t)CCR1_Val*CH1_Duty);
			CH1_Flag = 1;
		}
		else
		{
			TIM_SetCompare1(TIM3, capture + (uint16_t)(CCR1_Val* (1- CH1_Duty)));
			CH1_Flag = 0;
		}
  }


  if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
		  TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
    capture = TIM_GetCapture2(TIM3);
		if(CH2_Flag==0)
		{
    TIM_SetCompare2(TIM3, capture + (uint16_t)CCR2_Val*CH2_Duty);
			CH2_Flag=1;
		}
  
	else
	{
		TIM_SetCompare2(TIM3, capture + (uint16_t)(CCR2_Val* (1- CH2_Duty)));
			CH2_Flag = 0;
		}
	}
	
	
	  if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
  {
		  TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
    capture = TIM_GetCapture3(TIM3);
		if(CH3_Flag==0)
		{
    TIM_SetCompare3(TIM3, capture + (uint16_t)CCR3_Val*CH3_Duty);
			CH3_Flag=1;
		}
  
	else
	{
		TIM_SetCompare3(TIM3, capture + (uint16_t)(CCR3_Val* (1- CH3_Duty)));
			CH3_Flag = 0;
		}
	}
	
	
	
	
	  if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
  {
		  TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
    capture = TIM_GetCapture4(TIM3);
		if(CH4_Flag==0)
		{
    TIM_SetCompare4(TIM3, capture + (uint16_t)CCR4_Val*CH4_Duty);
			CH4_Flag=1;
		}
  
	else
	{
		TIM_SetCompare4(TIM3, capture + (uint16_t)(CCR4_Val* (1- CH4_Duty)));
			CH4_Flag = 0;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
}





















