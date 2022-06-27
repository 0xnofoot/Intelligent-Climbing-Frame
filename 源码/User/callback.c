#include "callback.h"
#include "tim.h"
#include "task.h"
#include "master.h"
#include "usart.h"
#include "server.h"
#include "GPS.h"
#include "shelf.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	/*tim13回调函数，用于分配各项任务*/
	if(htim->Instance == htim13.Instance)
	{
		Task_FlagCheck();
	}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  static uint8_t server_fifo;
	static uint8_t gps_fifo;
	//static uint8_t shelf_fifo;
	
	if(huart->Instance == huart1.Instance)
	{		
	  HAL_UART_Receive_IT(&huart1,&server_fifo,1);
    Server_Data_Analysis(server_fifo);			
	}

		if(huart->Instance == huart3.Instance)
	{
		if(gps_get)
		{
			HAL_UART_Receive_IT(&huart3,&gps_fifo,1);
			GPS_Data_Analysis(gps_fifo);
    }
	}
	
//	  if(huart->Instance == huart5.Instance)
//	{
//		{
//			HAL_UART_Receive_IT(&huart5,&shelf_fifo,1);
//			RS485_Data_Analysis(shelf_fifo);
//    }
//	}

}

