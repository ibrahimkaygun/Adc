#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t ADC_Read(void)
{
 ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_28Cycles5);
 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
 while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
 return ADC_GetConversionValue(ADC1);	
}
int main(void)
{
	uint16_t ADC_Data=0;
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef  ADC_InitStructure;
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode             = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin              = GPIO_Pin_0;
	//GPIO_InitStructure.GPIO_Speed            = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd (ADC1,ENABLE);	


	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);	
	while(ADC_GetCalibrationStatus(ADC1));

	
	//ADC_Cmd (ADC1,ENABLE);	
	//ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	while(1)
	{
		ADC_Data=ADC_Read();
		if (ADC_Data<51)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		}
		else if(ADC_Data>50  && ADC_Data<101)
		{
		 GPIO_SetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);	
		}
		else if(ADC_Data>100 && ADC_Data<151)
			{
		 GPIO_ResetBits(GPIOB, GPIO_Pin_5);
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);	
		}
		else if(ADC_Data>150  && ADC_Data<201)
		{
		 GPIO_ResetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);	
		}else if(ADC_Data>200 )
		{
		 GPIO_ResetBits(GPIOB, GPIO_Pin_5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);	
		}
	}
}