#ifndef __TASK_H
#define __TASK_H

#include "main.h"


extern uint8_t flag_slave_handle;          //�ӻ����  xxms
extern uint8_t flag_GPS;                  //GPS�źŴ��������ռ����� 20ms


void Task_FlagCheck(void);
void Task_Handle(void);
void Task_Init(void);

#endif /*__TASK_H*/

