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

void GPIO_InitX(void);
//
void InPin(void);
void KeyConfigInPin(void);
//
void OutPin(void);
void LedConfigOutPin(void);
//
void AFRH_GPIOA(int resetBit,int setBit, int AFx, int PAx);
void AFRL_GPIOA(int resetBit,int setBit, int AFx, int PAx);
void AFRL_GPIOB(int resetBit,int setBit, int AFx, int PBx);
//
void OdrGPIOA_Xor(int PAx);
void OdrGPIOA_Or(int PAx);

#endif