#include "GPIO.h"

void GPIO_Init(GPIO_Structure *GPIO_Str)
{
  /*--------------------- GPIO Конфигурация режима ------------------------*/

  /* Настроить режим направления ввода-вывода (Input, Output, Alternate, Analog) */
  GPIO_Str->GPIOx->MODER &= ~(GPIO_MODER_MODER0 << (GPIO_Str->Pin * 2));
  GPIO_Str->GPIOx->MODER |= ((GPIO_Str->Mode) << (GPIO_Str->Pin * 2));
	/*--------------------- GPIO Конфигурация остальное ------------------------*/

	/* В случае выбора режима входа*/
	if (GPIO_Str->Mode == GPIO_MODE_INPUT)
  {
    GPIO_Str->GPIOx->PUPDR &= ~(0x3 << (GPIO_Str->Pin * 2));
    GPIO_Str->GPIOx->PUPDR |= ((GPIO_Str->Pull) << (GPIO_Str->Pin * 2));
  }
	
	/* В случае выбора режима выхода*/
	if (GPIO_Str->Mode == GPIO_MODE_OUTPUT)
  {
		/* Активируйте подтягивающий или понижающий резистор для текущего ввода-вывода */
		GPIO_Str->GPIOx->PUPDR &= ~(0x3 << (GPIO_Str->Pin * 2));
    GPIO_Str->GPIOx->PUPDR |= ((GPIO_Str->Pull) << (GPIO_Str->Pin * 2));
		/* Настройте скорость ввода-вывода */
    GPIO_Str->GPIOx->OSPEEDR &= ~(0x3 << (GPIO_Str->Pin * 2));
    GPIO_Str->GPIOx->OSPEEDR |= (GPIO_Str->Speed << (GPIO_Str->Pin * 2));
		/* Настройте тип вывода ввода-вывода */
    GPIO_Str->GPIOx->OTYPER &= ~(GPIO_OTYPER_OT_0 << GPIO_Str->Pin);
    GPIO_Str->GPIOx->OTYPER |= (GPIO_Str->Otyper << GPIO_Str->Pin);
  }
	
	/* В случае выбора режима альтернативной функции */
	if (GPIO_Str->Mode == GPIO_MODE_AF)
  {
		/* Активируйте подтягивающий или понижающий резистор для текущего ввода-вывода */
		GPIO_Str->GPIOx->PUPDR &= ~(0x3 << (GPIO_Str->Pin * 2));
    GPIO_Str->GPIOx->PUPDR |= ((GPIO_Str->Pull) << (GPIO_Str->Pin * 2));
		/* Настройте скорость ввода-вывода */
    GPIO_Str->GPIOx->OSPEEDR &= ~(0x3 << (GPIO_Str->Pin * 2));
    GPIO_Str->GPIOx->OSPEEDR |= (GPIO_Str->Speed << (GPIO_Str->Pin * 2));
		/* Настройте тип вывода ввода-вывода */
    GPIO_Str->GPIOx->OTYPER &= ~(0x1 << GPIO_Str->Pin);
    GPIO_Str->GPIOx->OTYPER |= (GPIO_Str->Otyper << GPIO_Str->Pin);
    /* Настроить альтернативную функцию, сопоставленную с текущим вводом-выводом */
    GPIO_Str->GPIOx->AFR[GPIO_Str->Pin >> 3] &= ~(0xF << ((GPIO_Str->Pin & 0x07U) * 4));
    GPIO_Str->GPIOx->AFR[GPIO_Str->Pin >> 3] |= ((GPIO_Str->Alternate) << ((GPIO_Str->Pin & 0x07) * 4));
  }
	
	/* В случае выбора режима входа/выхода(аналог)*/
	if (GPIO_Str->Mode == GPIO_MODE_ANALOG)
  {

  }
	
//  /* В случае выбора режима выхода или альтернативной функции */
//  if (((GPIO_Str->Mode) == GPIO_MODE_OUTPUT) || (GPIO_Str->Mode) == GPIO_MODE_AF)
//  {
//    /* Настройте скорость ввода-вывода */
//    GPIO_Str->GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (GPIO_Str->Pin * 2U));
//    GPIO_Str->GPIOx->OSPEEDR |= (GPIO_Str->Speed << (GPIO_Str->Pin * 2U));

//    /* Настройте тип вывода ввода-вывода */
//    GPIO_Str->GPIOx->OTYPER &= ~(GPIO_OTYPER_OT_0 << GPIO_Str->Pin);
//    GPIO_Str->GPIOx->OTYPER |= (((GPIO_Str->Mode & GPIO_OUTPUT_TYPE) >> GPIO_OUTPUT_TYPE_Pos) << GPIO_Str->Pin);
//  }

//  /* В случае выбора режима аналогового выхода */
//  if ((GPIO_Str->Mode) != GPIO_MODE_ANALOG)
//  {
//    /* Активируйте подтягивающий или понижающий резистор для текущего ввода-вывода */
//    GPIO_Str->GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (GPIO_Str->Pin * 2U));
//    GPIO_Str->GPIOx->PUPDR |= ((GPIO_Str->Pull) << (GPIO_Str->Pin * 2U));
//  }

//  /* В случае выбора режима альтернативной функции */
//  if ((GPIO_Str->Mode) == GPIO_MODE_AF)
//  {
//    /* Настроить альтернативную функцию, сопоставленную с текущим вводом-выводом */
//    GPIO_Str->GPIOx->AFR[GPIO_Str->Pin >> 3U] &= ~(0xFU << ((uint32_t)(GPIO_Str->Pin & 0x07U) * 4U));
//    GPIO_Str->GPIOx->AFR[GPIO_Str->Pin >> 3U] |= ((uint32_t)(GPIO_Str->Alternate) << (((uint32_t)GPIO_Str->Pin & 0x07U) * 4U));
//  }
}

/* побитовые выполнители*/
void ODR_Xor(GPIO_Structure *GPIO_Str)
{
    GPIO_Str->GPIOx->ODR ^= 1 << GPIO_Str->Pin;
}

void ODR_1(GPIO_Structure *GPIO_Str)
{
    GPIO_Str->GPIOx->ODR |= 1 << GPIO_Str->Pin;
}

void ODR_0(GPIO_Structure *GPIO_Str)
{
    GPIO_Str->GPIOx->ODR |= 0 << GPIO_Str->Pin;
}
