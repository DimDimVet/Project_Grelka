#include "app.h"

RCC_Structure rcc_str = {.mDivider_PLLM = 8,.nMultiplier_PLLN = 192,.pDivider_PLLP = 6}; /*структура для RCC*/
/*main*/

int main()
{
		RCC_Init(&rcc_str);
		Start_PWR();
	
		EXE_TASK4();//PWR
    /*------------*/
		ADC_Init(ADC1);
    /*------------*/
		

    while (1)
    {
    }
		
    return 0;
}

void Start_PWR()
{
	/*RCC*/
	  APB2_ENABLE_PERIPHERY(RCC_APB2ENR_SYSCFGEN);
    APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM3EN);
	
    AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);/*выход PWR*/
    AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);/*выход LED*/
	
	
}
