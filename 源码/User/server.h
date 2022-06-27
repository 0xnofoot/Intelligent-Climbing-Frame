#ifndef __SERVER_H
#define __SERVER_H

#include "main.h"


extern uint8_t order_flag;  


void Server_Init(void);
void Server_SendData(uint8_t *data ,uint16_t len);
void Server_SendStr(char *str);
void Server_ReceiceData(uint8_t *data,uint16_t len);
void Server_Data_Analysis(uint8_t data);


#endif /*__SERVER_H*/

