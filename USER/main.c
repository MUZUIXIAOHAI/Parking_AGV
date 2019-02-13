#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "encoder.h"
 
/************************************************ 
 
 停车AGV初期调试 2019-1-16
 4路PWM输出  PA0、PA1、PA2、PA3
 四路电机方向开关量输出  PC8（左旋）、PC6（右旋）、PC11（左直）、PC1（右直）  
 四路电机启停开关量输出  PC9（左旋）、PC7（右旋）、PC12（左直）、PD2（右直）  
 
 编码器读取 
 PB6、PB7   TIM4     
 PA8、PA9   TIM1
 PA6、PA7   TIM3
 
 停车AGV初期调试 2019-1-24 V1.1
 写了以下的宏定义：
 1、给定各个电机速度的函数
 2、各个电机电源开关的给定
 3、各个电机方向的给定
 4、编码器的值的取回
 
 
 停车AGV调试初期 2019-1-25 V1.2
 
 转向编码器设定3500左右为角度80度左右;
 左边电机给定100有可能还不会转，有可能两边电机速度不一样，这个问题还没调试;
 已完成:
 1、直线行走,实时纠正车轮朝向；
 2、完成抓取车辆动作与流程，开机时机器人后退，检测车辆前轮，检测到前轮之后开始抓取车辆，抓取完毕后机器人前行
 
 
 作者：zhong
************************************************/

volatile s16 encoder_num_1;
volatile s16 encoder_num_3;
volatile s16 encoder_num_4;

//存储编码器值的变量
volatile u32 left_turn_motor_encoder_value ;
volatile u32 right_turn_motor_encoder_value ;
volatile u32 left_straight_motor_encoder_value ;

//抓取车辆动作函数
void grab_the_car(void) {
	
	int delay_i=0;
	//检测前轮标志
	char front_wheel_flag = 0;
	
	//车身延长到最长
	PUMP_M4_TURN_LONG;
	for(delay_i=0; delay_i<10; delay_i++){
		delay_ms(1000);
	}
	PUMP_M4_STOP; //伸到最长后关闭油阀
	//当延伸到最长时，打开M3开关
	PUMP_M3_TURN_ON;
	for(delay_i=0; delay_i<18; delay_i++){
		delay_ms(1000);
	}
	PUMP_M3_STOP; //打开M3后关闭油阀
	
	//收缩车身，同时检测前轮
	PUMP_M4_TURN_SHORT;
	while(front_wheel_flag == 0) {
			if(P3 == 0){
				delay_ms(200);
				if(P3 == 0) front_wheel_flag = 1;
			}
	}
	PUMP_M4_STOP; //到位后关闭油阀
	
	//打开M1、M2开关，把车辆抓取起来
//	PUMP_M1_TURN_ON; //M1漏油屏蔽该信号
	PUMP_M2_TURN_ON;
	for(delay_i=0; delay_i<15; delay_i++){
		delay_ms(1000);
	}
	//车辆抓取起来后关闭油阀
	PUMP_M1_STOP;
	PUMP_M2_STOP;
	
}

//机器人各开关量复位函数
void reset_robot()
{
	int delay_i=0;
	
	PUMP_M4_TURN_SHORT;
	PUMP_M2_TURN_OFF;
	PUMP_M3_TURN_OFF;
	
	for(delay_i=0; delay_i<10; delay_i++){
		delay_ms(1000);
	}
	
	PUMP_M4_STOP;
	PUMP_M2_STOP;
	PUMP_M3_STOP;
	
}

 int main(void)
 {		
 	u16 motorspeed=0;
	u8 dir=1;	
	 
	 
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 
	uart_init(115200);	 //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	 
	MOTOR_IO_Init();			//电机端口初始化
	PUMP_IO_Init();				//油泵控制端口初始化
	INFRARED_IO_Init();		//红外IO端口初始化

	TIM_Init();						//定时器编码器模式定义
	 
	 //使能电机
	 LEFT_STRAIGHT_MOTOR_POWER_ON;
	 RIGHT_STRAIGHT_MOTOR_POWER_ON;
	 LEFT_TURN_MOTOR_POWER_ON;
	 RIGHT_TURN_MOTOR_POWER_ON;
	 
	 //设定电机运动方向
	 LEFT_STRAIGHT_MOTOR_DIR_BACK;
	 RIGHT_STRAIGHT_MOTOR_DIR_BACK;
	 LEFT_TURN_MOTOR_DIR_LEFT;
	 RIGHT_TURN_MOTOR_DIR_LEFT;
	 
	 //设定电机速度 0-999
	 motorspeed = 200;	
	 
	  //设定电机速度  初始为静止
		LEFT_STRAIGHT_MOTOR_SPEED(0);		
		RIGHT_STRAIGHT_MOTOR_SPEED(0);
		LEFT_TURN_MOTOR_SPEED(0);
		RIGHT_TURN_MOTOR_SPEED(0);	
		
//		LEFT_TURN_MOTOR_DIR_LEFT;
//		LEFT_TURN_MOTOR_SPEED(motorspeed);	
//		
//		RIGHT_TURN_MOTOR_DIR_LEFT;
//		RIGHT_TURN_MOTOR_SPEED(motorspeed);
//		
//		//DEBUG
//	 while(1) {
//		 
//		 
//		 //取回编码器的值
//		left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;		
//		right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;	
//		left_straight_motor_encoder_value = GET_LEFT_STRAIGHT_MOTOR_ENCODER;
//		 
//		encoder_num_3=TIM_GetCounter(TIM3);		//取回编码器的值
//		encoder_num_4=TIM_GetCounter(TIM4);		//取回编码器的值
//		encoder_num_1=TIM_GetCounter(TIM1);		//取回编码器的值
//		 
//		 if(left_turn_motor_encoder_value > 3500) {
//			 LEFT_TURN_MOTOR_DIR_RIGHT;
//			 
//		 }
//		 if(left_turn_motor_encoder_value < 50) {
//		   LEFT_TURN_MOTOR_DIR_LEFT;
//			 
//		 }
//		 
//		 if(right_turn_motor_encoder_value > 3500) {
//				RIGHT_TURN_MOTOR_DIR_RIGHT;
//		 }
//		 if(right_turn_motor_encoder_value < 50) {
//			 RIGHT_TURN_MOTOR_DIR_LEFT;
//		 }
//		 
//	 }


	 //设定电机运动方向
	 LEFT_STRAIGHT_MOTOR_DIR_BACK;
	 RIGHT_STRAIGHT_MOTOR_DIR_BACK;
	 LEFT_TURN_MOTOR_DIR_RIGHT;
	 RIGHT_TURN_MOTOR_DIR_RIGHT;
	 
	 while(1) {
		
		 //设定电机速度 让机器人直行  转向电机不动作
		LEFT_STRAIGHT_MOTOR_SPEED(motorspeed);		
		RIGHT_STRAIGHT_MOTOR_SPEED(motorspeed);
		LEFT_TURN_MOTOR_SPEED(0);
		RIGHT_TURN_MOTOR_SPEED(0);	

		 //取回编码器的值
		left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;		
		right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;	
		left_straight_motor_encoder_value = GET_LEFT_STRAIGHT_MOTOR_ENCODER;	
		 
		 //矫正左轮电机方向
		 while(left_turn_motor_encoder_value > 50 && left_turn_motor_encoder_value < 0xffff-50) {
				//停止直行电机运行
				LEFT_STRAIGHT_MOTOR_SPEED(0);		
				RIGHT_STRAIGHT_MOTOR_SPEED(0);
			 
				while(left_turn_motor_encoder_value > 50 && left_turn_motor_encoder_value < 3000) {
					//这里设定编码器值减小的电机方向
					LEFT_TURN_MOTOR_DIR_RIGHT;
					LEFT_TURN_MOTOR_SPEED(30);
					left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;	
				}
				while(left_turn_motor_encoder_value < 0xffff-50 && left_turn_motor_encoder_value > 0xffff-3000) {
					//这里设定编码器值增大的电机方向
					LEFT_TURN_MOTOR_DIR_LEFT;
					LEFT_TURN_MOTOR_SPEED(30);
					left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;
				}
		 }
		 //矫正右轮电机方向
		 while(right_turn_motor_encoder_value > 50 && right_turn_motor_encoder_value < 0xffff-50) {
				//停止直行电机运行
				LEFT_STRAIGHT_MOTOR_SPEED(0);		
				RIGHT_STRAIGHT_MOTOR_SPEED(0);
			 
				while(right_turn_motor_encoder_value > 50 && right_turn_motor_encoder_value < 3000) {
					//这里设定编码器值减小的电机方向
					RIGHT_TURN_MOTOR_DIR_RIGHT;
					RIGHT_TURN_MOTOR_SPEED(30);
					right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;	
				}
				while(right_turn_motor_encoder_value < 0xffff-50 && right_turn_motor_encoder_value > 0xffff-3000) {
					//这里设定编码器值增大的电机方向
					RIGHT_TURN_MOTOR_DIR_LEFT;
					RIGHT_TURN_MOTOR_SPEED(30);
					right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;
				}
		 }
		 
		 //****开始抓取动作逻辑****//
		 //当检测到P1、P2信号之后开始抓取动作
		 if (P1 == 0 && P2 == 0)
		 {
			 delay_ms(500);			//确认信号，有时候信号有抖动
			 if (P1 == 0 && P2 == 0) {
					//先停车
					LEFT_STRAIGHT_MOTOR_SPEED(0);		
					RIGHT_STRAIGHT_MOTOR_SPEED(0);
					grab_the_car();
					LEFT_STRAIGHT_MOTOR_DIR_FRONT;
					RIGHT_STRAIGHT_MOTOR_DIR_FRONT;
			 }
					
		 }
		 //检测到P3信号开始复位
		 if (P3 == 0)
		 {
				delay_ms(500);		//确认信号，有时候信号有抖动
				if(P3 == 0)
				{
					//先停车
					LEFT_STRAIGHT_MOTOR_SPEED(0);		
					RIGHT_STRAIGHT_MOTOR_SPEED(0);
					//复位机器人
					reset_robot();
				}
		 } 
		 
		 
	 }
	 
 }

