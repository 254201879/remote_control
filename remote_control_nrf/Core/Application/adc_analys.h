/**
  ******************************************************************************
  * @file           : adc_analys.h
  * @author         : Wac
  * @brief          : None
  * @attention      : None
  * @date           : 2024/3/17
  ******************************************************************************
  */


#ifndef PROJECT_ADC_ANALYS_H
#define PROJECT_ADC_ANALYS_H

#include "main.h"

#define deadline 10
#define check 1000
extern char launch;

int rc_band_limit(uint16_t input,uint16_t compare);
void AD_Value_init(void);
void Typ_init(ADC_INIT Channel_init[]);
void ADC_Average(void);
void ADC_Converting(ADC_INIT Channel_init[],uint16_t *conversion);
void KEY_Function(void);
void check_value(uint16_t input);
void loop_init();//循环开始初始化
void standby_init();//待机状态初始化

/**GPIO FOR KEY**/
#define Key1_PORT GPIOA //取苗
#define Key1_PIN GPIO_PIN_11 //取苗
#define Key2_PORT GPIOA //放苗
#define Key2_PIN GPIO_PIN_12 //放苗
#define Key3_PORT GPIOA //取球
#define Key3_PIN GPIO_PIN_15
#define Key4_PORT GPIOB //放球
#define Key4_PIN GPIO_PIN_3
#define Key5_PORT GPIOB //取苗
#define Key5_PIN GPIO_PIN_6 //取苗
#define Key6_PORT GPIOB //放苗
#define Key6_PIN GPIO_PIN_7 //放苗
#define Key7_PORT GPIOB //取球
#define Key7_PIN GPIO_PIN_8
#define Key8_PORT GPIOB //放球
#define Key8_PIN GPIO_PIN_9
#define Key9_PORT GPIOA //取苗
#define Key9_PIN GPIO_PIN_0 //取苗

#endif //PROJECT_ADC_ANALYS_H
