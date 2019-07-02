
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"
#include "fatfs.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "GUI.h"
//hardware
#include "STMPE610.h"
#include "SSD1963.h"
#include "VS1053.h"
#include "ADXL345.h"
//software
#include "MP3.h"
#include "loadFromSD.h"
//windows
#include "LEDDLG.h"
#include "BUZZERDLG.h"
#include "INFODLG.h"
#include "MP3DLG.h"
#include "LIGHTDLG.h"
#include "MENUDLG.h"
#include "TEMPDLG.h"
#include "ACCELDLG.h"
#include "TIMEDLG.h"
#include "FILESDLG.h"
#include "SETTIMEDLG.h"
#include "SETDATEDLG.h"
#include "USBDLG.h"
#include "QWERTYDLG.h"


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc3;

CRC_HandleTypeDef hcrc;

I2C_HandleTypeDef hi2c1;

RNG_HandleTypeDef hrng;

RTC_HandleTypeDef hrtc;

SD_HandleTypeDef hsd1;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define RED 	0xF800
#define GREEN 	0x07E0
#define BLUE 	0x001F

// main menu items
#define MENU 	0x00
#define LED 	0x10
#define TEMP 	0x20
#define LIGHT 	0x30
#define ACCEL 	0x40
#define TIME 	0x50
#define TOUCH 	0x60
#define SLIDE 	0x70
#define BUZZER 	0x80
#define MP3 	0x90
#define USB 	0xA0
#define FILES 	0xB0
#define INFO 	0xC0
#define SETTIME 0xD0
#define SETDATE 0xE0

//variable
uint8_t state=0;
int keyPressed=0;
int8_t val=0;
uint16_t c=0, i=0, j=0, k=0;
uint16_t x_accel=0;
uint16_t y_accel=0;
uint16_t z_accel=0;
WM_HWIN hWin, hWin1;
char dataADC[20];
char dataLOG[20];
uint32_t ADC_BUF[2], ADC_Result, ad1, ad2;
float pom=0;
int scroll_state;
int volume=0;
uint8_t slider_RED=0, slider_GREEN=0, slider_BLUE=0, graph=0, backlight=0xC0, logg=0, SD_present=0;
uint16_t counter_LED=0, GUI_timer=0;
//uint8_t img_line[480*8*3]={0};
FATFS myFAT;
FIL myFile, AccelFile;
FRESULT res;

uint8_t myData[]="Hello world!!!\n";

UINT byteCount;

extern uint8_t UserRxBufferFS[256];
extern char message[256];
extern unsigned int cursor;

int RcalX[3]={24, 240, 456};
int RcalY[3]={14, 258, 136};
int ScalX[3]={336, 2039, 3742};
int ScalY[3]={510, 3640, 2077};

GRAPH_DATA_Handle hData;
GRAPH_DATA_Handle hData1;
GRAPH_DATA_Handle hData2;
RTC_TimeTypeDef htime;
RTC_DateTypeDef hdate;

GUI_PID_STATE hstate;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_ADC3_Init(void);
static void MX_CRC_Init(void);
static void MX_RNG_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                

/* USER CODE BEGIN PFP */
void Menu_State_Exec(void);
/* Private function prototypes -----------------------------------------------*/
extern volatile GUI_TIMER_TIME OS_TimeMS;
void HAL_SYSTICK_Callback(void)
{
	OS_TimeMS++;
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache-------------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache-------------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();
  MX_ADC3_Init();
  MX_CRC_Init();
  MX_RNG_Init();
  MX_RTC_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  Init_LCD_GPIO();
  Init_TOUCH_GPIO(hi2c1);
  Init_ACCEL_GPIO(hi2c1);
  Init_MP3_GPIO(hspi2);

  HAL_Delay(1000);
  ADXL345_Init();
  VS1053_Init();

  WM_SetCreateFlags(WM_CF_MEMDEV); // eliminise flickering
  GUI_Init();
  GUI_Clear();

  SSD1963_SetScrollArea(0, 272, 544);
  SSD1963_SetScrollStart(0);
  GUI_Clear();

  FATFS_UnLinkDriver(SDPath);

  hWin=CreateMENU();
  SSD1963_SetScrollStart(0);

  HAL_ADC_Start_DMA(&hadc3,(uint32_t*)ADC_BUF, 2);
  HAL_ADC_Start_IT(&hadc3);

  HAL_TIM_Base_Start_IT(&htim3);

  HAL_Delay(100);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_ADC_Start_IT(&hadc3);
	  GUI_Delay(1);
	  STMPE610_read_xyz();
	  GUI_TOUCH_Exec();
	  keyPressed=GUI_GetKey();
	  Menu_State_Exec();
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_SDMMC1|RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC3 init function */
static void MX_ADC3_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 2;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* CRC init function */
static void MX_CRC_Init(void)
{

  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x20303E5D;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Analogue filter 
    */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Digital filter 
    */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RNG init function */
static void MX_RNG_Init(void)
{

  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initialize RTC and set the Time and Date 
    */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JULY;
  sDate.Date = 7;
  sDate.Year = 19;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SDMMC1 init function */
static void MX_SDMMC1_SD_Init(void)
{

  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;

}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{

  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 27;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 200;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM4 init function */
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 108;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 200;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim4);

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD10 PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD9 PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PG15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance==ADC3)
	{
		ad1=ADC_BUF[0];
		ad2=ADC_BUF[1];
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance==TIM3)
	{
		counter_LED++;
		if(counter_LED==255)
		{
			counter_LED=0;

			if(counter_LED==slider_GREEN)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
			else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
			if(counter_LED==slider_BLUE)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
			if(counter_LED==slider_RED)HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET);
			else HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_SET);
		}


		if(counter_LED==slider_GREEN)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
		if(counter_LED==slider_BLUE)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		if(counter_LED==slider_RED)HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET);
	}

}

void Menu_State_Exec(void)
{
	  switch (state)
	  {
	  	  case MENU:
	  		  switch(keyPressed)
	  		  {
	  		  	  case (GUI_ID_USER + LED): // LED Control
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							state=LED;
	  							hWin=CreateLED();
	  							GUI_Delay(200);
	  							break;
	  		  	  case (GUI_ID_USER + TEMP): // Temperature
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							state=TEMP;
	  							hWin=CreateTEMP();
	  							GUI_Delay(200);
	  							break;
	  		  	  case (GUI_ID_USER + LIGHT): // Light
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							state=LIGHT;
	  							hWin=CreateLIGHT();
	  							SLIDER_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x07 + LIGHT)), backlight);
	  							GUI_Delay(200);
	  							break;
	  		  	  case (GUI_ID_USER + ACCEL): // Accelerometer
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							state=ACCEL;
	  							hWin=CreateACCEL();
	  							hData=GRAPH_DATA_YT_Create(GUI_BLUE, 440, 0, 0);
	  							GRAPH_AttachData(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x01+ACCEL)), hData);
	  							hData1=GRAPH_DATA_YT_Create(GUI_DARKGREEN , 440, 0, 0);
	  							GRAPH_AttachData(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x01+ACCEL)), hData1);
	  							hData2=GRAPH_DATA_YT_Create(GUI_RED , 440, 0, 0);
	  							GRAPH_AttachData(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x01+ACCEL)), hData2);
	  							if(SD_present)CHECKBOX_SetTextColor (WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), GUI_BLACK);
	  							else  CHECKBOX_SetTextColor (WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), GUI_RED);
	  							graph=1;
	  							GUI_Delay(200);
	  							break;
	  		  	  case (GUI_ID_USER + TIME): // Time/Date
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							state=TIME;
	  							hWin=CreateTIME();
	  							GUI_Delay(200);
	  							break;
	  		  	  case (GUI_ID_USER + TOUCH): // Touch calibration
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=TOUCH;
	  							break;
	  		  	  case (GUI_ID_USER + SLIDE): // Image SlideShow
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=SLIDE;
	  							break;
	  		  	 case (GUI_ID_USER + MP3)://MP3
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=MP3;
	  							hWin=CreateMP3();
	  							MP3_MountSD();
	  							PopulateMP3List(hWin);
	  							MP3_SetState(STOP);
	  							MP3_Exec();
	  							GUI_Delay(200);
	  				  	  	  	break;
	  		  	 case (GUI_ID_USER + BUZZER)://Buzzer
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=BUZZER;
	  							hWin=CreateBUZZER();
	  							GUI_Delay(200);
	  							break;
	  		  	 case (GUI_ID_USER + USB)://USB
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=USB;
	  							hWin=CreateUSB();
	  							hWin1=CreateQWERTY();
	  							GUI_Delay(200);
	  							break;
	  		  	 case (GUI_ID_USER + FILES)://Files
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=FILES;
	  							hWin=CreateFILES();
	  							GUI_Delay(200);
	  							break;
	  		  	 case (GUI_ID_USER + INFO): //Info
	  							scroll_state=SCROLLBAR_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)));
	  							WM_DeleteWindow(hWin);
	  							GUI_Clear();
	  							state=INFO;
	  							hWin=CreateINFO();
	  							GUI_Delay(200);
	  							break;
	  		  }
	  		  break;
	  	  case LED:
	  		  slider_RED=SLIDER_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x05 + LED)));
	  		  sprintf((char*)dataADC, "%d", slider_RED);
	  		  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x06 + LED)), dataADC);

	  		  slider_GREEN=SLIDER_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x03 + LED)));
	  		  sprintf((char*)dataADC, "%d", slider_GREEN);
	  		  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + LED)), dataADC);

	  		  slider_BLUE=SLIDER_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x01 + LED)));
	  		  sprintf((char*)dataADC, "%d", slider_BLUE);
	  		  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x02 + LED)), dataADC);

	  		  if(keyPressed==(GUI_ID_USER + 0x0B + LED)) // close btn
	  		  {
					WM_DeleteWindow(hWin);
					state=MENU;
					hWin=CreateMENU();
					SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
					GUI_Delay(200);
	  		  }
	  		  break;
	  	  case TEMP:
	  		  pom=(float)ad1;
	  		  pom=100.0*((pom)/(2048)-0.5);
	  		  sprintf((char*)dataADC, "%d", (uint16_t)pom);
	  		  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x05 + TEMP)), dataADC);
	  		  if(keyPressed==(GUI_ID_USER + 0x04 + TEMP)) //close btn
	  		  {
					WM_DeleteWindow(hWin);
					state=MENU;
					hWin=CreateMENU();
					SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
					GUI_Delay(200);
	  		  }
	  		  break;
	  	  case LIGHT:
	  		  pom=(float)ad2;
	  		  pom=100.0*(pom)/(4095);
	  		  backlight=(uint8_t)SLIDER_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x07 + LIGHT)));
	  		  SSD1963_SetBacklight(backlight);
	  		  sprintf((char*)dataADC, "%d", (uint16_t)pom);
	  		  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + LIGHT)), dataADC);
	  		  PROGBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x01 + LIGHT)), ad2);
	  		  if(keyPressed==(GUI_ID_USER + 0x03 + LIGHT)) //close btn
	  		  {
					WM_DeleteWindow(hWin);
					state=MENU;
					hWin=CreateMENU();
					SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
					GUI_Delay(200);
	  		  }
	  		  break;
	  	  case ACCEL:
	  		  ADXL345_read_xyz();
			  x_accel=(int)ADXL345_GetX_ACCEL()+400;
			  y_accel=(int)ADXL345_GetY_ACCEL()+400;
			  z_accel=(int)ADXL345_GetZ_ACCEL()+648;
			  GRAPH_DATA_YT_AddValue(hData, (uint16_t)((x_accel)>>2));
			  GRAPH_DATA_YT_AddValue(hData1, (uint16_t)((y_accel)>>2));
			  GRAPH_DATA_YT_AddValue(hData2, (uint16_t)((z_accel)>>2));
			  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)==GPIO_PIN_SET&&SD_present)
			  {
				  if(state==ACCEL)
				  {
					  GUI_StoreKey(GUI_ID_USER + 0x04 + ACCEL);
					  logg=0;
				  }

				  SD_present=0;

			  }
			  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)==GPIO_PIN_RESET&&!SD_present)
			  {
				  if(state==ACCEL)
				  {
					  CHECKBOX_SetTextColor (WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), GUI_BLACK);
				  }
				  SD_present=1;
			  }

			  if(logg)
			  {
				  sprintf((char*)dataLOG, "%d\t%d\t%d%s", (uint16_t)x_accel, (uint16_t)y_accel, (uint16_t)z_accel, "\n");

				  f_printf(&AccelFile, "%s", dataLOG);
				  f_sync(&AccelFile);
			  }

			  if(keyPressed==(GUI_ID_USER + 0x04 + ACCEL)) // log check box
			  {
					logg=0;
					if(!SD_present)
					{
						 CHECKBOX_SetState(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), CHECKBOX_BI_INACTIV_UNCHECKED);
						 CHECKBOX_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), "Log");
						 CHECKBOX_SetTextColor (WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + ACCEL)), GUI_RED);
						 f_close(&AccelFile);
						 f_mount(0, SDPath, 1);
						 FATFS_UnLinkDriver(SDPath);
					}
					else
					{

					  if(CHECKBOX_IsChecked(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + ACCEL))))
					  {
						  FATFS_LinkDriver(&SD_Driver, SDPath);
						  res=f_mount(&myFAT, SDPath, 1);
						  if(res==FR_OK)
						  {
							  f_open(&AccelFile, "accel.txt", FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
							  f_lseek(&AccelFile, f_size(&AccelFile));
							  logg=1;
							  CHECKBOX_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), "Log->ON");
							  CHECKBOX_SetTextColor (WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + ACCEL)), GUI_GREEN);
						  }

					  }
					  else
					  {
						  f_close(&AccelFile);
						  f_mount(0, SDPath, 1);
						  FATFS_UnLinkDriver(SDPath);
						  CHECKBOX_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 +	ACCEL)), "Log");
						  CHECKBOX_SetTextColor (WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + ACCEL)), GUI_BLACK);

					  }
					}
					GUI_Delay(200);
			  }

			  if(keyPressed==(GUI_ID_USER + 0x03 + ACCEL)) // close btn
			  {
					WM_DeleteWindow(hWin);
					state=MENU;
					graph=0;
					logg=0;
					f_close(&AccelFile);
					f_mount(0, SDPath, 1);
					FATFS_UnLinkDriver(SDPath);
					hWin=CreateMENU();
					SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
					GUI_Delay(200);
			  }
	  		  break;
	  	  case TIME:
			  HAL_RTC_GetTime(&hrtc, &htime, RTC_FORMAT_BIN);
			  HAL_RTC_GetDate(&hrtc, &hdate, RTC_FORMAT_BIN);
			  dataADC[0]=0x30;
			  dataADC[1]=0x30;
			  sprintf((char*)dataADC, "%02d", (uint16_t)htime.Seconds);
			  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x04 + TIME)), dataADC);
			  sprintf((char*)dataADC, "%02d", (uint16_t)htime.Minutes);
			  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x03 + TIME)), dataADC);
			  sprintf((char*)dataADC, "%02d", (uint16_t)htime.Hours);
			  EDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x02 + TIME)), dataADC);
			  sprintf((char*)dataADC, "%02d/%02d/%02d", (uint16_t)hdate.Date, (uint16_t)hdate.Month, (uint16_t)hdate.Year);
			  TEXT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0B + TIME)), dataADC);

			  if(keyPressed==(GUI_ID_USER + 0x09 + TIME))// Set time
			  {
					WM_DeleteWindow(hWin1);
					state=SETTIME;
					hWin1=CreateSETTIME();
					SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETTIME)),htime.Hours);
					SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETTIME)),htime.Minutes);
					SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x04 + SETTIME)),htime.Seconds);
					GUI_Delay(200);
			  }

			  if(keyPressed==(GUI_ID_USER + 0x0A + TIME))// Set date
			  {
					WM_DeleteWindow(hWin1);
					state=SETDATE;
					hWin1=CreateSETDATE();
					SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETDATE)),hdate.Date);
					SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETDATE)),hdate.Month);
					SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x04 + SETDATE)),hdate.Year);
					GUI_Delay(200);
			  }

			  if(keyPressed==(GUI_ID_USER + 0x07 + TIME)) // close btn
			  {
					WM_DeleteWindow(hWin1);
					WM_DeleteWindow(hWin);
					state=MENU;
					hWin=CreateMENU();
					SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
					GUI_Delay(200);
			  }

	  		  break;
	  	  case TOUCH:
	  		  GUI_Clear();

	  		  GUI_SetFont(&GUI_Font8x16);
	  		  GUI_SetColor(GUI_WHITE);
	  		  GUI_DispStringAt("Touch RED circle ", 170, 130);
	  		  HAL_Delay(500);

	  		  GUI_SetColor(GUI_RED);
	  		  GUI_DrawCircle(RcalX[0], RcalY[0], 3);
	  		  GUI_FillCircle(RcalX[0], RcalY[0], 3);
	  		  while(!STMPE610_IsTouched());
	  		  HAL_Delay(300);
	  		  STMPE610_read_xyz();
	  		  GUI_SetColor(GUI_GREEN);
	  		  GUI_DrawCircle(RcalX[0], RcalY[0], 3);
	  		  GUI_FillCircle(RcalX[0], RcalY[0], 3);
	  		  ScalX[0]=STMPE610_GetX_TOUCH_RAW();
	  		  ScalY[0]=STMPE610_GetY_TOUCH_RAW();
	  		  sprintf((char*)dataADC, "%d", (uint16_t)ScalX[0]);
	  		  GUI_DispStringAt(dataADC, RcalX[0]+10, RcalY[0]-5);
	  		  sprintf((char*)dataADC, "%d", (uint16_t)ScalY[0]);
	  		  GUI_DispStringAt(dataADC, RcalX[0]+10, RcalY[0]+10);

	  		  GUI_SetColor(GUI_RED);
	  		  GUI_DrawCircle(RcalX[1], RcalY[1], 3);
	  		  GUI_FillCircle(RcalX[1], RcalY[1], 3);
	  		  while(!STMPE610_IsTouched());
	  		  HAL_Delay(300);
	  		  STMPE610_read_xyz();
	  		  GUI_SetColor(GUI_GREEN);
	  		  GUI_DrawCircle(RcalX[1], RcalY[1], 3);
	  		  GUI_FillCircle(RcalX[1], RcalY[1], 3);
	  		  ScalX[1]=STMPE610_GetX_TOUCH_RAW();
	  		  ScalY[1]=STMPE610_GetY_TOUCH_RAW();
	  		  sprintf((char*)dataADC, "%d", (uint16_t)ScalX[1]);
	  		  GUI_DispStringAt(dataADC, RcalX[1]+10, RcalY[1]-17);
	  		  sprintf((char*)dataADC, "%d", (uint16_t)ScalY[1]);
	  		  GUI_DispStringAt(dataADC, RcalX[1]+10, RcalY[1]-3);

	  		  GUI_SetColor(GUI_RED);
	  		  GUI_DrawCircle(RcalX[2], RcalY[2], 3);
	  		  GUI_FillCircle(RcalX[2], RcalY[2], 3);
	  		  while(!STMPE610_IsTouched());
	  		  HAL_Delay(300);
	  		  STMPE610_read_xyz();
	  		  GUI_SetColor(GUI_GREEN);
	  		  GUI_DrawCircle(RcalX[2], RcalY[2], 3);
	  		  GUI_FillCircle(RcalX[2], RcalY[2], 3);
	  		  ScalX[2]=STMPE610_GetX_TOUCH_RAW();
	  		  ScalY[2]=STMPE610_GetY_TOUCH_RAW();
	  		  sprintf((char*)dataADC, "%d", (uint16_t)ScalX[2]);
	  		  GUI_DispStringAt(dataADC, RcalX[2]-40, RcalY[2]-10);
	  		  sprintf((char*)dataADC, "%d", (uint16_t)ScalY[2]);
	  		  GUI_DispStringAt(dataADC, RcalX[2]-40, RcalY[2]+5);

	  		  HAL_Delay(1000);

	  		  GUI_TOUCH_CalcCoefficients(3, RcalX, RcalY, ScalX, ScalY, 480, 272);

	  		  GUI_Clear();
	  		  GUI_SetColor(GUI_WHITE);
	  		  GUI_DispStringAt("Test calibration - PRESS touch panel", 100, 130);

	  		  for(i=0; i<200; i++)
	  		  {
	  			  STMPE610_read_xyz();
	  			  GUI_TOUCH_Exec();
	  			  if(GUI_TOUCH_GetState(&hstate))
	  			  {
	  				  GUI_DrawPoint(hstate.x, hstate.y);
	  			  }
	  			  HAL_Delay(50);
	  		  }

	  		  GUI_Clear();
	  		  GUI_SetColor(GUI_WHITE);
	  		  GUI_DispStringAt("PRESS touch panel if calibration is OK before time expires", 10, 120);
	  		  HAL_Delay(300);
	  		  for(j=0; j<10; j++)
	  		  {
				  for(i=0; i<100; i++)
				  {
					  HAL_Delay(10);

					 STMPE610_read_xyz();
					 GUI_TOUCH_Exec();
					 if(GUI_TOUCH_GetState(&hstate))
					 {
						 GUI_Clear();
						 GUI_DispStringAt("Calibration DONE!!!", 160, 120);
						 HAL_Delay(1000);
						 GUI_Clear();

						 state=MENU;
						 hWin=CreateMENU();
			 		  	 SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);

						 GUI_Exec();

						 j=10;
						 i=100;

					 }
				  }
				  sprintf((char*)dataADC, "%d", (uint16_t)(9-j));
				  GUI_DispStringAt(dataADC, 235, 140);
	  		  }
	  		  GUI_Clear();
	  		  GUI_DispStringAt("Repeating Calibration!!!", 160, 120);
	  		  HAL_Delay(1000);
	  		  break;
	  	  case SLIDE:
	  		  GUI_Clear();

			  SSD1963_SetArea(0, 479, 272, 543);
			  loadBMPfromSD("images/im1.bmp");
			  SSD1963_SetScrollStart(272);
			  HAL_Delay(2000);

			  SSD1963_SetArea(0, 479, 544, 815);
			  loadBMPfromSD("images/im2.bmp");
			  SSD1963_SetScrollStart(544);
			  HAL_Delay(2000);

			  SSD1963_SetArea(0, 479, 0, 271);
			  loadBMPfromSD("images/im3.bmp");
			  SSD1963_SetScrollStart(0);
			  HAL_Delay(2000);

			  SSD1963_SetArea(0, 479, 544, 815);
			  loadBMPfromSD("images/im4.bmp");
			  SSD1963_SetScrollStart(544);
			  HAL_Delay(2000);

			  SSD1963_SetArea(0, 479, 0, 271);
			  loadBMPfromSD("images/im5.bmp");
			  SSD1963_SetScrollStart(0);
			  HAL_Delay(2000);

			  state=MENU;
 		  	  hWin=CreateMENU();
 		  	  SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
 		  	  GUI_Delay(200);
	  		  break;
	  	  case BUZZER:
	  		  if(keyPressed==(GUI_ID_USER + 0x03 + BUZZER))//buzzer close btn
	  		  {
				  WM_DeleteWindow(hWin);
	  	  	  	  state=MENU;
			 	  hWin=CreateMENU();
	 		  	  SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
			 	  GUI_Delay(200);
	  		  }
	  		  break;
	  	  case MP3:
	  		  if(keyPressed==(GUI_ID_USER + 0x01 + MP3)) MP3_SetState(BACKWARD);
	  		  if(keyPressed==(GUI_ID_USER + 0x02 + MP3)) MP3_SetState(PLAY);
	  		  if(keyPressed==(GUI_ID_USER + 0x03 + MP3)) MP3_SetState(PAUSE);
	  		  if(keyPressed==(GUI_ID_USER + 0x04 + MP3)) MP3_SetState(STOP);
	  		  if(keyPressed==(GUI_ID_USER + 0x05 + MP3)) MP3_SetState(FORWARD);

	  		  MP3_Exec();

	  		  volume=100-SLIDER_GetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x07 + MP3)));
	  		  VS1053_SetVolume(volume, volume);

	  		  if(keyPressed==(GUI_ID_USER + 0x09 + MP3)) // mp3 close btn
	  		  {
				  WM_DeleteWindow(hWin);
  	  	  	  	  MP3_Close();
	  	  	  	  state=MENU;
			 	  hWin=CreateMENU();
	 		  	  SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
			 	  GUI_Delay(200);
	  		  }
	  		  break;
	  	  case USB:
	  		  if(keyPressed==(GUI_ID_USER + 0x04 + USB))
	  		  {
	  			  for(i=0; i<255;i++) message[i]=0;
	  			  cursor=0;
	  		  }
	  		  if(UserRxBufferFS[0]!=0)
	  		  {
	  			  for(i=0; i<255;i++) message[i]=0;
	  			  cursor=0;
	  			  cursor=strlen((const char *)UserRxBufferFS);
	  			  strncpy(message,(char *)UserRxBufferFS,cursor);
	  			  message[cursor]=0;
	  			  UserRxBufferFS[0]=0;
	  		  }
	  		  if(keyPressed==(GUI_ID_USER + 0x05 + USB))
	  		  {
	  			  CDC_Transmit_FS((uint8_t*)message, strlen((const char *)message));
	  		  }

	  		  MULTIEDIT_SetText(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x03 + USB)), (const char*)message);
	  		  if(keyPressed==(GUI_ID_USER + 0x02 + USB))//usb close btn
	  		  {
				  WM_DeleteWindow(hWin1);
	  	  	  	  WM_DeleteWindow(hWin);
	  	  	  	  state=MENU;
			 	  hWin=CreateMENU();
	 		  	  SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
			 	  GUI_Delay(200);
	  		  }
	  		  break;
	  	  case FILES:
	  		  if(keyPressed==(GUI_ID_USER + 0x03 + FILES))//files close btn
			  {
				  WM_DeleteWindow(hWin);
	  	  	  	  state=MENU;
			 	  hWin=CreateMENU();
	 		  	  SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
			 	  GUI_Delay(200);
			  }
	  		  break;
	  	  case INFO:
	  		  if(keyPressed==(GUI_ID_USER + 0x03 + INFO)) //info close btn
	  		  {
				  WM_DeleteWindow(hWin);
	  	  	  	  state=MENU;
			 	  hWin=CreateMENU();
	 		  	  SCROLLBAR_SetValue(WM_GetDialogItem(hWin, (GUI_ID_USER + 0x0E)),scroll_state);
			 	  GUI_Delay(200);
	  		  }
	  		  break;
		  case SETTIME:
			  val=(uint8_t)SPINBOX_GetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETTIME)));
			  if(val==24)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETTIME)),0);
				  val=0;
			  }
			  if(val==-1)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETTIME)),23);
				  val=23;
			  }
			  htime.Hours=val;

			  val=(uint8_t)SPINBOX_GetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETTIME)));
			  if(val==60)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETTIME)),0);
				  val=0;
			  }
			  if(val==-1)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETTIME)),59);
				  val=59;
			  }
			  htime.Minutes=val;

			  val=(uint8_t)SPINBOX_GetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x04 + SETTIME)));
			  if(val==60)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x04 + SETTIME)),0);
				  val=0;
			  }
			  if(val==-1)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x04 + SETTIME)),59);
				  val=59;
			  }
			  htime.Seconds=val;

			  if(keyPressed==(GUI_ID_USER + 0x06 + SETTIME))//Cancel
			  {
							WM_DeleteWindow(hWin1);
							state=TIME;
							GUI_Delay(200);
			  }
			  if(keyPressed==(GUI_ID_USER + 0x05 + SETTIME))//OK
			  {
							WM_DeleteWindow(hWin1);
							HAL_RTC_SetTime(&hrtc, &htime, RTC_FORMAT_BIN);
							state=TIME;
							GUI_Delay(200);
			  }
			  break;
		  case SETDATE:
			  val=(uint8_t)SPINBOX_GetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETDATE)));
			  if(val==32)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETDATE)),1);
				  val=1;
			  }
			  if(val==0)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x02 + SETDATE)),31);
				  val=31;
			  }
			  hdate.Date=val;

			  val=(uint8_t)SPINBOX_GetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETDATE)));
			  if(val==13)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETDATE)),1);
				  val=1;
			  }
			  if(val==0)
			  {
				  SPINBOX_SetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x03 + SETDATE)),12);
				  val=12;
			  }
			  hdate.Month=val;

			  val=(uint8_t)SPINBOX_GetValue(WM_GetDialogItem(hWin1, (GUI_ID_USER + 0x04 + SETDATE)));
			  hdate.Year=val;

			  if(keyPressed==(GUI_ID_USER + 0x06 + SETDATE))//Cancel
			  {
					WM_DeleteWindow(hWin1);
					state=TIME;
					GUI_Delay(200);
			  }
			  if(keyPressed==(GUI_ID_USER + 0x05 + SETDATE))//OK
			  {
					WM_DeleteWindow(hWin1);
					HAL_RTC_SetDate(&hrtc, &hdate, RTC_FORMAT_BIN);
					state=TIME;
					GUI_Delay(200);
			  }
			  break;
	  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
