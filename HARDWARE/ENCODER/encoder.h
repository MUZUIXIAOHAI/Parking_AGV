#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "timer.h"


/***定义各个电机的速度给定***/
#define LEFT_STRAIGHT_MOTOR_SPEED(speed) TIM_SetCompare4(TIM2,998-speed)
#define RIGHT_STRAIGHT_MOTOR_SPEED(speed) TIM_SetCompare3(TIM2,998-speed)
#define LEFT_TURN_MOTOR_SPEED(speed) TIM_SetCompare2(TIM2,998-speed)
#define RIGHT_TURN_MOTOR_SPEED(speed) TIM_SetCompare1(TIM2,998-speed)

/***定义左右旋转电机的编码器，以及左轮前进电机编码器***/
#define GET_LEFT_TURN_MOTOR_ENCODER TIM_GetCounter(TIM3)
#define GET_RIGHT_TURN_MOTOR_ENCODER TIM_GetCounter(TIM1)
#define GET_LEFT_STRAIGHT_MOTOR_ENCODER TIM_GetCounter(TIM4)


void TIM_Init(void);
void TIM3_Mode_Config(void);
#endif 
