/**
  ****************************(C)SWJTU_ROBOTCON2022****************************
  * @file       uart_dma.c/h
  * @brief      ������UART_DMA���պ���
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     1-12-2022       ZDYukino        1. done
  *
  @verbatim
  ==============================================================================
  //ע�����HAL���ɴ���ʱ�������DMA_init()��USART_init()֮ǰ������//
  ==============================================================================
  @endverbatim
  ****************************(C)SWJTU_ROBOTCON2023****************************
  **/


#include "main.h"
#include "usart.h"
#include "uart_dma.h"
#include "string.h"
#include "stdio.h"


/*��������Ԥ����*/
uint8_t buffer_receive_1[buffer_receive_length_1];
uint8_t buffer_receive_2[buffer_receive_length_2];
uint8_t buffer_receive_3[buffer_receive_length_3];
uint8_t buffer_receive_4[buffer_receive_length_4];
uint8_t buffer_receive_5[buffer_receive_length_5];
uint8_t buffer_receive_6[buffer_receive_length_6];

/**
  * @brief          UART1-6�жϽ��շ�����
  * @param[in]      ��������
  * @param[in]      ����ֵ��0-128��
  * @retval         none
  */
static void UART1_Receive_Serve(uint8_t *buffer, uint8_t length);
static void UART2_Receive_Serve(uint8_t *buffer, uint8_t length);
static void UART3_Receive_Serve(uint8_t *buffer, uint8_t length);
static void UART4_Receive_Serve(uint8_t *buffer, uint8_t length);
static void UART5_Receive_Serve(uint8_t *buffer, uint8_t length);
static void UART6_Receive_Serve(uint8_t *buffer, uint8_t length);
/**
  * @brief          ��ʼ������DMA����
  * @param[in]      UART�ӿ�
  * @param[in]      ��������->�Ƽ�ʹ���Ѷ�������
  * @param[in]      ����  ��1-128��
  * @retval         none
  */
void UART_DMA_Receive_init(UART_HandleTypeDef *usart, uint8_t *buffer, uint8_t length)
{
  __HAL_UART_ENABLE_IT(usart,UART_IT_IDLE);
  HAL_UART_Receive_DMA(usart,buffer,length);//��DMA����
}
/**
  * @brief          ����DMA�����жϺ���->���롶USER CODE BEGIN USARTX_IRQn 1�� ��
  * @param[in]      UART�ӿ�
  * @param[in]      UART DMA�ӿ�
  * @param[in]      ��������->�Ƽ�ʹ���Ѷ�������
  * @param[in]      ����  ��1-128��
  * @retval         none
  */
void UART_DMA_Receive_IT(UART_HandleTypeDef *usart, DMA_HandleTypeDef *DMA, uint8_t *buffer, uint8_t length)
{
 if(__HAL_UART_GET_FLAG(usart, UART_FLAG_IDLE) == 1)
 {
     __HAL_UART_CLEAR_IDLEFLAG(usart);  
     HAL_UART_DMAStop(usart);
     uint8_t real_length = length - __HAL_DMA_GET_COUNTER(DMA);

     if(usart == &huart1)      UART1_Receive_Serve(buffer, real_length);//ѡ��������
     else if(usart == &huart2) UART2_Receive_Serve(buffer, real_length);//ѡ��������
     //else if(usart == &huart3) UART3_Receive_Serve(buffer, real_length);//ѡ��������
     //else if(usart == &huart4) UART4_Receive_Serve(buffer, real_length);//ѡ��������
     //else if(usart == &huart5) UART5_Receive_Serve(buffer, real_length);//ѡ��������
     //else if(usart == &huart6) UART6_Receive_Serve(buffer, real_length);//ѡ��������
     memset(buffer,0,real_length);
	 HAL_UART_Receive_DMA(usart, buffer, length);//���´�DMA����
 }
}
/**
  * @brief          �����쳣�Ĵ���
  * @param[in]      UART�ӿ�
  * @retval         none
  */
void HAL_UART_ErrorCallback (UART_HandleTypeDef *huart)
{
	uint32_t data;
    __HAL_UNLOCK(huart);
 
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET)
	{
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);      		//�������ж�
		data = huart->Instance->SR;
		data = huart->Instance->DR;
		__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
	}
}
//UART1�жϽ��պ���
static void UART1_Receive_Serve(uint8_t *buffer, uint8_t length)
{





//    ////���Ե���һ�η��Ͷ��ֽ�
//    memcpy(&rx_data,buffer,3);
//    rx_cnt=3;
//ֱ�����Ӵ��������ֽڽ���
    if(rx_cnt!=4)
    {
        memcpy(&rx_data[rx_cnt],buffer,1);     //��������ת��������
        rx_cnt+=1;
    }

    if(rx_data[0]!=0x0a)
    {
        memset(rx_data, 0x00, 3);
        rx_cnt=0;
    }


    if (rx_data[rx_cnt-1] == 0xFF  && rx_data[rx_cnt-4] == 0x0a)  //�жϽ������ݵ�֡ͷ֡β
    {
        data_flag=rx_data[rx_cnt-3];
        time=rx_data[rx_cnt-2];
        memset(rx_data, 0x00, 4);
        rx_cnt=0;
        flag=1;

    }
//    printf("t0.txt=\"111\"\xff\xff\xff");
//////    HAL_UART_Transmit(&huart1,buffer,length,0xff);
//    printf("speed.n0.val=%d\xff\xff\xff",time);
//    printf("speed.n0.val=%d\xff\xff\xff",time);
//    printf("speed.n0.val=%d\xff\xff\xff",time);
//    printf("\r\n");
//    HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//    HAL_Delay(100);
}
//UART2�жϽ��պ���
static void UART2_Receive_Serve(uint8_t *buffer, uint8_t length)
{
    HAL_UART_Transmit(&huart2,buffer,length,0xff);
}
//UART3�жϽ��պ���
static void UART3_Receive_Serve(uint8_t *buffer, uint8_t length)
{
    //HAL_UART_Transmit(&huart3,buffer,length,0xff);
}
//UART4�жϽ��պ���
static void UART4_Receive_Serve(uint8_t *buffer, uint8_t length)
{
    //HAL_UART_Transmit(&huart4,buffer,length,0xff);
}
//UART5�жϽ��պ���
static void UART5_Receive_Serve(uint8_t *buffer, uint8_t length)
{
    //HAL_UART_Transmit(&huart5,buffer,length,0xff);
}
//UART6�жϽ��պ���
static void UART6_Receive_Serve(uint8_t *buffer, uint8_t length)
{

    //HAL_UART_Transmit(&huart6,buffer,length,0xff);
}