#include "RCC.h"

int flHSE,flHSI=0;
//
int isHSE()
{
    return flHSE;
}

int isHSI()
{
    return flHSI;
}

void RCC_INIT()
{
    int countStartHSE;
    START_HSE();

    for (countStartHSE = 0;; countStartHSE++)
    {
        if (READY_HSE())//проверяем готовность HSE
        {
            CONFIG_PLL(8,192,2);//PLLM=(HSE/8),PLLN=(HSE * 192),PLLP = 6
            START_PLL();

            if(READY_PLL())//проверяем готовность PLL
            {
                CONFIG_SYSCLK_SWITCH(RCC_CFGR_SW_PLL); // Установить свитч в PLL как системный такт

                if(READY_SYSCLK_SWITCH())//Проверяем свитч в PLL
                {
                    flHSE=TRUE;
                    flHSI=FALSE;
                    break;
                }
            }
        }

        //переполнение счетчика countStartHSE
        if (countStartHSE > 0x1000)//возврат на HSI
        {
            flHSI=TRUE;
            flHSE=FALSE;
            STOP_HSE(); // Останавливаем HSE
            break;
        }
    }
}

void START_HSE()
{
    RCC->CR|=RCC_CR_HSEON;//запуск HSE
}

void STOP_HSE()
{
    RCC->CR &= ~RCC_CR_HSEON;//останов HSE
}

int READY_HSE()
{
    return(RCC->CR & RCC_CR_HSERDY);//опросим RCC_CR_HSERDY
}

void CONFIG_PLL(int mDivider,int nMultiplier,int pDivider)
{
    RCC->PLLCFGR = 0; // Сброс настроек PLL
    RCC->PLLCFGR |= (mDivider << RCC_PLLCFGR_PLLM_Pos); // M-Делитель PLLM=(HSE/y)
    RCC->PLLCFGR |= (nMultiplier << RCC_PLLCFGR_PLLN_Pos); // N-Умножение PLLN=(HSE * x)
    RCC->PLLCFGR |= (pDivider << RCC_PLLCFGR_PLLP_Pos); // P-Делить PLLP=z
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; // Источник PLL = HSE
}

void START_PLL()
{
    RCC->CR |= RCC_CR_PLLON;//запуск PLL
}

int READY_PLL()
{
    return(RCC->CR & RCC_CR_PLLRDY);//опросим RCC_CR_PLLRDY
}

void CONFIG_SYSCLK_SWITCH(int itemSwitch)
{
    RCC->CFGR |= itemSwitch;
}

int READY_SYSCLK_SWITCH()
{
    return(RCC->CFGR & RCC_CFGR_SWS_PLL);//опросим RCC_CFGR_SWS_PLL
}
//
void AHB1_INIT_PERIPHERY(int RCC_PERIPHERY)
{
    RCC->AHB1ENR |=RCC_PERIPHERY;
}

void APB1_INIT_PERIPHERY(int RCC_PERIPHERY)
{
    RCC->APB1ENR |=RCC_PERIPHERY;
}

void APB2_INIT_PERIPHERY(int RCC_PERIPHERY)
{
    RCC->APB2ENR |= RCC_PERIPHERY;
}
