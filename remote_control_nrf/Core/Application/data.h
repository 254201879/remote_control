//
// Created by 25420 on 2024/3/8.
//

#ifndef REMOTE_CONTROL_NRF_DATA_H
#define REMOTE_CONTROL_NRF_DATA_H
#include "main.h"

extern uint16_t AM_ADC_Value[4];

char* data_format(uint16_t data_flag);
void data_format_nrf(uint16_t data_flag);

#endif //REMOTE_CONTROL_NRF_DATA_H
