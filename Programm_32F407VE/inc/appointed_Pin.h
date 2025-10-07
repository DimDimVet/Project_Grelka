#ifndef APPOINTED_PIN_H_
#define APPOINTED_PIN_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"
//#include "PWR.h"

/*defaines*/

/*structures*/
typedef struct
{
	TIM_TypeDef* TIMx;  /*Указывает настраиваемые таймер TIM_TypeDef*/
	uint8_t fill_Factor; /*значение Коэффициента заполнения*/
	
} Button_Structure;

/*var*/

/*func*/
void Init_App_Pin(void);
void Enable_Periphery_App_Pin(void);
void Key_Config_In_Pin(void);
void Led_Config_Out_Pin(void);

void Handler_LED7(void);
//void Handler_Key0(void);
//void Handler_Key1(void);
#endif