#ifndef RCC_H_
#define RCC_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"

/*defaines*/
#define TRUE 1
#define FALSE 0

/*structures*/

/*var*/

/*func*/
void RCC_INIT(void);
void START_HSE(void);
void STOP_HSE(void);
int READY_HSE(void);
void START_PLL(void);
int READY_PLL(void);
void CONFIG_SYSCLK_SWITCH(int itemSwitch);
int READY_SYSCLK_SWITCH(void);
void CONFIG_PLL(int mDivider,int nMultiplier,int pDivider);
//
void AHB1_INIT_PERIPHERY(int RCC_PERIPHERY);
void APB1_INIT_PERIPHERY(int RCC_PERIPHERY);
void APB2_INIT_PERIPHERY(int RCC_PERIPHERY);

#endif