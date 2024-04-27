/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "data.h"
#include "adc_analys.h"
#include "UART_DMA.h"
#include "string.h"
#include "data.h"
#include "NRF24L01.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint16_t AD_Value[4];// 发送数据 数据格式 0x0a data 0xff
uint16_t last_AD_Value[4];
int ADC_Flag=0;
//uint16_t ADC_INIT_Value[4]={2171,2075,2258,2066};//上电初始平均值 提供为参考数值 channel1 5 6 7
uint16_t ADC_Convert[4]={0}; //value after convertion
uint16_t AD_Data[20]; //存储adc接收数据
uint16_t ADC_Value;  //ADC值
uint16_t ADC_Values[ADC_MAX_NUM]={0};
uint16_t AD_Value_send[4]= {0};
ADC_INIT Channel_init[4]={{3634,2171,489},
                     {3520,2075,503},
                     {3679,2258,535},
                     {3649,2066,492}};
//ADC_INIT Channel1_init={3634,2171,489};
//ADC_INIT Channel5_init={3520,2075,503};
//ADC_INIT Channel6_init={3679,2258,535};
//ADC_INIT Channel7_init={3649,2066,492};
ADC_cal Channel_cal[4]={0};
//ADC_cal Channel1_cal={0,0};
//ADC_cal Channel5_cal={0,0};
//ADC_cal Channel6_cal={0,0};
//ADC_cal Channel7_cal={0,0};
int ADC_INIT_Flag = 0;

int rx_cnt=0;
char rx_data[]={00,00,00,00};
extern int flag=0;
extern uint16_t time=0;
extern uint16_t data_flag=0xff;
extern unsigned char* tx_data={0};
int a = 0;
int speed = 0; // store the speed scope
int Sprout = 0; //store the sprout number
int Ball = 0; //store the sprout number
int Status = 0; // store the status

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
unsigned char tx_buf[8] = "sendErr";
//unsigned char tmp_buf2[32] = {0};
unsigned char i;
extern const unsigned char INIT_ADDR0[5];
extern const unsigned char INIT_ADDR1[5];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
    HAL_ADCEx_Calibration_Start(&hadc1);    //AD校准
    //HAL_ADC_Start_DMA(&hadc1,(uint32_t*)AD_Data,20);
    UART_DMA_Receive_init(&huart1,buffer_receive_1,buffer_receive_length_1);
    UART_DMA_Receive_init(&huart2,buffer_receive_2,buffer_receive_length_2);
    HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Values,ADC_MAX_NUM);

    memset(rx_data, 0x00, 4);

    NRF24L01_Init();
    char init[7]="init_ok";
    HAL_UART_Transmit(&huart2,init,7,1000);
    int temp = 4;
    while(NRF24L01_Check()&&(temp--));
    TX_Mode_ack_data();

    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,SET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,SET);
    flag=0;
    ADC_INIT_Flag=1;
    Typ_init(Channel_init);

    HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


      HAL_Delay(5);

//      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,SET);
//      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,SET);
//      ADC_Flag=0;
//      AD_Value_init();

      loop_init();
      if(flag==0){
          HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,RESET);

          memset(rx_data, 0x00, 4);
          data_flag=0xf0;
          flag=0;
          ADC_Flag=0;

      }
      else if (flag==1){
          if (data_flag==0x01)
          {

              speed=time;
              printf("speed.n0.val=%d\xff\xff\xff",speed);
              printf("speed.n0.val=%d\xff\xff\xff",speed);
              printf("speed.n0.val=%d\xff\xff\xff",speed);
              printf("\r\n");
              HAL_Delay(5);
          }
          if (data_flag==0x02)
          {

              Sprout=time;
              printf("grab.n0.val=%d\xff\xff\xff",Sprout);
              printf("grab.n0.val=%d\xff\xff\xff",Sprout);
              printf("grab.n0.val=%d\xff\xff\xff",Sprout);
              printf("\r\n");
              HAL_Delay(5);

          }
          if (data_flag==0x03)
          {

              Sprout=time;
              printf("put_prout.n0.val=%d\xff\xff\xff",Sprout);
              printf("put_prout.n0.val=%d\xff\xff\xff",Sprout);
              printf("put_prout"
                     ".n0.val=%d\xff\xff\xff",Sprout);
              printf("\r\n");
              HAL_Delay(5);
//          Sprout=0;

          }

          if (data_flag==0x04)
          {

              Ball=time;
              printf("ball.n0.val=%d\xff\xff\xff",Ball);
              printf("ball.n0.val=%d\xff\xff\xff",Ball);
              printf("ball.n0.val=%d\xff\xff\xff",Ball);
              printf("\r\n");
              HAL_Delay(5);
//          Ball=0;
//          STATE=GetBall;
          }
          if (data_flag==0xf0)
          {

              Status=time;
              if (Status == 0x01|| Status == 0x02){
                  printf("page analog\xff\xff\xff");
                  printf("page analog\xff\xff\xff");
                  printf("page analog\xff\xff\xff");
                  printf("\r\n");
              }

              HAL_Delay(5);
//          Ball=0;
//          STATE=GetBall;
          }
          flag=0;

      }

      Typ_init(Channel_init);

      ADC_Average();
      for (int i = 0; i < 4; i++)
      {
          AD_Value[i]=rc_band_limit(AD_Value[i],Channel_init[i].ADC_INIT_Typ);
      }

        ADC_Converting(Channel_init,ADC_Convert);

      if(data_flag==0x00||ADC_Flag==1)
      {
          data_flag = 0x00;
          printf("analog.n4.val=%d\xff\xff\xff",AD_Value[0]);
          printf("analog.n5.val=%d\xff\xff\xff",AD_Value[1]);
          printf("analog.n6.val=%d\xff\xff\xff",AD_Value[2]);
          printf("analog.n7.val=%d\xff\xff\xff",AD_Value[3]);
          printf("analog.n4.val=%d\xff\xff\xff",AD_Value[0]);
          printf("analog.n5.val=%d\xff\xff\xff",AD_Value[1]);
          printf("analog.n6.val=%d\xff\xff\xff",AD_Value[2]);
          printf("analog.n7.val=%d\xff\xff\xff",AD_Value[3]);
          printf("analog.n8.val=%d\xff\xff\xff",ADC_Convert[0]);
          printf("analog.n9.val=%d\xff\xff\xff",ADC_Convert[1]);
          printf("analog.n10.val=%d\xff\xff\xff",ADC_Convert[2]);
          printf("analog.n11.val=%d\xff\xff\xff",ADC_Convert[3]);
          printf("analog.n8.val=%d\xff\xff\xff",ADC_Convert[0]);
          printf("analog.n9.val=%d\xff\xff\xff",ADC_Convert[1]);
          printf("analog.n10.val=%d\xff\xff\xff",ADC_Convert[2]);
          printf("analog.n11.val=%d\xff\xff\xff",ADC_Convert[3]);
          printf("\r\n");
      }


      printf("\r\n");
      KEY_Function();




        data_format_nrf(data_flag);
//        data_format(data_flag);

















//      printf("\r\n");





  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
