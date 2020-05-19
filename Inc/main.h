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
#include "stm32f1xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define S1_PORT_IN1				GPIOB
#define S1_PIN_IN1				GPIO_PIN_0

#define S1_PORT_IN2				GPIOB
#define S1_PIN_IN2				GPIO_PIN_1

#define S1_PORT_PWM				GPIOA
#define S1_PIN_PWM				GPIO_PIN_8

#define S1_PORT_EN1				GPIOB
#define S1_PIN_EN1				GPIO_PIN_3

#define S1_PORT_EN2				GPIOD
#define S1_PIN_EN2				GPIO_PIN_2




#define S2_PORT_IN1				GPIOB
#define S2_PIN_IN1				GPIO_PIN_2

#define S2_PORT_IN2				GPIOB
#define S2_PIN_IN2				GPIO_PIN_10

#define S2_PORT_PWM				GPIOA
#define S2_PIN_PWM				GPIO_PIN_9

#define S2_PORT_EN1				GPIOB
#define S2_PIN_EN1				GPIO_PIN_5

#define S2_PORT_EN2				GPIOB
#define S2_PIN_EN2				GPIO_PIN_4




#define S3_PORT_IN1				GPIOB
#define S3_PIN_IN1				GPIO_PIN_11

#define S3_PORT_IN2				GPIOC
#define S3_PIN_IN2				GPIO_PIN_5

#define S3_PORT_PWM				GPIOA
#define S3_PIN_PWM				GPIO_PIN_10

#define S3_PORT_EN1				GPIOB
#define S3_PIN_EN1				GPIO_PIN_7

#define S3_PORT_EN2				GPIOB
#define S3_PIN_EN2				GPIO_PIN_6
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
