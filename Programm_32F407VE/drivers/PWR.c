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
		APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM3EN);/*TIM2-TIM7,TIM12-TIM14*/
//		if((pwr->rcc_TIMEN) == (RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN |
//														RCC_APB1ENR_TIM4EN | RCC_APB1ENR_TIM5EN |
//														RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN))
//		{
//			APB1_ENABLE_PERIPHERY(pwr->rcc_TIMEN);/*TIM2-TIM7,TIM12-TIM14*/
//		}
//		else
//		{
//			APB2_ENABLE_PERIPHERY(pwr->rcc_TIMEN);/*TIM1,TIM8-TIM11*/
//		}

    AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);/*выход PWR для TIM3*/
}

void Enable_GPIO_PWR()
{
	  GPIO_Structure pwr_6 = {.GPIOx = GPIOA,.Pin = PIN6,.Mode = GPIO_MODE_AF,.Speed = GPIO_SPEED_LOW,.Alternate = GPIO_AF2};
    GPIO_Init(&pwr_6);
}

