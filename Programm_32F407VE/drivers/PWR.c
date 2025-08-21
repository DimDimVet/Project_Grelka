#include "PWR.h"

int countFillFactor=0;


//void AHB1_INIT_PERIPHERY(int RCC_PERIPHERY)
//{
//    RCC->AHB1ENR |=RCC_PERIPHERY;
//}

//void APB1_INIT_PERIPHERY(int RCC_PERIPHERY)
//{
//    RCC->APB1ENR |=RCC_PERIPHERY;
//}

//void APB2_INIT_PERIPHERY(int RCC_PERIPHERY)
//{
//    RCC->APB2ENR |= RCC_PERIPHERY;
//}

void EXE_TASK4()
{
    RCC_INIT();

    APB2_INIT_PERIPHERY(RCC_APB2ENR_SYSCFGEN);

    APB1_INIT_PERIPHERY(RCC_APB1ENR_TIM3EN);
    AHB1_INIT_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
    AHB1_INIT_PERIPHERY(RCC_AHB1ENR_GPIOEEN);

    GPIO_InitX();
		OdrGPIOA_Or(GPIO_ODR_OD7);
		
    AFRL_GPIOA(GPIO_MODER_MODER6,GPIO_MODER_MODER6_1, 2, 6);
    //INIT_TIM_PWR();
    INIT_EXTI();

}

void INIT_TIM_PWR(int fillFactor)
{
    // Устанавливаем предделитель и авто-перезагрузку
    TIM3->PSC = 8400 - 1; // делитель
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

        //OdrGPIOA_Xor(GPIO_ODR_OD7);
        countFillFactor+=2;
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
void KeyConfigInPin()
{
	GPIOE->MODER &= ~ (GPIO_MODER_MODER3|GPIO_MODER_MODER4); // сброс режима входа-выхода 
	GPIOE->PUPDR |= (GPIO_PUPDR_PUPD3_0|GPIO_PUPDR_PUPD4_0); // установка подтяжки к 0 
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
    GPIOA->MODER &= ~ (GPIO_MODER_MODER6|GPIO_MODER_MODER7); // сброс
    GPIOA->MODER |= (GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0);//режим на выход
    GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED6|GPIO_OSPEEDR_OSPEED7); // сброс скорости
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6_0|GPIO_OSPEEDR_OSPEED7_0); // установка средней скорости
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD6|GPIO_PUPDR_PUPD7); // сброс режим подтяжки
    GPIOA->PUPDR |= (GPIO_PUPDR_PUPD6_0|GPIO_PUPDR_PUPD7_0); // установка подтяжки к + (1)  РА0
    GPIOA->OTYPER &= ~ (GPIO_OTYPER_OT6|GPIO_OTYPER_OT7); // сброс режима нагрузки
    GPIOA->OTYPER |= (GPIO_OTYPER_OT6|GPIO_OTYPER_OT7); // установка в режим с открытым коллектором
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

