#include "appointed_Pin.h"
/*дефолт.устройства платы*/

GPIO_Structure LED_7 = {.GPIOx = GPIOA,.Pin = PIN7,.Mode = GPIO_MODE_OUTPUT,.Speed = GPIO_SPEED_LOW,.Pull = GPIO_PUPDR_PULLUP};
int tt0,tt2,tt4;
int tt1,tt3,tt5;
void Init_App_Pin()
{
	tt5 = SYSCFG_EXTICR1_EXTI3_Pos;
	tt3 = SYSCFG_EXTICR1_EXTI3;
	tt0 = SYSCFG_EXTICR1_EXTI3_PE;
	
	
	tt4 = SYSCFG_EXTICR2_EXTI4_Pos;
	tt2 = SYSCFG_EXTICR2_EXTI4;
	tt1 = SYSCFG_EXTICR2_EXTI4_PE;
	
	//
  Enable_Periphery_App_Pin();
  
  Key_Config_In_Pin();
	Led_Config_Out_Pin();

	/*Настроим кнопки по прерыванию*/
  ENABLE_BIT(SYSCFG->EXTICR[1],SYSCFG_EXTICR2_EXTI4_PE);/*cвязка PE4 с EXTI*/
  ENABLE_BIT(EXTI->IMR,EXTI_IMR_MR4);/*Разрешение irq*/
  ENABLE_BIT(EXTI->FTSR,EXTI_FTSR_TR4);/*Прерывание по спаду*/

  ENABLE_BIT(SYSCFG->EXTICR[0],SYSCFG_EXTICR1_EXTI3_PE);/*cвязка PE3 с EXTI*/
  ENABLE_BIT(EXTI->IMR,EXTI_IMR_MR3);/*Разрешение irq*/
  ENABLE_BIT(EXTI->FTSR,EXTI_FTSR_TR3);/*Прерывание по спаду*/

  NVIC_EnableIRQ(EXTI3_IRQn);//3
  NVIC_EnableIRQ(EXTI4_IRQn);//4
}

void Enable_Periphery_App_Pin()
{
	APB2_ENABLE_PERIPHERY(RCC_APB2ENR_SYSCFGEN);/*EXTI вкл*/
	AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);/*Key0 PE4, Key1 PE3*/
	AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);/*LED2 PA6,LED3 PA7*/
}

/*Key0 PE4 3pin, Key1 PE3 2pin*/
void Key_Config_In_Pin()
{
  GPIO_Structure key_PE3 = {.GPIOx = GPIOE,.Pin = PIN3,.Mode = GPIO_MODE_INPUT,.Pull = GPIO_PUPDR_PULLUP};
  GPIO_Init(&key_PE3);
  GPIO_Structure key_PE4 = {.GPIOx = GPIOE,.Pin = PIN4,.Mode = GPIO_MODE_INPUT,.Pull = GPIO_PUPDR_PULLUP};
  GPIO_Init(&key_PE4);
}

/*LED2 PA6 31pin, LED3 PA7 32pin*/
void Led_Config_Out_Pin()
{
  GPIO_Init(&LED_7);
}

/*Обработчики*/
void Handler_LED7()
{
	ODR_Xor(&LED_7);
}

void EXTI4_IRQHandler()
{
  if (Read_BIT(EXTI->PR,EXTI_PR_PR4)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR,EXTI_PR_PR4); /*reset флага*/
      //Handler_Key0();
    }
}

void EXTI3_IRQHandler()
{

  if (Read_BIT(EXTI->PR,EXTI_PR_PR3)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR,EXTI_PR_PR3); /*reset флага*/
      //Handler_Key1();
    }
}
