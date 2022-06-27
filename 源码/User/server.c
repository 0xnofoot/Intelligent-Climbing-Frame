#include "server.h"
#include "usart.h"
#include "callback.h"
#include "master.h"
#include "GPS.h"
#include "relay.h"
#include "shelf.h"

uint8_t order_flag;


void Server_Init(void)
{
	uint8_t fifo;
	order_flag = 0;
	HAL_GPIO_WritePin(Ser_IO_RT_GPIO_Port,Ser_IO_RT_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(Ser_RST_GPIO_Port,Ser_RST_Pin,GPIO_PIN_SET);
	HAL_Delay(10);
  HAL_UART_Receive_IT(&huart1,&fifo,1);
}

/*发送数据到服务器*/
void Server_SendData(uint8_t *data ,uint16_t len)
{
		HAL_UART_Transmit(&huart1,data,len,0x20);
}

/*发送字符串到服务器*/
void Server_SendStr(char *str)
{
	while(*str)
		{
			HAL_UART_Transmit(&huart1,str,1,0x20);
			while(!__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC));	
			str++;
		}
}

/*接收服务器数据*/
void Server_ReceiceData(uint8_t *data,uint16_t len)
{
	HAL_UART_Receive(&huart1,data,len,0Xff);
}

void Server_Data_Analysis(uint8_t data)
{
	static uint8_t state = 0;

	if(state == 0&&data == MASTER_NUM_1)
	{
		state = 1;
	}
	else if(state == 1&&data == MASTER_NUM_2)
	{
		state = 2;
	}
	else if(state == 2&&data == MASTER_NUM_3)
	{
		state = 3;
	}
	else if(state == 3&&data == MASTER_NUM_4)
	{
		state = 4;
	}
	else if(state == 4&&data == MASTER_NUM_5)
	{
		state = 5;
	}
	else if(state == 5)
	{
		state = 0;
		order_flag = data;
	if(order_flag)
	{
		switch(order_flag)
		{
			case(_A):Relay1_Open();  order_flag=0;break; //开继电器1
			case(_B):Relay1_Close(); order_flag=0;break; //关继电器1
			case(_C):Send_GPS();     order_flag=0;break; //发送GPS位置信息
			case(_D):Send_Shelf();   order_flag=0;break; //发送载荷量
			case(_E):Relay2_Open();  order_flag=0;break; //开继电器2
			case(_F):Relay2_Close(); order_flag=0;break; //关继电器2
			default:break;
		}
		order_flag=0;
	}		
	}
	else state = 0;
}

