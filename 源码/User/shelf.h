#ifndef __SHELF_H
#define __SHELF_H

#include "main.h"

extern float shelf_buffer[40];

void RS485_Init(void);
void RS485_Config_Send(void);
void RS485_Config_Receive(void);
void RS485_Data_Analysis(uint8_t data[12],uint8_t id);
void RS485_SendData(uint8_t *data ,uint16_t len);
void Polled_SendData(uint8_t address);
void Shelf_Polled(void);
void Send_Shelf(void);

#endif /*__SHELF_H*/

