//
// Created by 25420 on 2024/3/16.
//

#include <stdint-gcc.h>
#include <string.h>
#include "adc_analys.h"
#include "usart.h"

char launch=0x00;

/**选择按键**/
#define Key1
#define Key2
#define Key3
#define Key4
#define Key5
#define Key6
#define Key7
#define Key8
#define Key9
#define Key10



/**
 * @brief    死区消除函数
 * @note     None
 * @paramin  input 实际值 compare 比较值
 * @paramout None
 * @retval   None
 */
int rc_band_limit(uint16_t input,uint16_t compare)
{
    if(((input>compare)&&((input-compare)<deadline))||((input<compare)&&((compare-input)<deadline))||(input==compare))
    {
        return compare;

    }
    else
        data_flag=0x00;
        return input;
}

/**
 * @brief    init for AD_Value
 * @note     None
 * @paramin  None
 * @paramout None
 * @retval   None
 */

void AD_Value_init(void)
{
    AD_Value[0]=0.0;
    AD_Value[1]=0.0;
    AD_Value[2]=0.0;
    AD_Value[3]=0.0;
}

/**
 * @brief    press key to init the typ
 * @note     None
 * @paramin  ADC_INIT Channel_init[]
 * @paramout Channel_init after initialization
 * @retval   None
 */

void Typ_init(ADC_INIT Channel_init[])
{
    if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)==RESET||ADC_INIT_Flag==1)
    {
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        for(int i=0;i<4;i++)
        {
            Channel_init[i].ADC_INIT_Typ=0;
        }
        for(int i=0;i<ADC_MAX_NUM;)
        {
            Channel_init[0].ADC_INIT_Typ+=ADC_Values[i++];
            Channel_init[1].ADC_INIT_Typ+=ADC_Values[i++];
            Channel_init[2].ADC_INIT_Typ+=ADC_Values[i++];
            Channel_init[3].ADC_INIT_Typ+=ADC_Values[i++];
        }
        for (int i=0 ;i < 4; i++ )
        {
            Channel_init[i].ADC_INIT_Typ= Channel_init[i].ADC_INIT_Typ/(ADC_MAX_NUM/4);
        }

    }
    printf("analog.n0.val=%d\xff\xff\xff",Channel_init[0].ADC_INIT_Typ);
    printf("analog.n1.val=%d\xff\xff\xff",Channel_init[1].ADC_INIT_Typ);
    printf("analog.n2.val=%d\xff\xff\xff",Channel_init[2].ADC_INIT_Typ);
    printf("analog.n3.val=%d\xff\xff\xff",Channel_init[3].ADC_INIT_Typ);
    printf("analog.n0.val=%d\xff\xff\xff",Channel_init[0].ADC_INIT_Typ);
    printf("analog.n1.val=%d\xff\xff\xff",Channel_init[1].ADC_INIT_Typ);
    printf("analog.n2.val=%d\xff\xff\xff",Channel_init[2].ADC_INIT_Typ);
    printf("analog.n3.val=%d\xff\xff\xff",Channel_init[3].ADC_INIT_Typ);
    printf("\r\n");
    if (ADC_INIT_Flag==1){
        ADC_INIT_Flag=0;
    }
}

/**
 * @brief    get average value
 * @note     None
 * @paramin  None
 * @paramout None
 * @retval   None
 */

void ADC_Average(void)
{
    for (int i=0 ;i < ADC_MAX_NUM; )
    {

        AD_Value[0]+= ADC_Values[i++];
        AD_Value[1]+= ADC_Values[i++];
        AD_Value[2]+= ADC_Values[i++];
        AD_Value[3]+= ADC_Values[i++];

    }
    for (int i=0 ;i < 4; i++ )
    {

        AD_Value[i]= AD_Value[i]/(ADC_MAX_NUM/4);


    }
}

/**
 * @brief    converting ADC value
 * @note     None
 * @paramin  Channel_init
 * @paramout conversion of the value
 * @retval   None
 */

void ADC_Converting(ADC_INIT Channel_init[],uint16_t *conversion)
{
    for(int i=0;i<4;i++)
    {
        uint16_t temp=0;
        last_AD_Value[i]=AD_Value_send[i];
        if(AD_Value[i]>Channel_init[i].ADC_INIT_Typ)
        {
            temp=AD_Value[i]-Channel_init[i].ADC_INIT_Typ;
//              ADC_Convert[i]=(temp/Channel_cal[i].ADC_cal_Max*1000)+1000;
            conversion[i]=temp/converting_rate+1000;
            AD_Value_send[i]=conversion[i];
        }
        else
        {
            temp=Channel_init[i].ADC_INIT_Typ-AD_Value[i];
//              ADC_Convert[i]=1000-(temp/Channel_cal[i].ADC_cal_Min*1000);
            conversion[i]=1000-temp/converting_rate;
            AD_Value_send[i]=conversion[i];
        }
//          printf("temp %d :%d\n",i,temp);
        if(i<=3&&last_AD_Value[i]!=AD_Value_send[i]){
            ADC_Flag=1;
        }

    }
}

/**
 * @brief    press key to achieve the action
 * @note     None
 * @paramin  None
 * @paramout None
 * @retval   None
 */
void KEY_Function(){
    /**************Key1************/
    if(HAL_GPIO_ReadPin(Key1_PORT,Key1_PIN)==RESET){
        //取苗
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x10;
        HAL_Delay(500);
    }
    if(HAL_GPIO_ReadPin(Key2_PORT,Key2_PIN)==RESET){
        //放苗
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x11;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key3_PORT,Key3_PIN)==RESET){
        //取球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x20;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key4_PORT,Key4_PIN)==RESET){
        //放球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x21;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key5_PORT,Key5_PIN)==RESET){
        //放球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x30;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key6_PORT,Key6_PIN)==RESET){
        //放球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x31;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key7_PORT,Key7_PIN)==RESET){
        //放球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x40;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key8_PORT,Key8_PIN)==RESET){
        //放球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x41;
        HAL_Delay(500);

    }
    else if(HAL_GPIO_ReadPin(Key9_PORT,Key9_PIN)==SET){
        //放球
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
        data_flag=0xA6;
        launch=0x50;
        HAL_Delay(500);

    }




}

/**
 * @brief    init when starting the while loop
 * @note     None
 * @paramin  None
 * @paramout None
 * @retval   None
 */
 void loop_init(){
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,SET);
    ADC_Flag=0; //set the ADC flag to 1
    AD_Value_init(); //set the ADC value to zero
 }

 /**
  * @brief    init when flag==0(standby)
  * @note     None
  * @paramin  None
  * @paramout None
  * @retval   None
  */
  void standby_init(){
     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,RESET);
     memset(rx_data, 0x00, 4);
     data_flag=0xf0;
     flag=0;
     ADC_Flag=0;
  }

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//    if (GPIO_Pin==GPIO_PIN_11){
//        if (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)==0){
//            if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)==RESET){
//                //取苗
//                HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_4);
//                data_flag=0xA6;
//                launch=0x10;
//                HAL_Delay(500);
//            }
//
//        }
//    }
//}