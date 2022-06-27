#include "relay.h"
#include "flash.h"

uint8_t Value_Buffer_Close[4] = {"C"}; //�̵����ر�״̬���� ����flashд��
uint8_t Value_Buffer_Open[4]  = {"O"}; //�̵�����״̬���� ����flashд��

uint8_t Relay_State[4]; //��ǰ�̵���״̬���� ����flash��ȡ
		
void Relay_Init(void)
{
	/*�̵���flashԤ������,����ǰ������һ�Σ�Ȼ��ر�������һ�Σ�����ǰ�ܹ��������δ���*/
	//STMFLASH_Write(FLASH_VALUE_RELAY1,(uint32_t*)Value_Buffer_Open,1);//�򿪼̵���1
  //STMFLASH_Write(FLASH_VALUE_RELAY2,(uint32_t*)Value_Buffer_Open,1);//�򿪼̵���2
	
	/*��ȡ�̵�����ǰflash����״̬����ʼ���̵���*/
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

