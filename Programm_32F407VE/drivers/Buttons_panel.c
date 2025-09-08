/*includes*/
#include "Buttons_panel.h"

/*defaines*/

/*structures*/

/*var*/

/*func*/

void Buttons_Init(Butt_Panel_Structure* buttons)
{
  for (int i = 0; i < buttons->buttons_count; i++)
    {
      buttons->pin_butt[i].Mode = GPIO_MODE_INPUT;
      buttons->pin_butt[i].Pull = GPIO_PUPDR_PULLDOWN;

      Enable_Periphery_Button(&buttons->pin_butt[i]);

      GPIO_Init(&buttons->pin_butt[i]);

      Enable_EXTI_Button(&buttons->pin_butt[i]);

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
  if (GPIO_Str->GPIOx == GPIOA)
    {
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
      return;
    }

  if (GPIO_Str->GPIOx == GPIOB)
    {
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
      return;
    }

  if (GPIO_Str->GPIOx == GPIOC)
    {
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOCEN);
      return;
    }

  if (GPIO_Str->GPIOx == GPIOD)
    {
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIODEN);
      return;
    }

  if (GPIO_Str->GPIOx == GPIOE)
    {
      AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);
      return;
    }
}

void Enable_EXTI_Button(GPIO_Structure *GPIO_Str)
{

  uint8_t arr_reg;

  if ((GPIO_Str->Pin == PIN0) || (GPIO_Str->Pin == PIN1) || (GPIO_Str->Pin == PIN2) || (GPIO_Str->Pin == PIN3))
    {
      arr_reg = 0U;
    }

  if ((GPIO_Str->Pin == PIN4) || (GPIO_Str->Pin == PIN5) || (GPIO_Str->Pin == PIN6) || (GPIO_Str->Pin == PIN7))
    {
      arr_reg = 1U;
    }

  if ((GPIO_Str->Pin == PIN8) || (GPIO_Str->Pin == PIN9) || (GPIO_Str->Pin == PIN10) || (GPIO_Str->Pin == PIN11))
    {
      arr_reg = 2U;
    }

  if ((GPIO_Str->Pin == PIN12) || (GPIO_Str->Pin == PIN13) || (GPIO_Str->Pin == PIN14) || (GPIO_Str->Pin == PIN15))
    {
      arr_reg = 3U;
    }

  Set_Buttons_EXTI(arr_reg, GPIO_Str);

  ENABLE_BIT(EXTI->IMR, 1U << GPIO_Str->Pin);
  ENABLE_BIT(EXTI->RTSR, 1U << GPIO_Str->Pin);/*по фронту триггера, или по спаду FTSR*/

  Enable_Buttons_NVIC(GPIO_Str);

}

void Set_Buttons_EXTI(uint8_t arr_reg, GPIO_Structure *GPIO_Str)
{
  uint8_t port_pos_tmp;
  uint16_t SYSCFG_tmp;

  /*назначим позицию порта*/
  if (GPIO_Str->GPIOx == GPIOA)
    {
      port_pos_tmp = 0U;
    }

  if (GPIO_Str->GPIOx == GPIOB)
    {
      port_pos_tmp = 1U;
    }

  if (GPIO_Str->GPIOx == GPIOC)
    {
      port_pos_tmp = 2U;
    }

  if (GPIO_Str->GPIOx == GPIOD)
    {
      port_pos_tmp = 3U;
    }

  if (GPIO_Str->GPIOx == GPIOE)
    {
      port_pos_tmp = 4U;
    }

  /*назначим бит на позицию*/
  if ((GPIO_Str->Pin == PIN0) || (GPIO_Str->Pin == PIN4) || (GPIO_Str->Pin == PIN8) || (GPIO_Str->Pin == PIN12))
    {
      SYSCFG_tmp = port_pos_tmp << 0U;/*0x0001*/
    }

  if ((GPIO_Str->Pin == PIN1) || (GPIO_Str->Pin == PIN5) || (GPIO_Str->Pin == PIN9) || (GPIO_Str->Pin == PIN13))
    {
      SYSCFG_tmp =  port_pos_tmp << 4U;/*0x0010*/
    }

  if ((GPIO_Str->Pin == PIN2) || (GPIO_Str->Pin == PIN6) || (GPIO_Str->Pin == PIN10) || (GPIO_Str->Pin == PIN14))
    {
      SYSCFG_tmp = port_pos_tmp << 8U;/*0x0100*/
    }

  if ((GPIO_Str->Pin == PIN3) || (GPIO_Str->Pin == PIN7) || (GPIO_Str->Pin == PIN11) || (GPIO_Str->Pin == PIN15))
    {
      SYSCFG_tmp = port_pos_tmp << 12U;/*0x1000*/
    }

  ENABLE_BIT(SYSCFG->EXTICR[arr_reg], SYSCFG_tmp);
}

/*подключим прерывание*/
void Enable_Buttons_NVIC(GPIO_Structure *GPIO_Str)
{
  if (GPIO_Str->Pin == PIN0)
    {
      NVIC_EnableIRQ(EXTI0_IRQn);
    }

  if (GPIO_Str->Pin == PIN1)
    {
      NVIC_EnableIRQ(EXTI1_IRQn);
    }

  if (GPIO_Str->Pin == PIN2)
    {
      NVIC_EnableIRQ(EXTI2_IRQn);
    }

  if (GPIO_Str->Pin == PIN3)
    {
      NVIC_EnableIRQ(EXTI3_IRQn);
    }

  if (GPIO_Str->Pin == PIN4)
    {
      NVIC_EnableIRQ(EXTI4_IRQn);
    }

  if ((GPIO_Str->Pin == PIN5) || (GPIO_Str->Pin == PIN6) || (GPIO_Str->Pin == PIN7) || (GPIO_Str->Pin == PIN8) || (GPIO_Str->Pin == PIN9))
    {
      NVIC_EnableIRQ(EXTI9_5_IRQn);
    }

  if ((GPIO_Str->Pin == PIN10) || (GPIO_Str->Pin == PIN11) || (GPIO_Str->Pin == PIN12) || (GPIO_Str->Pin == PIN13) || (GPIO_Str->Pin == PIN14) || (GPIO_Str->Pin == PIN15))
    {
      NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
}


//IRQ
void EXTI0_IRQHandler()
{

  if (Read_BIT(EXTI->PR, EXTI_PR_PR0)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR0); /*reset флага*/
      Start_Event_Buttons_panel("0", 0);
    }
}

void EXTI1_IRQHandler()
{

  if (Read_BIT(EXTI->PR, EXTI_PR_PR1)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR1); /*reset флага*/
      Start_Event_Buttons_panel("1", 0);
    }
}

void EXTI2_IRQHandler()
{
  if (Read_BIT(EXTI->PR, EXTI_PR_PR2)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR2); /*reset флага*/
      Start_Event_Buttons_panel("2", 0);
    }
}

/*резерв, использую на встроеных кнопках*/
//void EXTI3_IRQHandler()
//{
//  if (Read_BIT(EXTI->PR, EXTI_PR_PR3)) /*проверим флаг irq*/
//    {
//      ENABLE_BIT(EXTI->PR, EXTI_PR_PR3); /*reset флага*/
//      Start_Event_Buttons_panel("3", 0);
//    }
//}

//void EXTI4_IRQHandler()
//{
//  if (Read_BIT(EXTI->PR, EXTI_PR_PR4)) /*проверим флаг irq*/
//    {
//      ENABLE_BIT(EXTI->PR, EXTI_PR_PR4); /*reset флага*/
//      Start_Event_Buttons_panel("4", 0);
//    }
//}

void EXTI9_5_IRQHandler()
{

  if (Read_BIT(EXTI->PR, EXTI_PR_PR5)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR5); /*reset флага*/
      Start_Event_Buttons_panel("5", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR6)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR6); /*reset флага*/
      Start_Event_Buttons_panel("6", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR7)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR7); /*reset флага*/
      Start_Event_Buttons_panel("7", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR8)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR8); /*reset флага*/
      Start_Event_Buttons_panel("8", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR9)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR9); /*reset флага*/
      Start_Event_Buttons_panel("9", 0);

    }
}

void EXTI15_10_IRQHandler()
{
  if (Read_BIT(EXTI->PR, EXTI_PR_PR10)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR10); /*reset флага*/
      Start_Event_Buttons_panel("10", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR11)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR11); /*reset флага*/
      Start_Event_Buttons_panel("11", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR12)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR12); /*reset флага*/
      Start_Event_Buttons_panel("12", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR13)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR13); /*reset флага*/
      Start_Event_Buttons_panel("13", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR14)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR14); /*reset флага*/
      Start_Event_Buttons_panel("14", 0);
    }

  if (Read_BIT(EXTI->PR, EXTI_PR_PR15)) /*проверим флаг irq*/
    {
      ENABLE_BIT(EXTI->PR, EXTI_PR_PR15); /*reset флага*/
      Start_Event_Buttons_panel("15", 0);
    }
}


