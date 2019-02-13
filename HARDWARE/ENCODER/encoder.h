#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "timer.h"


/***�������������ٶȸ���***/
#define LEFT_STRAIGHT_MOTOR_SPEED(speed) TIM_SetCompare4(TIM2,998-speed)
#define RIGHT_STRAIGHT_MOTOR_SPEED(speed) TIM_SetCompare3(TIM2,998-speed)
#define LEFT_TURN_MOTOR_SPEED(speed) TIM_SetCompare2(TIM2,998-speed)
#define RIGHT_TURN_MOTOR_SPEED(speed) TIM_SetCompare1(TIM2,998-speed)

/***����������ת����ı��������Լ�����ǰ�����������***/
#define GET_LEFT_TURN_MOTOR_ENCODER TIM_GetCounter(TIM3)
#define GET_RIGHT_TURN_MOTOR_ENCODER TIM_GetCounter(TIM1)
#define GET_LEFT_STRAIGHT_MOTOR_ENCODER TIM_GetCounter(TIM4)


void TIM_Init(void);
void TIM3_Mode_Config(void);
#endif 
