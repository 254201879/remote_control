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
void loop_init();//ѭ����ʼ��ʼ��
void standby_init();//����״̬��ʼ��

/**GPIO FOR KEY**/
#define Key1_PORT GPIOA //ȡ��
#define Key1_PIN GPIO_PIN_11 //ȡ��
#define Key2_PORT GPIOA //����
#define Key2_PIN GPIO_PIN_12 //����
#define Key3_PORT GPIOA //ȡ��
#define Key3_PIN GPIO_PIN_15
#define Key4_PORT GPIOB //����
#define Key4_PIN GPIO_PIN_3
#define Key5_PORT GPIOB //ȡ��
#define Key5_PIN GPIO_PIN_6 //ȡ��
#define Key6_PORT GPIOB //����
#define Key6_PIN GPIO_PIN_7 //����
#define Key7_PORT GPIOB //ȡ��
#define Key7_PIN GPIO_PIN_8
#define Key8_PORT GPIOB //����
#define Key8_PIN GPIO_PIN_9
#define Key9_PORT GPIOA //ȡ��
#define Key9_PIN GPIO_PIN_0 //ȡ��

#endif //PROJECT_ADC_ANALYS_H
