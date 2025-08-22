#include "PWR.h"

int countFillFactor=0;


void EXE_TASK4()
{

    GPIO_InitX();
	
		//OdrGPIOA_Or(GPIO_ODR_OD6);
		
    AFRL_GPIOA(GPIO_MODER_MODER6,GPIO_MODER_MODER6_1, 2, 6);
    //INIT_TIM_PWR();
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

    NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI4_IRQHandler()
{

if (EXTI->PR & EXTI_PR_PR4)   // проверим флаг irq
    {
        EXTI->PR |= EXTI_PR_PR4; // reset флага

        OdrGPIOA_Xor(GPIO_ODR_OD7);
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

void GPIO_InitX()
{
    OutPin();
		InPin();
}

//In
void InPin()
{
    KeyConfigInPin();
}

//Key0 PE4 3pin
//Key1 PE3 2pin
uint32_t tt;
uint32_t tt2;
uint32_t tt3;
void KeyConfigInPin()
{
	GPIO_Structure key_PE3 = {.GPIOx = GPIOE,.Pin = PIN3,.Mode = GPIO_MODE_INPUT,.Pull = GPIO_PULLUP};
	GPIO_Init(&key_PE3);
	GPIO_Structure key_PE4 = {.GPIOx = GPIOE,.Pin = PIN4,.Mode = GPIO_MODE_INPUT,.Pull = GPIO_PULLUP};
	GPIO_Init(&key_PE4);

}
//Out
void OutPin()
{
    LedConfigOutPin();
}

// LED2 PA6 31pin
// LED3 PA7 32pin
void LedConfigOutPin()
{
	GPIO_Structure LED_7 = {.GPIOx = GPIOA,.Pin = PIN7,.Mode = GPIO_MODE_OUTPUT,.Speed = GPIO_SPEED_LOW,.Pull = GPIO_PULLUP};
	GPIO_Init(&LED_7);

}


//Altern
void AFRH_GPIOA(int resetBit,int setBit, int AFx, int PAx)
{
    GPIOA->MODER &= ~resetBit;//сброс
    GPIOA->MODER |= setBit;//установка
    GPIOA->AFR[1] |= (AFx << ((PAx-8) * 4));//выбор функции
}

void AFRL_GPIOA(int resetBit,int setBit, int AFx, int PAx)
{
    GPIOA->MODER &= ~resetBit;//сброс
    GPIOA->MODER |= setBit;//установка
    GPIOA->AFR[0] |= (AFx << (PAx * 4));//выбор функции
}

void AFRL_GPIOB(int resetBit,int setBit, int AFx, int PBx)
{
    GPIOB->MODER &= ~resetBit;//сброс
    GPIOB->MODER |= setBit;//установка
    GPIOB->AFR[0] |= (AFx << (PBx * 4));//выбор функции
}

//побитовые выполнители
void OdrGPIOA_Xor(int PAx)
{
    GPIOA->ODR ^= PAx;
}

void OdrGPIOA_Or(int PAx)
{
    GPIOA->ODR |= PAx;
}

