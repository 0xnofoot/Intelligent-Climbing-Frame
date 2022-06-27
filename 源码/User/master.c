#include "master.h"
#include "usart.h"
#include "server.h"
#include "GPS.h"
#include "shelf.h"


/*����ѭ�����ͱ�������Ϣ���غ���*/
void Master_Init(void)
{
	uint8_t server_state;
	server_state = HAL_GPIO_ReadPin(Ser_LIKA_GPIO_Port,Ser_LIKA_Pin);
	while(!server_state)
	{
		server_state = HAL_GPIO_ReadPin(Ser_LIKA_GPIO_Port,Ser_LIKA_Pin);
		HAL_Delay(100);
		//printf("come");
	}
	
	GPS_Get();
	Send_GPS();
	
	HAL_Delay(500);
	
	Shelf_Polled();
	Send_Shelf();
}


