#include "task.h"
#include "tim.h"
#include "master.h"
#include "GPS.h"
#include "usart.h"
#include "server.h"
#include "callback.h"
#include "relay.h"
#include "shelf.h"

/*��������־λ*/

uint8_t flag_GPS;              //GPS�źŴ��������ռ����� 
uint8_t flag_slave_handle;     //RS485�غ�����ȡ 

void Task_Init(void)
{
	 flag_GPS = 0;  
	 flag_slave_handle = 0;
	 HAL_TIM_Base_Start_IT(&htim13);
}


/*�����־λ��⣬��callback�е���*/
void Task_FlagCheck(void)
{
	static uint32_t i = 0;
	static uint32_t j = 0;
	i++;
	j++;

	if(j >= 15001)//15s
	{
		flag_slave_handle = 1;
		j = 0;		
	}
	
	if(i >= 60001)//������1min��ѯ�ҷ��� 
	{
		flag_GPS = 1;
		i = 0;
	}
}

/*��������*/
void Task_Handle(void)
{
	
//������Ž��� server.c ��
//	if(order_flag)
//	{
//		HAL_TIM_Base_Stop_IT(&htim13);
//		switch(order_flag)
//		{
//			case(_A):Relay1_Open();  order_flag=0;break; //���̵���1
//			case(_B):Relay1_Close(); order_flag=0;break; //�ؼ̵���1
//			case(_C):Send_GPS();     order_flag=0;break; //����GPSλ����Ϣ
//			case(_D):Send_Shelf();   order_flag=0;break; //�����غ���
//			case(_E):Relay2_Open();  order_flag=0;break; //���̵���2
//			case(_F):Relay2_Close(); order_flag=0;break; //�ؼ̵���2
//			default:break;
//		}
//		order_flag=0;
//		HAL_TIM_Base_Start_IT(&htim13);
//	}
	
	if(flag_slave_handle)
	{
		HAL_TIM_Base_Stop_IT(&htim13);
		Shelf_Polled();
		Send_Shelf();
		flag_slave_handle = 0;
		HAL_TIM_Base_Start_IT(&htim13);
	}
	
	if(flag_GPS)
	{	
		HAL_TIM_Base_Stop_IT(&htim13);
		GPS_Get();
		Send_GPS();
		flag_GPS = 0;
		HAL_TIM_Base_Start_IT(&htim13);
	}

}


