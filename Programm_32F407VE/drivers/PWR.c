#include "PWR.h"

int countFillFactor=0;
GPIO_Structure LED_7 = {.GPIOx = GPIOA,.Pin = PIN7,.Mode = GPIO_MODE_OUTPUT,.Speed = GPIO_SPEED_LOW,.Otyper = GPIO_OTYPER_PUSHPULL,.Pull = GPIO_PUPDR_PULLUP};

void EXE_TASK4()
{

    KeyConfigInPin();
		LedConfigOutPin();

		GPIO_Structure pwr_6 = {.GPIOx = GPIOA,.Pin = PIN6,.Mode = GPIO_MODE_AF,.Speed = GPIO_SPEED_LOW,.Alternate = GPIO_AF2};
	  GPIO_Init(&pwr_6);

    INIT_EXTI();

}

void INIT_TIM_PWR(int fillFactor)
{
    // Устанавливаем предделитель и авто-перезагрузку
    TIM3->PSC = 8400 - 1; // делитель TIM prescaler
    TIM3->ARR = 100 - 1; // автосброс

    //ШИМ TIM3_CH1 PA6
    TIM3->CCR1 = fillFactor; // Коэффициент заполнения
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // режим ШИМ

    TIM3->CCMR1 |= TIM_CCMR1_OC1PE; // включен регистр предварительной загрузки
    TIM3->CCER |= TIM_CCER_CC1E; // включаем TIM3_CH1

    // Запуск таймера
    TIM3->CR1 |= TIM_CR1_CEN;
}

void INIT_EXTI()
{
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PE; // cвязка PE4 с EXTI
    EXTI->IMR |= EXTI_IMR_MR4; // Разрешение irq
    EXTI->FTSR |= EXTI_FTSR_TR4; // Прерывание на спад
		
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PE; // cвязка PE4 с EXTI
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

				ODR_Xor(&LED_7);
        countFillFactor+=25;
        if(countFillFactor<=100)
        {
            INIT_TIM_PWR(countFillFactor);
        }
        else
        {
            countFillFactor=0;
            INIT_TIM_PWR(countFillFactor);
        }
    }
}

void EXTI3_IRQHandler()
{

if (EXTI->PR & EXTI_PR_PR3)   // проверим флаг irq
    {
        EXTI->PR |= EXTI_PR_PR3; // reset флага

        ODR_Xor(&LED_7);
        countFillFactor+=10;
        if(countFillFactor<=100)
        {
            INIT_TIM_PWR(countFillFactor);
        }
        else
        {
            countFillFactor=0;
            INIT_TIM_PWR(countFillFactor);
        }
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
	//GPIO_Structure LED_7 = {.GPIOx = GPIOA,.Pin = PIN7,.Mode = GPIO_MODE_OUTPUT,.Speed = GPIO_SPEED_LOW,.Pull = GPIO_PUPDR_PULLUP};
	GPIO_Init(&LED_7);
}
