/********************************************************************************
  //ͣ��AGV���Գ���
	//�������������ö�ʱ���ı�����ģʽ���ܱ������źţ���������ת�ǶȻ������߳���
  *******************************************************************************/
#include "encoder.h"


void TIM1_Mode_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
/*----------------------------------------------------------------*/
	//�������˿ڳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.08,09 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	
	//��ʱ����ʼ������
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʹ��TIM1
	TIM_DeInit(TIM1);
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM1��ʱ�� */
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM1, &TIM_ICInitStructure);
  
	//TIM_ARRPreloadConfig(TIM1, ENABLE);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM1->CNT =0;
	
	TIM_Cmd(TIM1, ENABLE);   //ʹ�ܶ�ʱ��1
}

void TIM3_Mode_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
/*----------------------------------------------------------------*/
	//�������˿ڳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	
	//��ʱ����ʼ������
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ��TIM3
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM3��ʱ�� */
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM3->CNT =0;
	
	TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ��3
}


void TIM4_Mode_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
/*----------------------------------------------------------------*/
	//�������˿ڳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PB.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
/*----------------------------------------------------------------*/	
	//��ʱ����ʼ������
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��TIM4
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =0xffff;       //
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM4��ʱ�� */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
	//TIM_ARRPreloadConfig(TIM4, ENABLE);
 // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //ʹ���ж�
  //Reset counter
  TIM4->CNT =0;
	
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��4
}


void TIM_Init(void)
{
	TIM1_Mode_Config();
	TIM2_PWM_Init(999,15);	 //����Ƶ��PWMƵ��=72000000/15/1000=4.8Khz  4·����PWM�����
  TIM3_Mode_Config();
	TIM4_Mode_Config();
}

