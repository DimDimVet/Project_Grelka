#include "PWR.h"

void Init_Tim_PWR(PWR_Structure* pwr)
{
		Enable_Periphery_PWR(pwr);
		Enable_GPIO_PWR();
    /*Устанавливаем предделитель и авто-перезагрузку*/
    Write_REG(pwr->TIMx->PSC,TIM_PRESCALE); /*делитель TIM prescaler*/
    Write_REG(pwr->TIMx->ARR,COUNT_RESET); /*автосброс*/

    /*ШИМ TIM3_CH1 PA6*/
    Write_REG(pwr->TIMx->CCR1,pwr->fill_Factor); /*Коэффициент заполнения*/
    ENABLE_BIT(pwr->TIMx->CCMR1,TIM_MODE_PWR1); /*режим ШИМ TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1*/

    ENABLE_BIT(pwr->TIMx->CCMR1, TIM_CCMR1_OC1PE);/*включен регистр предварительной загрузки*/
    ENABLE_BIT(pwr->TIMx->CCER, TIM_CCER_CC1E); /*включаем TIM3_CH1*/

    ENABLE_BIT(pwr->TIMx->CR1, TIM_CR1_CEN);/*Запуск таймера*/
}

void Replace_Fill_Factor(PWR_Structure* pwr)
{
	Write_REG(pwr->TIMx->CCR1,pwr->fill_Factor); /*Коэффициент заполнения*/
}

void Enable_Periphery_PWR(PWR_Structure* pwr)
{
	AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);/*выход PWR для TIM3*/
	
	if(pwr->TIMx == TIM1){APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM1EN);return;}
	if(pwr->TIMx == TIM8){APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM8EN);return;}
	if(pwr->TIMx == TIM9){APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM9EN);return;}
	if(pwr->TIMx == TIM10){APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM10EN);return;}
	if(pwr->TIMx == TIM11){APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM11EN);return;}
	
	if(pwr->TIMx == TIM2){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM2EN);return;}
	if(pwr->TIMx == TIM3){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM3EN);return;}
	if(pwr->TIMx == TIM4){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM4EN);return;}
	if(pwr->TIMx == TIM5){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM5EN);return;}
	if(pwr->TIMx == TIM6){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM6EN);return;}
	if(pwr->TIMx == TIM7){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM7EN);return;}
	if(pwr->TIMx == TIM12){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM12EN);return;}
	if(pwr->TIMx == TIM13){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM13EN);return;}
	if(pwr->TIMx == TIM14){APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM14EN);return;}

}

void Enable_GPIO_PWR()
{
	  GPIO_Structure pwr_6 = {.GPIOx = GPIOA,.Pin = PIN6,.Mode = GPIO_MODE_AF,.Speed = GPIO_SPEED_LOW,.Alternate = GPIO_AF2};
    GPIO_Init(&pwr_6);
}

