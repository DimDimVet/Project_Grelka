#ifndef RCC_H_
#define RCC_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"

/*defaines*/
#define US SystemCoreClock / 1000000 /*SystemCoreClock=72000000*/
#define SYSTICK_MAX_VALUE 16777215
#define US_MAX_VALUE SYSTICK_MAX_VALUE / (US)

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

void delay_us(int us);
void delay_ms(int ms);
void delay_s(int s);

#endif