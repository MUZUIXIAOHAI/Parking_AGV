#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "encoder.h"
 
/************************************************ 
 
 ͣ��AGV���ڵ��� 2019-1-16
 4·PWM���  PA0��PA1��PA2��PA3
 ��·������򿪹������  PC8����������PC6����������PC11����ֱ����PC1����ֱ��  
 ��·�����ͣ���������  PC9����������PC7����������PC12����ֱ����PD2����ֱ��  
 
 ��������ȡ 
 PB6��PB7   TIM4     
 PA8��PA9   TIM1
 PA6��PA7   TIM3
 
 ͣ��AGV���ڵ��� 2019-1-24 V1.1
 д�����µĺ궨�壺
 1��������������ٶȵĺ���
 2�����������Դ���صĸ���
 3�������������ĸ���
 4����������ֵ��ȡ��
 
 
 ͣ��AGV���Գ��� 2019-1-25 V1.2
 
 ת��������趨3500����Ϊ�Ƕ�80������;
 ��ߵ������100�п��ܻ�����ת���п������ߵ���ٶȲ�һ����������⻹û����;
 �����:
 1��ֱ������,ʵʱ�������ֳ���
 2�����ץȡ�������������̣�����ʱ�����˺��ˣ���⳵��ǰ�֣���⵽ǰ��֮��ʼץȡ������ץȡ��Ϻ������ǰ��
 
 
 ���ߣ�zhong
************************************************/

volatile s16 encoder_num_1;
volatile s16 encoder_num_3;
volatile s16 encoder_num_4;

//�洢������ֵ�ı���
volatile u32 left_turn_motor_encoder_value ;
volatile u32 right_turn_motor_encoder_value ;
volatile u32 left_straight_motor_encoder_value ;

//ץȡ������������
void grab_the_car(void) {
	
	int delay_i=0;
	//���ǰ�ֱ�־
	char front_wheel_flag = 0;
	
	//�����ӳ����
	PUMP_M4_TURN_LONG;
	for(delay_i=0; delay_i<10; delay_i++){
		delay_ms(1000);
	}
	PUMP_M4_STOP; //�쵽���ر��ͷ�
	//�����쵽�ʱ����M3����
	PUMP_M3_TURN_ON;
	for(delay_i=0; delay_i<18; delay_i++){
		delay_ms(1000);
	}
	PUMP_M3_STOP; //��M3��ر��ͷ�
	
	//��������ͬʱ���ǰ��
	PUMP_M4_TURN_SHORT;
	while(front_wheel_flag == 0) {
			if(P3 == 0){
				delay_ms(200);
				if(P3 == 0) front_wheel_flag = 1;
			}
	}
	PUMP_M4_STOP; //��λ��ر��ͷ�
	
	//��M1��M2���أ��ѳ���ץȡ����
//	PUMP_M1_TURN_ON; //M1©�����θ��ź�
	PUMP_M2_TURN_ON;
	for(delay_i=0; delay_i<15; delay_i++){
		delay_ms(1000);
	}
	//����ץȡ������ر��ͷ�
	PUMP_M1_STOP;
	PUMP_M2_STOP;
	
}

//�����˸���������λ����
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
	 
	 
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	 
	MOTOR_IO_Init();			//����˿ڳ�ʼ��
	PUMP_IO_Init();				//�ͱÿ��ƶ˿ڳ�ʼ��
	INFRARED_IO_Init();		//����IO�˿ڳ�ʼ��

	TIM_Init();						//��ʱ��������ģʽ����
	 
	 //ʹ�ܵ��
	 LEFT_STRAIGHT_MOTOR_POWER_ON;
	 RIGHT_STRAIGHT_MOTOR_POWER_ON;
	 LEFT_TURN_MOTOR_POWER_ON;
	 RIGHT_TURN_MOTOR_POWER_ON;
	 
	 //�趨����˶�����
	 LEFT_STRAIGHT_MOTOR_DIR_BACK;
	 RIGHT_STRAIGHT_MOTOR_DIR_BACK;
	 LEFT_TURN_MOTOR_DIR_LEFT;
	 RIGHT_TURN_MOTOR_DIR_LEFT;
	 
	 //�趨����ٶ� 0-999
	 motorspeed = 200;	
	 
	  //�趨����ٶ�  ��ʼΪ��ֹ
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
//		 //ȡ�ر�������ֵ
//		left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;		
//		right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;	
//		left_straight_motor_encoder_value = GET_LEFT_STRAIGHT_MOTOR_ENCODER;
//		 
//		encoder_num_3=TIM_GetCounter(TIM3);		//ȡ�ر�������ֵ
//		encoder_num_4=TIM_GetCounter(TIM4);		//ȡ�ر�������ֵ
//		encoder_num_1=TIM_GetCounter(TIM1);		//ȡ�ر�������ֵ
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


	 //�趨����˶�����
	 LEFT_STRAIGHT_MOTOR_DIR_BACK;
	 RIGHT_STRAIGHT_MOTOR_DIR_BACK;
	 LEFT_TURN_MOTOR_DIR_RIGHT;
	 RIGHT_TURN_MOTOR_DIR_RIGHT;
	 
	 while(1) {
		
		 //�趨����ٶ� �û�����ֱ��  ת����������
		LEFT_STRAIGHT_MOTOR_SPEED(motorspeed);		
		RIGHT_STRAIGHT_MOTOR_SPEED(motorspeed);
		LEFT_TURN_MOTOR_SPEED(0);
		RIGHT_TURN_MOTOR_SPEED(0);	

		 //ȡ�ر�������ֵ
		left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;		
		right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;	
		left_straight_motor_encoder_value = GET_LEFT_STRAIGHT_MOTOR_ENCODER;	
		 
		 //�������ֵ������
		 while(left_turn_motor_encoder_value > 50 && left_turn_motor_encoder_value < 0xffff-50) {
				//ֱֹͣ�е������
				LEFT_STRAIGHT_MOTOR_SPEED(0);		
				RIGHT_STRAIGHT_MOTOR_SPEED(0);
			 
				while(left_turn_motor_encoder_value > 50 && left_turn_motor_encoder_value < 3000) {
					//�����趨������ֵ��С�ĵ������
					LEFT_TURN_MOTOR_DIR_RIGHT;
					LEFT_TURN_MOTOR_SPEED(30);
					left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;	
				}
				while(left_turn_motor_encoder_value < 0xffff-50 && left_turn_motor_encoder_value > 0xffff-3000) {
					//�����趨������ֵ����ĵ������
					LEFT_TURN_MOTOR_DIR_LEFT;
					LEFT_TURN_MOTOR_SPEED(30);
					left_turn_motor_encoder_value = GET_LEFT_TURN_MOTOR_ENCODER;
				}
		 }
		 //�������ֵ������
		 while(right_turn_motor_encoder_value > 50 && right_turn_motor_encoder_value < 0xffff-50) {
				//ֱֹͣ�е������
				LEFT_STRAIGHT_MOTOR_SPEED(0);		
				RIGHT_STRAIGHT_MOTOR_SPEED(0);
			 
				while(right_turn_motor_encoder_value > 50 && right_turn_motor_encoder_value < 3000) {
					//�����趨������ֵ��С�ĵ������
					RIGHT_TURN_MOTOR_DIR_RIGHT;
					RIGHT_TURN_MOTOR_SPEED(30);
					right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;	
				}
				while(right_turn_motor_encoder_value < 0xffff-50 && right_turn_motor_encoder_value > 0xffff-3000) {
					//�����趨������ֵ����ĵ������
					RIGHT_TURN_MOTOR_DIR_LEFT;
					RIGHT_TURN_MOTOR_SPEED(30);
					right_turn_motor_encoder_value = GET_RIGHT_TURN_MOTOR_ENCODER;
				}
		 }
		 
		 //****��ʼץȡ�����߼�****//
		 //����⵽P1��P2�ź�֮��ʼץȡ����
		 if (P1 == 0 && P2 == 0)
		 {
			 delay_ms(500);			//ȷ���źţ���ʱ���ź��ж���
			 if (P1 == 0 && P2 == 0) {
					//��ͣ��
					LEFT_STRAIGHT_MOTOR_SPEED(0);		
					RIGHT_STRAIGHT_MOTOR_SPEED(0);
					grab_the_car();
					LEFT_STRAIGHT_MOTOR_DIR_FRONT;
					RIGHT_STRAIGHT_MOTOR_DIR_FRONT;
			 }
					
		 }
		 //��⵽P3�źſ�ʼ��λ
		 if (P3 == 0)
		 {
				delay_ms(500);		//ȷ���źţ���ʱ���ź��ж���
				if(P3 == 0)
				{
					//��ͣ��
					LEFT_STRAIGHT_MOTOR_SPEED(0);		
					RIGHT_STRAIGHT_MOTOR_SPEED(0);
					//��λ������
					reset_robot();
				}
		 } 
		 
		 
	 }
	 
 }

