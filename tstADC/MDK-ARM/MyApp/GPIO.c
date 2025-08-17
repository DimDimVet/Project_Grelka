#include "GPIO.h"

void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_Structure *GPIO_Str)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t temp = 0x00U;

  /* Настройте контакты порта */
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    /* Получить позицию ввода-вывода */
    ioposition = 0x01U << position;
    /* Получить текущую позицию ввода-вывода */
    iocurrent = (uint32_t)(GPIO_Str->Pin) & ioposition;

    if(iocurrent == ioposition)
    {
      /*--------------------- GPIO Конфигурация режима ------------------------*/
      /* В случае выбора режима выхода или альтернативной функции */
      if(((GPIO_Str->Mode & GPIO_MODE) == MODE_OUTPUT) || \
          (GPIO_Str->Mode & GPIO_MODE) == MODE_AF)
      {
        /* Настройте скорость ввода-вывода */
        temp = GPIOx->OSPEEDR; 
        temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));
        temp |= (GPIO_Str->Speed << (position * 2U));
        GPIOx->OSPEEDR = temp;

        /* Настройте тип вывода ввода-вывода */
        temp = GPIOx->OTYPER;
        temp &= ~(GPIO_OTYPER_OT_0 << position) ;
        temp |= (((GPIO_Str->Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << position);
        GPIOx->OTYPER = temp;
       }

      if((GPIO_Str->Mode & GPIO_MODE) != MODE_ANALOG)
      {
        /* Активируйте подтягивающий или понижающий резистор для текущего ввода-вывода */
        temp = GPIOx->PUPDR;
        temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));
        temp |= ((GPIO_Str->Pull) << (position * 2U));
        GPIOx->PUPDR = temp;
      }

      /* В случае выбора режима альтернативной функции */
      if((GPIO_Str->Mode & GPIO_MODE) == MODE_AF)
      {
        /* Настроить альтернативную функцию, сопоставленную с текущим вводом-выводом */
        temp = GPIOx->AFR[position >> 3U];
        temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;
        temp |= ((uint32_t)(GPIO_Str->Alternate) << (((uint32_t)position & 0x07U) * 4U));
        GPIOx->AFR[position >> 3U] = temp;
      }

      /* Настроить режим направления ввода-вывода (Input, Output, Alternate or Analog) */
      temp = GPIOx->MODER;
      temp &= ~(GPIO_MODER_MODER0 << (position * 2U));
      temp |= ((GPIO_Str->Mode & GPIO_MODE) << (position * 2U));
      GPIOx->MODER = temp;

      /*--------------------- Конфигурация режима EXTI ------------------------*/
      /* Настройте внешнее прерывание или событие для текущего ввода-вывода */
      if((GPIO_Str->Mode & EXTI_MODE) != 0x00U)
      {
        /* Включить SYSCFG */
				ENABLE_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

        temp = SYSCFG->EXTICR[position >> 2U];
        temp &= ~(0x0FU << (4U * (position & 0x03U)));
        temp |= ((uint32_t)(GPIO_GET_INDEX(GPIOx)) << (4U * (position & 0x03U)));
        SYSCFG->EXTICR[position >> 2U] = temp;

        /* Очистить конфигурацию восходящего и нисходящего фронта */
        temp = EXTI->RTSR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Str->Mode & TRIGGER_RISING) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->RTSR = temp;

        temp = EXTI->FTSR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Str->Mode & TRIGGER_FALLING) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->FTSR = temp;

        temp = EXTI->EMR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Str->Mode & EXTI_EVT) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->EMR = temp;

        /* Очистить конфигурацию линии EXTI */
        temp = EXTI->IMR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Str->Mode & EXTI_IT) != 0x00U)
        {
          temp |= iocurrent;
        }
        EXTI->IMR = temp;
      }
    }
  }
}