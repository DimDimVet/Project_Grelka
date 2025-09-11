#ifndef BUTTONS_PANEL_H_
#define BUTTONS_PANEL_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "events.h"
#include "GPIO.h"
#include "RCC.h"
#include "ADC.h"
#include "flash_F407.h"
#include "setup_flash_F407.h"
/*defaines*/


/*structures*/
typedef struct
{
  uint8_t buttons_count;
  GPIO_Structure *pin_butt; /*кнопки вход*/
  GPIO_Structure *pin_com; /*пин выход притянутый*/

} Butt_Panel_Structure;

/*var*/

/*func*/
void Buttons_Init(Butt_Panel_Structure* buttons);
void Enable_Periphery_Button(GPIO_Structure *GPIO_Str);
/*настройки прерывания*/
void Enable_EXTI_Button(GPIO_Structure *GPIO_Str);
void Set_Buttons_EXTI(uint8_t arr_reg, GPIO_Structure *GPIO_Str);
void Enable_Buttons_NVIC(GPIO_Structure *GPIO_Str);

void Event_Buttons_panel(uint8_t pin);

#endif