#ifndef PWR_H_
#define PWR_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"

/*defaines*/
#define TIM_PRESCALE (840 - 1)/*делитель TIM prescaler 8400 - 1 = 38Гц, 840 - 1=380Гц*/
#define COUNT_RESET (100 - 1)/*автосброс*/
#define TIM_MODE_PWR1 (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)/*TIM1 and TIM8 capture/compare mode register 1 (TIMx_CCMR1)*/
/*structures*/
typedef struct
{
	TIM_TypeDef* TIMx;  /*Указывает настраиваемые таймер TIM_TypeDef*/
	uint32_t rcc_TIMEN; /*ссылка на периферию*/
	uint8_t fill_Factor; /*значение Коэффициента заполнения*/
	
} PWR_Structure;

/*var*/

/*func*/
void Init_Tim_PWR(PWR_Structure* pwr);
void Enable_Periphery_PWR(PWR_Structure* pwr);
void Enable_GPIO_PWR(void);
void Replace_Fill_Factor(PWR_Structure* pwr);

#endif