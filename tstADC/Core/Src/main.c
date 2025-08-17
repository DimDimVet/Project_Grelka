
#include "main.h"
#include "HEHAL.h"
#include "ADC.h"
//
//#define ADC_SOFTWARE_START             ((uint32_t)ADC_CR2_EXTSEL + 1U)
//#define ADC_COMMON_REGISTER(__HANDLE__)                ADC123_COMMON
//#define ADC_CR2_CONTINUOUS(_CONTINUOUS_MODE_) ((_CONTINUOUS_MODE_) << 1U)
//#define ADC_CR1_DISCONTINUOUS(_NBR_DISCONTINUOUSCONV_) (((_NBR_DISCONTINUOUSCONV_) - 1U) << ADC_CR1_DISCNUM_Pos)
//#define ADC_SQR1(_NbrOfConversion_) (((_NbrOfConversion_) - (uint8_t)1U) << 20U)
//#define ADC_CR2_DMAContReq(_DMAContReq_MODE_) ((_DMAContReq_MODE_) << 9U)
//#define ADC_CR2_EOCSelection(_EOCSelection_MODE_) ((_EOCSelection_MODE_) << 10U)
//


//typedef struct
//{
//  uint32_t Pin;       /*!< Specifies the GPIO pins to be configured.
//                           This parameter can be any value of @ref GPIO_pins_define */

//  uint32_t Mode;      /*!< Specifies the operating mode for the selected pins.
//                           This parameter can be a value of @ref GPIO_mode_define */

//  uint32_t Pull;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
//                           This parameter can be a value of @ref GPIO_pull_define */

//  uint32_t Speed;     /*!< Specifies the speed for the selected pins.
//                           This parameter can be a value of @ref GPIO_speed_define */

//  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins. 
//                            This parameter can be a value of @ref GPIO_Alternate_function_selection */
//}GPIO_Structure;
//
//void SystemClock_Config(void);
//void MX_ADC1_InitX(void);
//HAL_StatusTypeDef ADC_InitX(ADC_Structure* hadc);
//void ADC_Init(ADC_Structure* hadc);
//void ADC_MspInit(ADC_HandleTypeDef* hadc);
//


ADC_HandleTypeDef hadc1;

//ADC_Structure adc;

int main(void)
{

  HAL_Init();

  //SystemClock_Config();

//  ADC_GPIO_Init();//ok
	
  //MX_ADC1_InitX();
	ADC_Init(ADC1,&hadc1);
	
	HAL_ADC_Start_IT(&hadc1); ///zzz

  while (1)
  {

  }

}


//void MX_ADC1_InitX(void)
//{

//  ADC_ChannelConfTypeDef sConfig = {0};//temp

//	
//  hadc.Instance = ADC1;
//  hadc.Init.ClockPrescaler = 0;
//  hadc.Init.Resolution = 0;
//  hadc.Init.ScanConvMode = 0;
//  hadc.Init.ContinuousConvMode = 1; ///запуск последовательности измерений
//  hadc.Init.DiscontinuousConvMode = 0;
//  hadc.Init.ExternalTrigConvEdge = 0;
//  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;//0x0F000001
//  hadc.Init.DataAlign = 0;
//  hadc.Init.NbrOfConversion = 1;
//  hadc.Init.DMAContinuousRequests = 0;
//  hadc.Init.EOCSelection = 0; ///измеряем все ацп которые используем
//  
//  hadc.Channel = ADC_CR1_AWDCH_0;//канал 1
//  hadc.Rank = 1;
//  hadc.SamplingTime = ADC_SMPR1_SMP10_1;//циклы подсчета

//	sConfig.Channel = hadc.Channel;
//  sConfig.Rank = hadc.Rank;
//  sConfig.SamplingTime = hadc.SamplingTime;
//	
//	hadc1.Instance = hadc.Instance;
//  hadc1.Init.ClockPrescaler = hadc.Init.ClockPrescaler;
//  hadc1.Init.Resolution = hadc.Init.Resolution;
//  hadc1.Init.ScanConvMode = hadc.Init.ScanConvMode;
//  hadc1.Init.ContinuousConvMode = hadc.Init.ContinuousConvMode;
//  hadc1.Init.DiscontinuousConvMode = hadc.Init.DiscontinuousConvMode;
//  hadc1.Init.ExternalTrigConvEdge = hadc.Init.ExternalTrigConvEdge;
//  hadc1.Init.ExternalTrigConv = hadc.Init.ExternalTrigConv;//0x0F000001
//  hadc1.Init.DataAlign = hadc.Init.DataAlign;
//  hadc1.Init.NbrOfConversion = hadc.Init.NbrOfConversion;
//  hadc1.Init.DMAContinuousRequests = hadc.Init.DMAContinuousRequests;
//  hadc1.Init.EOCSelection = hadc.Init.EOCSelection; ///измеряем все ацп которые используем
//	
//	
//	if (ADC_InitX(&hadc) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

//}

//HAL_StatusTypeDef ADC_InitX(ADC_Structure* hadc)
//{
//	
//	hadc1.Instance = hadc->Instance;
//  hadc1.Init.ClockPrescaler = hadc->Init.ClockPrescaler;
//  hadc1.Init.Resolution = hadc->Init.Resolution;
//  hadc1.Init.ScanConvMode = hadc->Init.ScanConvMode;
//  hadc1.Init.ContinuousConvMode = hadc->Init.ContinuousConvMode;
//  hadc1.Init.DiscontinuousConvMode = hadc->Init.DiscontinuousConvMode;
//  hadc1.Init.ExternalTrigConvEdge = hadc->Init.ExternalTrigConvEdge;
//  hadc1.Init.ExternalTrigConv = hadc->Init.ExternalTrigConv;//0x0F000001
//  hadc1.Init.DataAlign = hadc->Init.DataAlign;
//  hadc1.Init.NbrOfConversion = hadc->Init.NbrOfConversion;
//  hadc1.Init.DMAContinuousRequests = hadc->Init.DMAContinuousRequests;
//  hadc1.Init.EOCSelection = hadc->Init.EOCSelection; ///измеряем все ацп которые используем
//	
//  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
//  
//  /* Check ADC handle */
//  if(hadc == NULL)
//  {
//    return HAL_ERROR;
//  }
//  
//  if(hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
//  {
//    //assert_param(IS_ADC_EXT_TRIG_EDGE(hadc->Init.ExternalTrigConvEdge));
//  }
//  
//    ADC_MspInit(&hadc1);
//	
//    ADC_Init(hadc);

//  return tmp_hal_status;
//}

//void ADC_MspInit(ADC_HandleTypeDef* hadc)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  if(hadc->Instance==ADC1)
//  {
//  /* USER CODE BEGIN ADC1_MspInit 0 */

//  /* USER CODE END ADC1_MspInit 0 */
//    /* Peripheral clock enable */
//    __HAL_RCC_ADC1_CLK_ENABLE();

//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    /**ADC1 GPIO Configuration
//    PA1     ------> ADC1_IN1
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_1;
//    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//    /* ADC1 interrupt Init */
//    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(ADC_IRQn);
//  /* USER CODE BEGIN ADC1_MspInit 1 */

//  /* USER CODE END ADC1_MspInit 1 */
//  }

//}

//void ADC_Init(ADC_Structure* hadc)
//{
//  ADC_Common_TypeDef *tmpADC_Common;
//  
//  /* Set ADC parameters */
//  /* Pointer to the common control register to which is belonging hadc    */
//  /* (Depending on STM32F4 product, there may be up to 3 ADCs and 1 common */
//  /* control register)                                                    */
//  tmpADC_Common = ADC_COMMON_REGISTER(hadc);
//  
//  /* Set the ADC clock prescaler */
//  tmpADC_Common->CCR &= ~(ADC_CCR_ADCPRE);
//  tmpADC_Common->CCR |=  hadc->Init.ClockPrescaler;
//  
//  /* Set ADC scan mode */
//  hadc->Instance->CR1 &= ~(ADC_CR1_SCAN);
//  hadc->Instance->CR1 |=  ADC_CR1_SCANCONV(hadc->Init.ScanConvMode);
//  
//  /* Set ADC resolution */
//  hadc->Instance->CR1 &= ~(ADC_CR1_RES);
//  hadc->Instance->CR1 |=  hadc->Init.Resolution;
//  
//  /* Set ADC data alignment */
//  hadc->Instance->CR2 &= ~(ADC_CR2_ALIGN);
//  hadc->Instance->CR2 |= hadc->Init.DataAlign;
//  
//  /* Enable external trigger if trigger selection is different of software  */
//  /* start.                                                                 */
//  /* Note: This configuration keeps the hardware feature of parameter       */
//  /*       ExternalTrigConvEdge "trigger edge none" equivalent to           */
//  /*       software start.                                                  */
//  if(hadc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
//  {
//    /* Select external trigger to start conversion */
//    hadc->Instance->CR2 &= ~(ADC_CR2_EXTSEL);
//    hadc->Instance->CR2 |= hadc->Init.ExternalTrigConv;
//    
//    /* Select external trigger polarity */
//    hadc->Instance->CR2 &= ~(ADC_CR2_EXTEN);
//    hadc->Instance->CR2 |= hadc->Init.ExternalTrigConvEdge;
//  }
//  else
//  {
//    /* Reset the external trigger */
//    hadc->Instance->CR2 &= ~(ADC_CR2_EXTSEL);
//    hadc->Instance->CR2 &= ~(ADC_CR2_EXTEN);
//  }
//  
//  /* Enable or disable ADC continuous conversion mode */
//  hadc->Instance->CR2 &= ~(ADC_CR2_CONT);
//  hadc->Instance->CR2 |= ADC_CR2_CONTINUOUS((uint32_t)hadc->Init.ContinuousConvMode);
//  
//  if(hadc->Init.DiscontinuousConvMode != DISABLE)
//  {
//    //assert_param(IS_ADC_REGULAR_DISC_NUMBER(hadc->Init.NbrOfDiscConversion));
//  
//    /* Enable the selected ADC regular discontinuous mode */
//    hadc->Instance->CR1 |= (uint32_t)ADC_CR1_DISCEN;
//    
//    /* Set the number of channels to be converted in discontinuous mode */
//    hadc->Instance->CR1 &= ~(ADC_CR1_DISCNUM);
//    hadc->Instance->CR1 |=  ADC_CR1_DISCONTINUOUS(hadc->Init.NbrOfDiscConversion);
//  }
//  else
//  {
//    /* Disable the selected ADC regular discontinuous mode */
//    hadc->Instance->CR1 &= ~(ADC_CR1_DISCEN);
//  }
//  
//  /* Set ADC number of conversion */
//  hadc->Instance->SQR1 &= ~(ADC_SQR1_L);
//  hadc->Instance->SQR1 |=  ADC_SQR1(hadc->Init.NbrOfConversion);
//  
//  /* Enable or disable ADC DMA continuous request */
//  hadc->Instance->CR2 &= ~(ADC_CR2_DDS);
//  hadc->Instance->CR2 |= ADC_CR2_DMAContReq((uint32_t)hadc->Init.DMAContinuousRequests);
//  
//  /* Enable or disable ADC end of conversion selection */
//  hadc->Instance->CR2 &= ~(ADC_CR2_EOCS);
//  hadc->Instance->CR2 |= ADC_CR2_EOCSelection(hadc->Init.EOCSelection);
//}









//void SystemClock_Config(void)
//{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

//  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
//  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
//  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }

//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}





//void Error_Handler(void)
//{

//  __disable_irq();
//  while (1)
//  {
//  }

//}

