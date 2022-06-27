#ifndef __CALLBACK_H
#define __CALLBACK_H

#include "main.h"

extern uint8_t gps_get_flag;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /*__CALLBACK_H*/

