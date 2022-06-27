#include "task.h"
#include "tim.h"
#include "master.h"
#include "GPS.h"
#include "usart.h"
#include "server.h"
#include "callback.h"
#include "relay.h"
#include "shelf.h"

/*任务分配标志位*/

uint8_t flag_GPS;              //GPS信号触发及接收及发送 
uint8_t flag_slave_handle;     //RS485载荷量读取 

void Task_Init(void)
{
	 flag_GPS = 0;  
	 flag_slave_handle = 0;
	 HAL_TIM_Base_Start_IT(&htim13);
}


/*任务标志位检测，在callback中调用*/
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
	
	if(i >= 60001)//现在是1min查询且发送 
	{
		flag_GPS = 1;
		i = 0;
	}
}

/*任务处理函数*/
void Task_Handle(void)
{
	
//任务处理放进了 server.c 中
//	if(order_flag)
//	{
//		HAL_TIM_Base_Stop_IT(&htim13);
//		switch(order_flag)
//		{
//			case(_A):Relay1_Open();  order_flag=0;break; //开继电器1
//			case(_B):Relay1_Close(); order_flag=0;break; //关继电器1
//			case(_C):Send_GPS();     order_flag=0;break; //发送GPS位置信息
//			case(_D):Send_Shelf();   order_flag=0;break; //发送载荷量
//			case(_E):Relay2_Open();  order_flag=0;break; //开继电器2
//			case(_F):Relay2_Close(); order_flag=0;break; //关继电器2
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


