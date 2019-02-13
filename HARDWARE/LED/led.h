#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
// ͣ��AGV����
// ��·������򿪹������  PC8����������PC6����������PC11����ֱ����PC1����ֱ��  
// ��·�����ͣ���������  PC9����������PC7����������PC12����ֱ����PD2����ֱ��  
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

//��ת���������ͣ�źſ���
#define LEFT_TURN_MOTOR_POWER PCout(9)
#define LEFT_TURN_MOTOR_DIR PCout(8)
#define RIGHT_TURN_MOTOR_POWER PCout(7)
#define RIGHT_TURN_MOTOR_DIR PCout(6)
//ֱ�е��������ͣ�źſ���
#define LEFT_STRAIGHT_MOTOR_POWER PCout(12)
#define LEFT_STRAIGHT_MOTOR_DIR PCout(11)
#define RIGHT_STRAIGHT_MOTOR_POWER PDout(2)
#define RIGHT_STRAIGHT_MOTOR_DIR PCout(1)
//�ͱÿ��ƶ˿�
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
//�����ź�����
#define P1 PBin(0)
#define P2 PBin(1)
#define P3 PBin(4)
//#define P4 PBin(3)

//������ƶ˿ڣ��궨��ֱ����ʾ
/***��Դ�궨��***/
#define LEFT_STRAIGHT_MOTOR_POWER_ON LEFT_STRAIGHT_MOTOR_POWER=0
#define LEFT_STRAIGHT_MOTOR_POWER_OFF LEFT_STRAIGHT_MOTOR_POWER=1
#define RIGHT_STRAIGHT_MOTOR_POWER_ON RIGHT_STRAIGHT_MOTOR_POWER=0
#define RIGHT_STRAIGHT_MOTOR_POWER_OFF RIGHT_STRAIGHT_MOTOR_POWER=1

#define LEFT_TURN_MOTOR_POWER_ON LEFT_TURN_MOTOR_POWER=0
#define LEFT_TURN_MOTOR_POWER_OFF LEFT_TURN_MOTOR_POWER=1
#define RIGHT_TURN_MOTOR_POWER_ON RIGHT_TURN_MOTOR_POWER=0
#define RIGHT_TURN_MOTOR_POWER_OFF RIGHT_TURN_MOTOR_POWER=1


/***����궨��  -- �����ճ���ǰ�������� �Դ�����Ϊ��ͷ  ����ץȡ����ʱ���복��Ϊ����***/
#define LEFT_STRAIGHT_MOTOR_DIR_FRONT LEFT_STRAIGHT_MOTOR_DIR=0
#define LEFT_STRAIGHT_MOTOR_DIR_BACK LEFT_STRAIGHT_MOTOR_DIR=1
#define RIGHT_STRAIGHT_MOTOR_DIR_FRONT RIGHT_STRAIGHT_MOTOR_DIR = 1
#define RIGHT_STRAIGHT_MOTOR_DIR_BACK RIGHT_STRAIGHT_MOTOR_DIR = 0

#define LEFT_TURN_MOTOR_DIR_RIGHT LEFT_TURN_MOTOR_DIR = 0
#define LEFT_TURN_MOTOR_DIR_LEFT LEFT_TURN_MOTOR_DIR = 1
#define RIGHT_TURN_MOTOR_DIR_RIGHT RIGHT_TURN_MOTOR_DIR = 0
#define RIGHT_TURN_MOTOR_DIR_LEFT RIGHT_TURN_MOTOR_DIR = 1



void LED_Init(void);					//��ʼ��
void MOTOR_IO_Init(void);			//������ƶ˿ڳ�ʼ��
void PUMP_IO_Init(void);			//�ͱÿ��ƶ˿ڳ�ʼ��
void INFRARED_IO_Init(void);	//����IO�˿ڳ�ʼ��
#endif
