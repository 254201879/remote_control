/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CSN_24L01_Pin GPIO_PIN_10
#define CSN_24L01_GPIO_Port GPIOB
#define IRQ_24L01_Pin GPIO_PIN_11
#define IRQ_24L01_GPIO_Port GPIOB
#define CE_24L01_Pin GPIO_PIN_12
#define CE_24L01_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern uint16_t AD_Data[20]; //存储adc接收数据
extern uint16_t AD_Value[4];// 发送数据 数据格式 0x0a data 0xff
extern uint16_t last_AD_Value[4];
extern uint16_t AD_Value_send[4];
#define ADC_MAX_NUM 4*5 //3组ADC,每组最多存储5个值
extern uint16_t ADC_Values[ADC_MAX_NUM];
extern uint16_t ADC_Convert[4];
extern int ADC_Flag;
extern int ADC_INIT_Flag ;
typedef struct
{
    uint16_t ADC_INIT_Max;//最大值
    uint16_t ADC_INIT_Typ;//typical value of the rocker
    uint16_t ADC_INIT_Min;//minimum value of the rocker
}ADC_INIT;

typedef struct
{
    uint16_t ADC_cal_Max;//MAX-TYP
    uint16_t ADC_cal_Min;//TYP-MIN
}ADC_cal;

extern char rx_data[];
extern int rx_cnt;
extern int flag;
extern uint16_t time;
extern uint16_t data_flag;
extern int speed;
extern int Sprout;
extern int Ball;
extern int Status;
extern unsigned char* tx_data;

#define converting_rate 2 //use 1000 for converting
#define base 1000//basic of the conversion
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
