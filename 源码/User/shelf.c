#include "shelf.h"
#include "usart.h"
#include "master.h"
#include "server.h"
#include "flash.h"
#include "relay.h"

float shelf_buffer[40];
uint8_t shelf_char_buffer[40][7];

uint8_t Relay_State_now[4]; //当前继电器状态数据 用于flash读取
uint8_t Rise_State;

void RS485_Init(void)
{
	//uint8_t fifo;
	HAL_GPIO_WritePin(GPIOE, RS485_DE_Pin|RS485_RE_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	//HAL_UART_Receive_IT(&huart5,&fifo,1);
}

void RS485_Config_Send(void)
{
	HAL_GPIO_WritePin(GPIOE, RS485_DE_Pin|RS485_RE_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
}

void RS485_Config_Receive(void)
{
	//uint8_t fifo;
	HAL_GPIO_WritePin(GPIOE, RS485_DE_Pin|RS485_RE_Pin, GPIO_PIN_RESET);
	//HAL_Delay(1);
	//HAL_UART_Receive_IT(&huart5,&fifo,1);
}

void RS485_SendData(uint8_t *data ,uint16_t len)
{
		HAL_UART_Transmit(&huart5,data,len,0x20);
}

void RS485_Data_Analysis(uint8_t data[12],uint8_t id)
{
	if((data[0] == 0XF0)&&(data[11] == 0XFF))
	{
		shelf_char_buffer[data[2]-1][0] = (id/10)+0x30;
		shelf_char_buffer[data[2]-1][1] = (id%10)+0x30;
		
		shelf_buffer[data[2]-1] = data[7]+data[8]*0.1+data[9]*0.01;
		if(data[4] == 0x01)
		{
			shelf_buffer[data[2]-1] = -1 * shelf_buffer[data[2]];
			shelf_char_buffer[data[2]-1][2] = '-';
		}
		else
		{
			shelf_char_buffer[data[2]-1][2] = '+';
		}
		shelf_char_buffer[data[2]-1][3] = data[7]+0x30;
		shelf_char_buffer[data[2]-1][4] = data[8]+0x30;
		shelf_char_buffer[data[2]-1][5] = data[9]+0x30;
		shelf_char_buffer[data[2]-1][6] = ',';
//		printf("Cal_%d_%s\n", data[2],shelf_char_buffer[data[2]-1]);
	}
}

void Polled_SendData(uint8_t address)
{
	uint8_t address_data[4] = {0XF0,0XA0,address,0XFF};
	RS485_Config_Send();
	RS485_SendData(address_data,4);
}


void Shelf_Polled(void)
{
	uint8_t add;
	uint8_t fifo[12];
	for(add = 1;add <= 40;add++)
	{
		Polled_SendData(add);
		RS485_Config_Receive();
		if(HAL_UART_Receive(&huart5,fifo,12,0XFF) == HAL_OK)
		{
			RS485_Data_Analysis(fifo,add); 
		}
		HAL_Delay(150);
		RS485_Config_Send();
	}
	
}

void Send_Shelf(void)
{
	uint8_t master[6] = {MASTER_NUM_1,MASTER_NUM_2,MASTER_NUM_3,MASTER_NUM_4,MASTER_NUM_5,','};
	uint8_t i =0;
	
	STMFLASH_Read(FLASH_VALUE_RELAY1,(uint32_t*)Relay_State_now,1);
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
		Rise_State = 'U';
	else Rise_State = 'S';
	uint8_t state_check[3] = {Relay_State_now[0],Rise_State,','};
	
	Server_SendData(master,6);
	Server_SendData(state_check,3);
	for(i=0;i<=39;i++)
	{
		Server_SendData(shelf_char_buffer[i],7);
//		printf("Send_%d_%s\n", (i+1),shelf_char_buffer[i]);
	}
}


