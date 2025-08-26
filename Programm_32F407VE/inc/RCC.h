#ifndef RCC_H_
#define RCC_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"

/*defaines*/

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