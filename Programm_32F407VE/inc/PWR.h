#ifndef PWR_H_
#define PWR_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "RCC.h"
#include "GPIO.h"
/*defaines*/

/*structures*/

/*var*/

/*func*/
void EXE_TASK4(void);

void INIT_EXTI(void);
void INIT_TIM_PWR(int fillFactor);

void KeyConfigInPin(void);
void LedConfigOutPin(void);


#endif