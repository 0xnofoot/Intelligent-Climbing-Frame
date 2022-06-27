#ifndef __GPS_H
#define __GPS_H

#include "main.h"

extern uint8_t gps_get;

void GPS_Init(void);
void GPS_Get(void);
void GPS_Data_Analysis(uint8_t data);
void Send_GPS(void);

#endif /*__GPS_H*/

