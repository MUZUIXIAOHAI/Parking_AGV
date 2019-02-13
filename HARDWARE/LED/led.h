#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
// 停车AGV调试
// 四路电机方向开关量输出  PC8（左旋）、PC6（右旋）、PC11（左直）、PC1（右直）  
// 四路电机启停开关量输出  PC9（左旋）、PC7（右旋）、PC12（左直）、PD2（右直）  
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

//旋转电机方向，启停信号控制
#define LEFT_TURN_MOTOR_POWER PCout(9)
#define LEFT_TURN_MOTOR_DIR PCout(8)
#define RIGHT_TURN_MOTOR_POWER PCout(7)
#define RIGHT_TURN_MOTOR_DIR PCout(6)
//直行电机方向，启停信号控制
#define LEFT_STRAIGHT_MOTOR_POWER PCout(12)
#define LEFT_STRAIGHT_MOTOR_DIR PCout(11)
#define RIGHT_STRAIGHT_MOTOR_POWER PDout(2)
#define RIGHT_STRAIGHT_MOTOR_DIR PCout(1)
//油泵控制端口
#define PUMP_M1_TURN_ON PBout(8)=0;PBout(9)=1;
#define PUMP_M1_TURN_OFF PBout(9)=0;PBout(8)=1;
#define PUMP_M1_STOP PBout(8)=1;PBout(9)=1;
#define PUMP_M2_TURN_ON PBout(10)=0;PBout(11)=1;
#define PUMP_M2_TURN_OFF PBout(11)=0;PBout(10)=1;
#define PUMP_M2_STOP PBout(10)=1;PBout(11)=1;
#define PUMP_M3_TURN_ON PBout(12)=0;PBout(13)=1;
#define PUMP_M3_TURN_OFF PBout(13)=0;PBout(12)=1;
#define PUMP_M3_STOP PBout(12)=1;PBout(13)=1;
#define PUMP_M4_TURN_SHORT PBout(14)=0;PBout(15)=1;
#define PUMP_M4_TURN_LONG PBout(15)=0;PBout(14)=1;
#define PUMP_M4_STOP PBout(14)=1;PBout(15)=1;
//红外信号输入
#define P1 PBin(0)
#define P2 PBin(1)
#define P3 PBin(4)
//#define P4 PBin(3)

//定义控制端口，宏定义直观显示
/***电源宏定义***/
#define LEFT_STRAIGHT_MOTOR_POWER_ON LEFT_STRAIGHT_MOTOR_POWER=0
#define LEFT_STRAIGHT_MOTOR_POWER_OFF LEFT_STRAIGHT_MOTOR_POWER=1
#define RIGHT_STRAIGHT_MOTOR_POWER_ON RIGHT_STRAIGHT_MOTOR_POWER=0
#define RIGHT_STRAIGHT_MOTOR_POWER_OFF RIGHT_STRAIGHT_MOTOR_POWER=1

#define LEFT_TURN_MOTOR_POWER_ON LEFT_TURN_MOTOR_POWER=0
#define LEFT_TURN_MOTOR_POWER_OFF LEFT_TURN_MOTOR_POWER=1
#define RIGHT_TURN_MOTOR_POWER_ON RIGHT_TURN_MOTOR_POWER=0
#define RIGHT_TURN_MOTOR_POWER_OFF RIGHT_TURN_MOTOR_POWER=1


/***方向宏定义  -- 方向按照车辆前进方向定义 以大铁盒为车头  例：抓取车辆时进入车辆为倒车***/
#define LEFT_STRAIGHT_MOTOR_DIR_FRONT LEFT_STRAIGHT_MOTOR_DIR=0
#define LEFT_STRAIGHT_MOTOR_DIR_BACK LEFT_STRAIGHT_MOTOR_DIR=1
#define RIGHT_STRAIGHT_MOTOR_DIR_FRONT RIGHT_STRAIGHT_MOTOR_DIR = 1
#define RIGHT_STRAIGHT_MOTOR_DIR_BACK RIGHT_STRAIGHT_MOTOR_DIR = 0

#define LEFT_TURN_MOTOR_DIR_RIGHT LEFT_TURN_MOTOR_DIR = 0
#define LEFT_TURN_MOTOR_DIR_LEFT LEFT_TURN_MOTOR_DIR = 1
#define RIGHT_TURN_MOTOR_DIR_RIGHT RIGHT_TURN_MOTOR_DIR = 0
#define RIGHT_TURN_MOTOR_DIR_LEFT RIGHT_TURN_MOTOR_DIR = 1



void LED_Init(void);					//初始化
void MOTOR_IO_Init(void);			//电机控制端口初始化
void PUMP_IO_Init(void);			//油泵控制端口初始化
void INFRARED_IO_Init(void);	//红外IO端口初始化
#endif
