#include "Buttons.h"

void Init_Buttons()
{
		AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);/*выход LED*/
		APB2_ENABLE_PERIPHERY(RCC_APB2ENR_SYSCFGEN);
		KeyConfigInPin();
		
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PE; // cвязка PE4 с EXTI
    EXTI->IMR |= EXTI_IMR_MR4; // Разрешение irq
    EXTI->FTSR |= EXTI_FTSR_TR4; // Прерывание на спад
		
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PE; // cвязка PE3 с EXTI
    EXTI->IMR |= EXTI_IMR_MR3; // Разрешение irq
    EXTI->FTSR |= EXTI_FTSR_TR3; // Прерывание на спад
 
    NVIC_EnableIRQ(EXTI4_IRQn);
		NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI4_IRQHandler()
{

if (EXTI->PR & EXTI_PR_PR4)   // проверим флаг irq
    {
        EXTI->PR |= EXTI_PR_PR4; // reset флага
				Handler_Key0();
//				ODR_Xor(&LED_7);
//        countFillFactor+=10;
//        if(countFillFactor<=100)
//        {
//            INIT_TIM_PWR(countFillFactor);
//        }
//        else
//        {
//            countFillFactor=0;
//            INIT_TIM_PWR(countFillFactor);
//        }
    }
}

void EXTI3_IRQHandler()
{

if (EXTI->PR & EXTI_PR_PR3)   // проверим флаг irq
    {
        EXTI->PR |= EXTI_PR_PR3; // reset флага
				Handler_Key1();
//        ODR_Xor(&LED_7);
//        countFillFactor+=10;
//        if(countFillFactor<=100)
//        {
//            INIT_TIM_PWR(countFillFactor);
//        }
//        else
//        {
//            countFillFactor=0;
//            INIT_TIM_PWR(countFillFactor);
//        }
    }
}

//Key0 PE4 3pin
//Key1 PE3 2pin
void KeyConfigInPin()
{
	GPIO_Structure key_PE3 = {.GPIOx = GPIOE,.Pin = PIN3,.Mode = GPIO_MODE_INPUT,.Pull = GPIO_PUPDR_PULLUP};
	GPIO_Init(&key_PE3);
	GPIO_Structure key_PE4 = {.GPIOx = GPIOE,.Pin = PIN4,.Mode = GPIO_MODE_INPUT,.Pull = GPIO_PUPDR_PULLUP};
	GPIO_Init(&key_PE4);
}

// LED2 PA6 31pin
// LED3 PA7 32pin
void LedConfigOutPin()
{
	AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
	
	GPIO_Structure LED_7 = {.GPIOx = GPIOA,.Pin = PIN7,.Mode = GPIO_MODE_OUTPUT,.Speed = GPIO_SPEED_LOW,.Pull = GPIO_PUPDR_PULLUP};
	GPIO_Init(&LED_7);
}