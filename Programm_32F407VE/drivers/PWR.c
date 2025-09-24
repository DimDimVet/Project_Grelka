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
	if((pwr->pwr_on) == 1)
	{
		Write_REG(pwr->TIMx->CCR1,pwr->fill_Factor); /*Коэффициент заполнения*/
	}
	else
	{
		Write_REG(pwr->TIMx->CCR1,0); /*Коэффициент заполнения*/
	}
    
}

void Enable_Periphery_PWR(PWR_Structure* pwr)
{
    /*RM0090 Reference manual на STM32F407/417*/
    if(pwr->TIMx == TIM1)
    {
        APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM1EN);		/*GPIOA,GPIOE*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);
        return;
    }

    if(pwr->TIMx == TIM8)
    {
        APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM8EN);    /*GPIOA,GPIOB,GPIOC*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOCEN);
				return;
    }
    if(pwr->TIMx == TIM9)
    {
        APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM9EN);    /*GPIOA,GPIOE*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);
				return;
    }
    if(pwr->TIMx == TIM10)
    {
        APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM10EN);    /*GPIOB,GPIOF*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOFEN);
				return;
    }
    if(pwr->TIMx == TIM11)
    {
        APB2_ENABLE_PERIPHERY(RCC_APB2ENR_TIM11EN);    /*GPIOB,GPIOF*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOFEN);
				return;
    }

    if(pwr->TIMx == TIM2)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM2EN);    /*GPIOA,GPIOB*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				return;
    }
    if(pwr->TIMx == TIM3)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM3EN);    /*GPIOA,GPIOB,GPIOC*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOCEN);
				return;
    }
    if(pwr->TIMx == TIM4)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM4EN);    /*GPIOB,GPIOD*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIODEN);
				return;
    }
    if(pwr->TIMx == TIM5)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM5EN);    /*GPIOA,GPIOH*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOHEN);
				return;
    }
    if(pwr->TIMx == TIM12)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM12EN);    /*GPIOB*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				return;
    }
    if(pwr->TIMx == TIM13)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM13EN);    /*GPIOA,GPIOF*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOFEN);
				return;
    }
    if(pwr->TIMx == TIM14)
    {
        APB1_ENABLE_PERIPHERY(RCC_APB1ENR_TIM14EN);    /*GPIOA,GPIOF*/
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOFEN);
				return;
    }

}

void Enable_GPIO_PWR()
{
    GPIO_Structure pwr_6 = {.GPIOx = GPIOA,.Pin = PIN6,.Mode = GPIO_MODE_AF,.Speed = GPIO_SPEED_LOW,.Alternate = GPIO_AF2};
    GPIO_Init(&pwr_6);
}

