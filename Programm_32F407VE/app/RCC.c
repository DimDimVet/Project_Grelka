#include "RCC.h"

/*includes*/

/*defaines*/

/*structures*/

/*var*/

/*func*/

void RCC_Init(RCC_Structure* rcc)
{
    int countStartHSE;
    START_HSE;

    for (countStartHSE = 0;; countStartHSE++)
    {
        if (READY_HSE)/*проверяем готовность HSE*/
        {
            Config_PLL(rcc);/*PLLM=(HSE/8),PLLN=(HSE * 192),PLLP = 6*/
            START_PLL;

            if(READY_PLL)/*проверяем готовность PLL*/
            {
                CONFIG_SYSCLK_SWITCH(RCC_CFGR_SW_PLL);/*Установить свитч в PLL как системный такт*/ 

                if(READY_SYSCLK_SWITCH)/*Проверяем свитч в PLL*/
                {
                    break;
                }
            }
        }
				/*переполнение счетчика countStartHSE*/
        if (countStartHSE > 0x1000)/*возврат на HSI*/
        {
            STOP_HSE;/*Останавливаем HSE*/
            break;
        }
    }
}

void Config_PLL(RCC_Structure* rcc)
{
    RCC->PLLCFGR = 0;/*Сброс настроек PLL*/
    RCC->PLLCFGR |= (rcc->mDivider_PLLM << RCC_PLLCFGR_PLLM_Pos);/*M-Делитель PLLM=(HSE/y)*/
    RCC->PLLCFGR |= (rcc->nMultiplier_PLLN << RCC_PLLCFGR_PLLN_Pos);/*N-Умножение PLLN=(HSE * x)*/
    RCC->PLLCFGR |= (rcc->pDivider_PLLP << RCC_PLLCFGR_PLLP_Pos);/*P-Делить PLLP=z*/
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;/*Источник PLL = HSE*/
}

