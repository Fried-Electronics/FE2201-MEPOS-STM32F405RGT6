/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO12_Pin GPIO_PIN_13
#define GPIO12_GPIO_Port GPIOC
#define GPIO13_Pin GPIO_PIN_14
#define GPIO13_GPIO_Port GPIOC
#define GPIO14_Pin GPIO_PIN_15
#define GPIO14_GPIO_Port GPIOC
#define A8_Pin GPIO_PIN_0
#define A8_GPIO_Port GPIOC
#define A7_Pin GPIO_PIN_1
#define A7_GPIO_Port GPIOC
#define A6_Pin GPIO_PIN_2
#define A6_GPIO_Port GPIOC
#define A5_Pin GPIO_PIN_3
#define A5_GPIO_Port GPIOC
#define A1_Pin GPIO_PIN_0
#define A1_GPIO_Port GPIOA
#define A2_Pin GPIO_PIN_1
#define A2_GPIO_Port GPIOA
#define A3_Pin GPIO_PIN_2
#define A3_GPIO_Port GPIOA
#define A4_Pin GPIO_PIN_3
#define A4_GPIO_Port GPIOA
#define A9_Pin GPIO_PIN_4
#define A9_GPIO_Port GPIOA
#define A10_Pin GPIO_PIN_5
#define A10_GPIO_Port GPIOA
#define GPIO15_Pin GPIO_PIN_6
#define GPIO15_GPIO_Port GPIOA
#define GPIO16_Pin GPIO_PIN_7
#define GPIO16_GPIO_Port GPIOA
#define GPIO17__Pin GPIO_PIN_4
#define GPIO17__GPIO_Port GPIOC
#define GPIO18__Pin GPIO_PIN_5
#define GPIO18__GPIO_Port GPIOC
#define GPIO19__Pin GPIO_PIN_0
#define GPIO19__GPIO_Port GPIOB
#define GPIO20__Pin GPIO_PIN_1
#define GPIO20__GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define TX2_Pin GPIO_PIN_10
#define TX2_GPIO_Port GPIOB
#define RX2_Pin GPIO_PIN_11
#define RX2_GPIO_Port GPIOB
#define GPIO21_Pin GPIO_PIN_12
#define GPIO21_GPIO_Port GPIOB
#define GPIO22_Pin GPIO_PIN_13
#define GPIO22_GPIO_Port GPIOB
#define GPIO1__Pin GPIO_PIN_6
#define GPIO1__GPIO_Port GPIOC
#define GPIO2__Pin GPIO_PIN_7
#define GPIO2__GPIO_Port GPIOC
#define GPIO3__Pin GPIO_PIN_8
#define GPIO3__GPIO_Port GPIOC
#define GPIO4__Pin GPIO_PIN_9
#define GPIO4__GPIO_Port GPIOC
#define GPIO5_Pin GPIO_PIN_8
#define GPIO5_GPIO_Port GPIOA
#define TX1_Pin GPIO_PIN_9
#define TX1_GPIO_Port GPIOA
#define RX1_Pin GPIO_PIN_10
#define RX1_GPIO_Port GPIOA
#define GPIO6_Pin GPIO_PIN_11
#define GPIO6_GPIO_Port GPIOA
#define GPIO7_Pin GPIO_PIN_12
#define GPIO7_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define GPIO8_Pin GPIO_PIN_15
#define GPIO8_GPIO_Port GPIOA
#define SCLK1_Pin GPIO_PIN_10
#define SCLK1_GPIO_Port GPIOC
#define MISO1_Pin GPIO_PIN_11
#define MISO1_GPIO_Port GPIOC
#define MOSI1_Pin GPIO_PIN_12
#define MOSI1_GPIO_Port GPIOC
#define CS1_Pin GPIO_PIN_2
#define CS1_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define CS2_Pin GPIO_PIN_4
#define CS2_GPIO_Port GPIOB
#define GPIO9_Pin GPIO_PIN_5
#define GPIO9_GPIO_Port GPIOB
#define GPIO10_Pin GPIO_PIN_6
#define GPIO10_GPIO_Port GPIOB
#define GPIO11_Pin GPIO_PIN_7
#define GPIO11_GPIO_Port GPIOB
#define SCL1_Pin GPIO_PIN_8
#define SCL1_GPIO_Port GPIOB
#define SDA1_Pin GPIO_PIN_9
#define SDA1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
