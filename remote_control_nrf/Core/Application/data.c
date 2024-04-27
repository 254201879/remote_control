//
// Created by 25420 on 2024/3/8.
//
#include <stdint-gcc.h>
#include "main.h"
#include "data.h"
#include "usart.h"
#include "NRF24L01.h"
#include "adc_analys.h"


uint16_t AM_ADC_Value[4]={0};
/**
 * @brief    data_format format the data in 8 bits
 * @note     None
 * @paramin  dataflag
 * @paramout None
 * @retval   None
 */

char* data_format(uint16_t data_flag)
{
    unsigned char data_value[8]={0};
    data_value[0]=0x0a;
    data_value[7]=0xff;
    data_value[6]=flag;
//    HAL_UART_Transmit(&huart1,data_value,3,0xff);
//    printf("senddata\r\n");
//    if(data_flag == 0x00) {
//
//        //send the data of ADC
//        data_value[1] = 0x00;
//        data_value[2] = ADC_Convert[0];
//        data_value[3] = ADC_Convert[1];
//        data_value[4] = ADC_Convert[2];
//        data_value[5] = ADC_Convert[3];
//        data_value[6] = 0;
//    }
    if(data_flag == 0x00) {

        //send the data of ADC
        data_value[1] = 0x00;
        data_value[2] = AD_Value_send[2]>>8;
        data_value[3] = AD_Value_send[2];
        data_value[4] = AD_Value_send[3]>>8;
        data_value[5] = AD_Value_send[3];
        data_value[6] = AD_Value_send[1]/10;
    }
    else if(data_flag == 0x01) {
        //send the speed scope
        data_value[1] = 0x01;
        data_value[2] = speed;
        data_value[3] = 0;
        data_value[4] = 0;
        data_value[5] = 0;
        data_value[6] = 0;
    }
    else if(data_flag == 0x02) {
        //取苗

        data_value[1] = 0x02;
        data_value[2] = Sprout;
        data_value[3] = 0;
        data_value[4] = 0;
        data_value[5] = 0;
        data_value[6] = 0;
    }
    else if(data_flag == 0x03) {
        //放苗

        data_value[1] = 0x03;
        data_value[2] = Sprout;
        data_value[3] = 0;
        data_value[4] = 0;
        data_value[5] = 0;
        data_value[6] = 0;
    }
    else if(data_flag == 0x04){
        //取球
        data_value[1]=0x04;
        data_value[2]=Ball;
        data_value[3]=0;
        data_value[4]=0;
        data_value[5]=0;
        data_value[6]=0;

    }
    else if(data_flag == 0xA6){
        data_value[1]=data_flag;
        data_value[2]=launch;
        data_value[3]=0;
        data_value[4]=0;
        data_value[5]=0;
        data_value[6]=0;

    }
    else if(data_flag == 0xf0){
        data_value[1]=0xf0;
        data_value[2]=Status;
        data_value[3]=0;
        data_value[4]=0;
        data_value[5]=0;
        data_value[6]=0;

    }
    data_flag = 0xff;
    launch = 0x00;
//    Status = 0x00;

    HAL_UART_Transmit(&huart2,(char*)data_value,8,0xff);
    return data_value;
}

void data_format_nrf(uint16_t data_flag){
    unsigned char data_value[8]={0};
    data_value[0]=0x0a;
    data_value[7]=0xff;
//    HAL_UART_Transmit(&huart1,data_value,3,0xff);
//    printf("senddata\r\n");
    if(data_flag == 0x00) {

        //send the data of ADC
        data_value[1] = 0x00;
        data_value[2] = AD_Value_send[2]>>8;
        data_value[3] = AD_Value_send[2];
        data_value[4] = AD_Value_send[3]>>8;
        data_value[5] = AD_Value_send[3];
        data_value[6] = AD_Value_send[1]/10;
    }
    else if(data_flag == 0x01) {
        //send the speed
        data_value[1] = 0x01;
        data_value[2] = speed;
        data_value[3] = 0;
        data_value[4] = 0;
        data_value[5] = 0;
        data_value[6] = 0;
    }
    else if(data_flag == 0x02) {
        //取苗

        data_value[1] = 0x02;
        data_value[2] = Sprout;
        data_value[3] = 0;
        data_value[4] = 0;
        data_value[5] = 0;
        data_value[6] = 0;
    }
    else if(data_flag == 0x03) {
        //放苗

        data_value[1] = 0x03;
        data_value[2] = Sprout;
        data_value[3] = 0;
        data_value[4] = 0;
        data_value[5] = 0;
        data_value[6] = 0;
    }
    else if(data_flag == 0x04){
        //取球
        data_value[1]=0x04;
        data_value[2]=Ball;
        data_value[3]=0;
        data_value[4]=0;
        data_value[5]=0;
        data_value[6]=0;

    }
    else if(data_flag == 0xA6){
        data_value[1]=data_flag;
        data_value[2]=launch;
        data_value[3]=0;
        data_value[4]=0;
        data_value[5]=0;
        data_value[6]=0;

    }
    else if(data_flag == 0xf0){
        data_value[1]=0xf0;
        data_value[2]=Status;
        data_value[3]=0;
        data_value[4]=0;
        data_value[5]=0;
        data_value[6]=0;

    }
    if(NRF24L01_TxPacket_ack_data(INIT_ADDR1, data_value, 8) == 0x20)	//????????
    {
        printf("send data OK!\r\n");
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//        HAL_UART_Transmit(&huart2,rxbuf,8,1000);
    }
//    else
//    {
//        HAL_UART_Transmit(&huart2,data_value,8,0xff);
//    }
    data_flag=0xff;
    launch=0x00;

}

