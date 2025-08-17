#include "ADC.h"

/*var*/
ADC_Structure adc;

Rezult_t ADC_Init(ADC_TypeDef* instance,ADC_HandleTypeDef* hadc1)
{
	Rezult_t tmp_rezult=OK_;
	
	if (instance == NULL)
	{
		tmp_rezult = ERROR_;
	}
	else
	{
		adc.Instance = instance;
		ADC_SetStructure(&adc, hadc1);
	}
	
	return tmp_rezult;
}

Rezult_t ADC_SetStructure(ADC_Structure* adc, ADC_HandleTypeDef* hadc1)
{
	Rezult_t tmp_rezult=OK_;

  ADC_ChannelConfTypeDef sConfig = {0};//temp

  adc->Init.ClockPrescaler = 0;
  adc->Init.Resolution = 0;
  adc->Init.ScanConvMode = 0;
  adc->Init.ContinuousConvMode = 1; ///запуск последовательности измерений
  adc->Init.DiscontinuousConvMode = 0;
  adc->Init.ExternalTrigConvEdge = 0;
  adc->Init.ExternalTrigConv = ADC_SOFTWARE_START;//0x0F000001
  adc->Init.DataAlign = 0;
  adc->Init.NbrOfConversion = 1;
  adc->Init.DMAContinuousRequests = 0;
  adc->Init.EOCSelection = 0; ///измеряем все ацп которые используем
  
  adc->Channel = ADC_CR1_AWDCH_0;//канал 1
  adc->Rank = 1;
  adc->SamplingTime = ADC_SMPR1_SMP10_1;//циклы подсчета

	//мусор
	sConfig.Channel = adc->Channel;
  sConfig.Rank = adc->Rank;
  sConfig.SamplingTime = adc->SamplingTime;
	
	hadc1->Instance = adc->Instance;
  hadc1->Init.ClockPrescaler = adc->Init.ClockPrescaler;
  hadc1->Init.Resolution = adc->Init.Resolution;
  hadc1->Init.ScanConvMode = adc->Init.ScanConvMode;
  hadc1->Init.ContinuousConvMode = adc->Init.ContinuousConvMode;
  hadc1->Init.DiscontinuousConvMode = adc->Init.DiscontinuousConvMode;
  hadc1->Init.ExternalTrigConvEdge = adc->Init.ExternalTrigConvEdge;
  hadc1->Init.ExternalTrigConv = adc->Init.ExternalTrigConv;//0x0F000001
  hadc1->Init.DataAlign = adc->Init.DataAlign;
  hadc1->Init.NbrOfConversion = adc->Init.NbrOfConversion;
  hadc1->Init.DMAContinuousRequests = adc->Init.DMAContinuousRequests;
  hadc1->Init.EOCSelection = adc->Init.EOCSelection; ///измеряем все ацп которые используем
	//мусор
  
  ADC_MspInit(adc);
	
	ADC_SetReg(adc);


  if (HAL_ADC_ConfigChannelX(hadc1, &sConfig) != HAL_OK)
  {
    tmp_rezult=ERROR_;
  }
	
	return tmp_rezult;

}

Rezult_t ADC_MspInit(ADC_Structure* adc)
{
	Rezult_t tmp_rezult=OK_;
	
  GPIO_Structure GPIO_InitStruct = {0};
	
  if(adc->Instance==ADC1) /*ADC1 GPIO Configuration PA1 --> ADC1_IN1 */
  {
		ENABLE_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);

		ENABLE_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		
		GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		
    GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
	else
	{
	
	}
	
	/* ADC прерывания */
	NVIC_SetPriority(ADC_IRQn, 0);
	NVIC_EnableIRQ(ADC_IRQn);
	
	return tmp_rezult;

}

Rezult_t ADC_SetReg(ADC_Structure* adc)
{
	Rezult_t tmp_rezult=OK_;
	
  ADC_Common_TypeDef *tmpADC_Common;
  
  /* Указатель на общий регистр управления, к которому принадлежит adc */                                                  
  tmpADC_Common = ADC_COMMON_REGISTER(adc);
  
  /* Установите предделитель тактовой частоты АЦП */
  tmpADC_Common->CCR &= ~(ADC_CCR_ADCPRE);
  tmpADC_Common->CCR |=  adc->Init.ClockPrescaler;
  
  /* Установить режим сканирования АЦП */
  adc->Instance->CR1 &= ~(ADC_CR1_SCAN);
  adc->Instance->CR1 |=  ADC_CR1_SCANCONV(adc->Init.ScanConvMode);
  
  /* Установить разрешение АЦП */
  adc->Instance->CR1 &= ~(ADC_CR1_RES);
  adc->Instance->CR1 |=  adc->Init.Resolution;
  
  /* Установить выравнивание данных АЦП */
  adc->Instance->CR2 &= ~(ADC_CR2_ALIGN);
  adc->Instance->CR2 |= adc->Init.DataAlign;
  
  /* Включить внешний триггер, если выбор триггера отличается от запуска программного обеспечения */
  if(adc->Init.ExternalTrigConv != ADC_SOFTWARE_START)
  {
    /* Выберите внешний триггер для начала преобразования */
    adc->Instance->CR2 &= ~(ADC_CR2_EXTSEL);
    adc->Instance->CR2 |= adc->Init.ExternalTrigConv;
    
    /* Выберите полярность внешнего триггера */
    adc->Instance->CR2 &= ~(ADC_CR2_EXTEN);
    adc->Instance->CR2 |= adc->Init.ExternalTrigConvEdge;
  }
  else
  {
    /* Сброс внешнего триггера */
    adc->Instance->CR2 &= ~(ADC_CR2_EXTSEL);
    adc->Instance->CR2 &= ~(ADC_CR2_EXTEN);
  }
  
  /* Включить или отключить режим непрерывного преобразования АЦП */
  adc->Instance->CR2 &= ~(ADC_CR2_CONT);
  adc->Instance->CR2 |= ADC_CR2_CONTINUOUS((uint32_t)adc->Init.ContinuousConvMode);
  
  if(adc->Init.DiscontinuousConvMode != DISABLE)
  {
    /* Включить выбранный регулярный прерывистый режим АЦП */
    adc->Instance->CR1 |= (uint32_t)ADC_CR1_DISCEN;
    
    /* Установите количество каналов для преобразования в прерывистом режиме. */
    adc->Instance->CR1 &= ~(ADC_CR1_DISCNUM);
    adc->Instance->CR1 |=  ADC_CR1_DISCONTINUOUS(adc->Init.NbrOfDiscConversion);
  }
  else
  {
    /* Отключить выбранный режим постоянного прерывистого преобразования АЦП */
    adc->Instance->CR1 &= ~(ADC_CR1_DISCEN);
  }
  
  /* Установить номер преобразования АЦП */
  adc->Instance->SQR1 &= ~(ADC_SQR1_L);
  adc->Instance->SQR1 |=  ADC_SQR1(adc->Init.NbrOfConversion);
  
  /* Включить или отключить непрерывный запрос ADC DMA */
  adc->Instance->CR2 &= ~(ADC_CR2_DDS);
  adc->Instance->CR2 |= ADC_CR2_DMAContReq((uint32_t)adc->Init.DMAContinuousRequests);
  
  /* Включить или отключить выбор конца преобразования АЦП */
  adc->Instance->CR2 &= ~(ADC_CR2_EOCS);
  adc->Instance->CR2 |= ADC_CR2_EOCSelection(adc->Init.EOCSelection);
	
	return tmp_rezult;
}

HAL_StatusTypeDef HAL_ADC_ConfigChannelX(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{
  __IO uint32_t counter = 0U;
  ADC_Common_TypeDef *tmpADC_Common;
  
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(sConfig->Channel));
  assert_param(IS_ADC_REGULAR_RANK(sConfig->Rank));
  assert_param(IS_ADC_SAMPLE_TIME(sConfig->SamplingTime));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* if ADC_Channel_10 ... ADC_Channel_18 is selected */
  if (sConfig->Channel > ADC_CHANNEL_9)
  {
    /* Clear the old sample time */
    hadc->Instance->SMPR1 &= ~ADC_SMPR1(ADC_SMPR1_SMP10, sConfig->Channel);
    
    /* Set the new sample time */
    hadc->Instance->SMPR1 |= ADC_SMPR1(sConfig->SamplingTime, sConfig->Channel);
  }
  else /* ADC_Channel include in ADC_Channel_[0..9] */
  {
    /* Clear the old sample time */
    hadc->Instance->SMPR2 &= ~ADC_SMPR2(ADC_SMPR2_SMP0, sConfig->Channel);
    
    /* Set the new sample time */
    hadc->Instance->SMPR2 |= ADC_SMPR2(sConfig->SamplingTime, sConfig->Channel);
  }
  
  /* For Rank 1 to 6 */
  if (sConfig->Rank < 7U)
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->SQR3 &= ~ADC_SQR3_RK(ADC_SQR3_SQ1, sConfig->Rank);
    
    /* Set the SQx bits for the selected rank */
    hadc->Instance->SQR3 |= ADC_SQR3_RK(sConfig->Channel, sConfig->Rank);
  }
  /* For Rank 7 to 12 */
  else if (sConfig->Rank < 13U)
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->SQR2 &= ~ADC_SQR2_RK(ADC_SQR2_SQ7, sConfig->Rank);
    
    /* Set the SQx bits for the selected rank */
    hadc->Instance->SQR2 |= ADC_SQR2_RK(sConfig->Channel, sConfig->Rank);
  }
  /* For Rank 13 to 16 */
  else
  {
    /* Clear the old SQx bits for the selected rank */
    hadc->Instance->SQR1 &= ~ADC_SQR1_RK(ADC_SQR1_SQ13, sConfig->Rank);
    
    /* Set the SQx bits for the selected rank */
    hadc->Instance->SQR1 |= ADC_SQR1_RK(sConfig->Channel, sConfig->Rank);
  }

    /* Pointer to the common control register to which is belonging hadc    */
    /* (Depending on STM32F4 product, there may be up to 3 ADCs and 1 common */
    /* control register)                                                    */
    tmpADC_Common = ADC_COMMON_REGISTER(hadc);

  /* if ADC1 Channel_18 is selected for VBAT Channel ennable VBATE */
  if ((hadc->Instance == ADC1) && (sConfig->Channel == ADC_CHANNEL_VBAT))
  {
    /* Disable the TEMPSENSOR channel in case of using board with multiplixed ADC_CHANNEL_VBAT & ADC_CHANNEL_TEMPSENSOR*/    
    if ((uint16_t)ADC_CHANNEL_TEMPSENSOR == (uint16_t)ADC_CHANNEL_VBAT)
    {
      tmpADC_Common->CCR &= ~ADC_CCR_TSVREFE;
    }
    /* Enable the VBAT channel*/
    tmpADC_Common->CCR |= ADC_CCR_VBATE;
  }
  
  /* if ADC1 Channel_16 or Channel_18 is selected for Temperature sensor or 
     Channel_17 is selected for VREFINT enable TSVREFE */
  if ((hadc->Instance == ADC1) && ((sConfig->Channel == ADC_CHANNEL_TEMPSENSOR) || (sConfig->Channel == ADC_CHANNEL_VREFINT)))
  {
    /* Disable the VBAT channel in case of using board with multiplixed ADC_CHANNEL_VBAT & ADC_CHANNEL_TEMPSENSOR*/
    if ((uint16_t)ADC_CHANNEL_TEMPSENSOR == (uint16_t)ADC_CHANNEL_VBAT)
    {
      tmpADC_Common->CCR &= ~ADC_CCR_VBATE;
    }
    /* Enable the Temperature sensor and VREFINT channel*/
    tmpADC_Common->CCR |= ADC_CCR_TSVREFE;
    
    if(sConfig->Channel == ADC_CHANNEL_TEMPSENSOR)
    {
      /* Delay for temperature sensor stabilization time */
      /* Compute number of CPU cycles to wait for */
      counter = (ADC_TEMPSENSOR_DELAY_US * (SystemCoreClock / 1000000U));
      while(counter != 0U)
      {
        counter--;
      }
    }
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}



