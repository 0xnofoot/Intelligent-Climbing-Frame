#include "relay.h"
#include "flash.h"

uint8_t Value_Buffer_Close[4] = {"C"}; //继电器关闭状态数据 用于flash写入
uint8_t Value_Buffer_Open[4]  = {"O"}; //继电器打开状态数据 用于flash写入

uint8_t Relay_State[4]; //当前继电器状态数据 用于flash读取
		
void Relay_Init(void)
{
	/*继电器flash预留代码,出厂前打开下载一次，然后关闭再下载一次，出厂前总共下载两次代码*/
	//STMFLASH_Write(FLASH_VALUE_RELAY1,(uint32_t*)Value_Buffer_Open,1);//打开继电器1
  //STMFLASH_Write(FLASH_VALUE_RELAY2,(uint32_t*)Value_Buffer_Open,1);//打开继电器2
	
	/*读取继电器当前flash数据状态并初始化继电器*/
	STMFLASH_Read(FLASH_VALUE_RELAY1,(uint32_t*)Relay_State,1);
	if(Relay_State[0] == 'C') Relay1_Close();
	else Relay1_Open();
	
	STMFLASH_Read(FLASH_VALUE_RELAY2,(uint32_t*)Relay_State,1);
	if(Relay_State[0] == 'C') Relay2_Close();
	else Relay2_Open();
}


void Relay1_Open(void)
{
	STMFLASH_Write(FLASH_VALUE_RELAY1,(uint32_t*)Value_Buffer_Open,1);
	HAL_GPIO_WritePin(Relay1_GPIO_Port,Relay1_Pin,GPIO_PIN_SET);
}

void Relay1_Close(void)
{
	STMFLASH_Write(FLASH_VALUE_RELAY1,(uint32_t*)Value_Buffer_Close,1);
	HAL_GPIO_WritePin(Relay1_GPIO_Port,Relay1_Pin,GPIO_PIN_RESET);
}

void Relay2_Open(void)
{
	STMFLASH_Write(FLASH_VALUE_RELAY2,(uint32_t*)Value_Buffer_Open,1);
	HAL_GPIO_WritePin(Relay2_GPIO_Port,Relay2_Pin,GPIO_PIN_SET);
}

void Relay2_Close(void)
{
	STMFLASH_Write(FLASH_VALUE_RELAY2,(uint32_t*)Value_Buffer_Close,1);
	HAL_GPIO_WritePin(Relay2_GPIO_Port,Relay2_Pin,GPIO_PIN_RESET);
}

