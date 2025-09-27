#ifndef PWR_H_
#define PWR_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"

/*defaines*/
#define TIM_PRESCALE (840 - 1)/*делитель TIM prescaler 8400 - 1 = 38Гц, 840 - 1=380Гц, 84 - 1=3800Гц*/
#define COUNT_RESET (100 - 1)/*автосброс*/
#define TIM_MODE_PWR1 (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)/*TIM1 and TIM8 capture/compare mode register 1 (TIMx_CCMR1)*/
/*structures*/
typedef struct
{
	uint8_t pwr_on; /*Указывает состояние вкл-выкл*/
	TIM_TypeDef* TIMx;  /*Указывает настраиваемые таймер TIM_TypeDef*/
	uint8_t fill_Factor; /*значение Коэффициента заполнения*/
	uint16_t step_temp; /*значение ограничения по заполнению*/
	
} PWR_Structure;

/*var*/

/*func*/
void Init_Tim_PWR(PWR_Structure* pwr);
void Enable_Periphery_PWR(PWR_Structure* pwr);
void Enable_GPIO_PWR(void);
void Replace_Fill_Factor(PWR_Structure* pwr);

#endif
