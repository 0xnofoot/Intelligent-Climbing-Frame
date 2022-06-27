/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Ser_RST_Pin GPIO_PIN_4
#define Ser_RST_GPIO_Port GPIOE
#define Ser_IO_RT_Pin GPIO_PIN_5
#define Ser_IO_RT_GPIO_Port GPIOE
#define GPS_PPS_Pin GPIO_PIN_7
#define GPS_PPS_GPIO_Port GPIOE
#define Ser_STAT_Pin GPIO_PIN_11
#define Ser_STAT_GPIO_Port GPIOE
#define Ser_LIKA_Pin GPIO_PIN_12
#define Ser_LIKA_GPIO_Port GPIOE
#define Ser_LIKB_Pin GPIO_PIN_13
#define Ser_LIKB_GPIO_Port GPIOE
#define Ser_LIKC_Pin GPIO_PIN_14
#define Ser_LIKC_GPIO_Port GPIOE
#define Ser_LIKD_Pin GPIO_PIN_15
#define Ser_LIKD_GPIO_Port GPIOE
#define Relay2_Pin GPIO_PIN_12
#define Relay2_GPIO_Port GPIOB
#define Relay1_Pin GPIO_PIN_13
#define Relay1_GPIO_Port GPIOB
#define AUX_Pin GPIO_PIN_7
#define AUX_GPIO_Port GPIOB
#define LORA_M0_Pin GPIO_PIN_8
#define LORA_M0_GPIO_Port GPIOB
#define LORA_M1_Pin GPIO_PIN_9
#define LORA_M1_GPIO_Port GPIOB
#define RS485_RE_Pin GPIO_PIN_0
#define RS485_RE_GPIO_Port GPIOE
#define RS485_DE_Pin GPIO_PIN_1
#define RS485_DE_GPIO_Port GPIOE

#define Rise_Check_Pin GPIO_PIN_5
#define Rise_Check_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
