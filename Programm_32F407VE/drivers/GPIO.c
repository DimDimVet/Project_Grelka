#include "GPIO.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_Structure *GPIO_Str)
{
  /*--------------------- GPIO Конфигурация режима ------------------------*/

  /* Настроить режим направления ввода-вывода (Input, Output, Alternate or Analog) */
  GPIOx->MODER &= ~(GPIO_MODER_MODER0 << (GPIO_Str->Pin * 2U));
  GPIOx->MODER |= ((GPIO_Str->Mode) << (GPIO_Str->Pin * 2U));

  /* В случае выбора режима выхода или альтернативной функции */
  if (((GPIO_Str->Mode) == GPIO_MODE_OUTPUT) || (GPIO_Str->Mode) == GPIO_MODE_AF)
  {
    /* Настройте скорость ввода-вывода */
    GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (GPIO_Str->Pin * 2U));
    GPIOx->OSPEEDR |= (GPIO_Str->Speed << (GPIO_Str->Pin * 2U));

    /* Настройте тип вывода ввода-вывода */
    GPIOx->OTYPER &= ~(GPIO_OTYPER_OT_0 << GPIO_Str->Pin);
    GPIOx->OTYPER |= (((GPIO_Str->Mode & GPIO_OUTPUT_TYPE) >> GPIO_OUTPUT_TYPE_Pos) << GPIO_Str->Pin);
  }

  /* В случае выбора режима аналогового выхода */
  if ((GPIO_Str->Mode) != GPIO_MODE_ANALOG)
  {
    /* Активируйте подтягивающий или понижающий резистор для текущего ввода-вывода */
    GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (GPIO_Str->Pin * 2U));
    GPIOx->PUPDR |= ((GPIO_Str->Pull) << (GPIO_Str->Pin * 2U));
  }

  /* В случае выбора режима альтернативной функции */
  if ((GPIO_Str->Mode) == GPIO_MODE_AF)
  {
    /* Настроить альтернативную функцию, сопоставленную с текущим вводом-выводом */
    GPIOx->AFR[GPIO_Str->Pin >> 3U] &= ~(0xFU << ((uint32_t)(GPIO_Str->Pin & 0x07U) * 4U));
    GPIOx->AFR[GPIO_Str->Pin >> 3U] |= ((uint32_t)(GPIO_Str->Alternate) << (((uint32_t)GPIO_Str->Pin & 0x07U) * 4U));
  }
}