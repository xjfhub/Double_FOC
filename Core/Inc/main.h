/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define SCL_Pin GPIO_PIN_13
#define SCL_GPIO_Port GPIOC
#define ENC_A_Pin GPIO_PIN_14
#define ENC_A_GPIO_Port GPIOC
#define ENC_B_Pin GPIO_PIN_15
#define ENC_B_GPIO_Port GPIOC
#define CS2_Pin GPIO_PIN_4
#define CS2_GPIO_Port GPIOA
#define LED_RZ_Pin GPIO_PIN_4
#define LED_RZ_GPIO_Port GPIOC
#define CS1_Pin GPIO_PIN_0
#define CS1_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_2
#define DC_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_10
#define SDA_GPIO_Port GPIOB
#define KEY_EN_Pin GPIO_PIN_6
#define KEY_EN_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
extern int32_t g_adc_buff[7];  //adc????{IA1,IB1,IC1,IA2,IB2,IC2,VBUS}
extern float ano_data[20];
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
