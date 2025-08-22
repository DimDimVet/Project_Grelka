#ifndef RCC_H_
#define RCC_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"

/*defaines*/
#define START_HSE (RCC->CR|=RCC_CR_HSEON)/*запуск HSE*/
#define STOP_HSE (RCC->CR &= ~RCC_CR_HSEON)/*останов HSE*/
#define READY_HSE (RCC->CR & RCC_CR_HSERDY)/*опросим RCC_CR_HSERDY*/
#define START_PLL (RCC->CR |= RCC_CR_PLLON)/*запуск PLL*/
#define READY_PLL (RCC->CR & RCC_CR_PLLRDY)/*опросим RCC_CR_PLLRDY*/
#define READY_SYSCLK_SWITCH (RCC->CFGR & RCC_CFGR_SWS_PLL)/*опросим RCC_CFGR_SWS_PLL*/
#define CONFIG_SYSCLK_SWITCH(_ITEM_SWITCH_) (RCC->CFGR |= _ITEM_SWITCH_)/*Установить свитч в PLL как системный такт*/
#define AHB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->AHB1ENR |= _RCC_PERIPHERY_)/*вкл что то по AHB1*/
#define APB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB1ENR |= _RCC_PERIPHERY_)/*вкл что то по APB1*/
#define APB2_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB2ENR |= _RCC_PERIPHERY_)/*вкл что то по APB2*/

/*structures*/
typedef struct
{
	uint16_t mDivider_PLLM; /*делитель PLLM=(HSE/8)*/
	uint16_t nMultiplier_PLLN; /*множитель PLLN=(HSE * 192)*/
	uint16_t pDivider_PLLP; /*значение PLLP = 6*/

} RCC_Structure;
/*var*/

/*func*/
void RCC_Init(RCC_Structure* rcc);
void Config_PLL(RCC_Structure* rcc);

#endif