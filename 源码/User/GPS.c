#include "GPS.h"
#include "server.h"
#include "usart.h"
#include "callback.h"
#include "master.h"

uint8_t gps_get=0;
uint8_t gps_buff[6]; //GPS数据缓存数组
uint8_t gps_data_buff[26];//当前经纬度数据      //校验用
uint8_t gps_data_buff_back[26];//备份经纬度数据 //发送用

void GPS_Init(void)
{
	uint8_t gps_state;
	HAL_Delay(1000);
	gps_state = HAL_GPIO_ReadPin(GPS_PPS_GPIO_Port,GPS_PPS_Pin);
		while(!gps_state)
	{
		gps_state = HAL_GPIO_ReadPin(GPS_PPS_GPIO_Port,GPS_PPS_Pin);
		HAL_Delay(100);
	}
	gps_get = 0;
	HAL_Delay(1000);
	GPS_Get();
	HAL_Delay(1000);
}

void GPS_Get(void)
{
	static uint8_t fifo;
	gps_get = 1;
	HAL_UART_Receive_IT(&huart3,&fifo,1);
}


void GPS_Data_Analysis(uint8_t data)
{
	static uint8_t count = 0;
	static uint8_t data_count = 0;
	static uint8_t data_flag = 0;
	static uint8_t get_flag = 0;
	uint8_t i;
	
	if(data == '$')
	{
		data_flag = 1;
		count = 0;

	}
	
	if(data_flag)
	{
		gps_buff[count] = data;
		count++;
		if(count >= 6 ) count = 0;
		
		if(data == ',')
		{
			data_flag = 0;
			count = 0;
			if(gps_buff[1] == 'G' && gps_buff[2] == 'N' && gps_buff[5] == 'L' )
			{
				get_flag = 1;
				return;
			}				
		}
	}
	
	if(get_flag == 1)
	{
		gps_data_buff[data_count] = data;
		data_count++;
		if(data_count >= 26) 
		{
			data_count = 0;
			get_flag = 0;
			gps_get = 0;	
			if((gps_data_buff[0]>=_0)&&(gps_data_buff[0]<=_9) && (gps_data_buff[1]>=_0)&&(gps_data_buff[1]<=_9))
			{
				for(i=0;i<26;i++)
				{
					gps_data_buff_back[i] = gps_data_buff[i];
				}
				//printf("%s\n",gps_data_buff_back);				
			}

		}
	}
}

void Send_GPS(void)
{
	uint8_t master[6] = {MASTER_NUM_1,MASTER_NUM_2,MASTER_NUM_3,MASTER_NUM_4,MASTER_NUM_5,','};
	Server_SendData(master,6);	
	Server_SendData(gps_data_buff,26);
}
