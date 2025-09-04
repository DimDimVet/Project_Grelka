/*includes*/
#include "Buttons_panel.h"

/*defaines*/

/*structures*/

/*var*/

/*func*/

void Buttons_Init(Butt_Panel_Structure* buttons)
{
    for (int i=0; i < buttons->buttons_count; i++)
    {
        buttons->pin_butt[i].Mode = GPIO_MODE_INPUT;
        buttons->pin_butt[i].Pull = GPIO_PUPDR_PULLDOWN;

        Enable_Periphery_Button(&buttons->pin_butt[i]);

        GPIO_Init(&buttons->pin_butt[i]);
        delay_ms(1);
    }

    buttons->pin_com->Mode = GPIO_MODE_OUTPUT;
    buttons->pin_com->Speed = GPIO_SPEED_LOW;
    buttons->pin_com->Otyper = GPIO_OTYPER_PUSHPULL;
    buttons->pin_com->Pull = GPIO_PUPDR_NOPULL;

    Enable_Periphery_Button(buttons->pin_com);

    GPIO_Init(buttons->pin_com);
		
		ODR_1(buttons->pin_com);
		
    delay_ms(1);
}

void Enable_Periphery_Button(GPIO_Structure *GPIO_Str)
{
    /*RM0090 Reference manual на STM32F407/417*/
    if(GPIO_Str->GPIOx == GPIOA)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
        return;
    }

    if(GPIO_Str->GPIOx == GPIOB)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
        return;
    }
    if(GPIO_Str->GPIOx == GPIOC)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOCEN);
        return;
    }

    if(GPIO_Str->GPIOx == GPIOD)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIODEN);
        return;
    }

    if(GPIO_Str->GPIOx == GPIOE)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);
        return;
    }
}
//думаю
void Enable_EXTI_Button(GPIO_Structure *GPIO_Str)
{
	  if(GPIO_Str->Pin == PIN0)
    {
			ENABLE_BIT(SYSCFG->EXTICR[0],SYSCFG_EXTICR1_EXTI0);/*cвязка PB15 с EXTI*/
			ENABLE_BIT(EXTI->IMR,EXTI_IMR_MR15);/*Разрешение irq*/
			ENABLE_BIT(EXTI->FTSR,EXTI_FTSR_TR15);/*Прерывание по спаду*/
			NVIC_EnableIRQ(EXTI4_IRQn);
        return;
    }
	
	ENABLE_BIT(SYSCFG->EXTICR[3],SYSCFG_EXTICR4_EXTI15_PB);/*cвязка PB15 с EXTI*/
  ENABLE_BIT(EXTI->IMR,EXTI_IMR_MR15);/*Разрешение irq*/
  ENABLE_BIT(EXTI->FTSR,EXTI_FTSR_TR15);/*Прерывание по спаду*/
  NVIC_EnableIRQ(EXTI4_IRQn);
	
	
}