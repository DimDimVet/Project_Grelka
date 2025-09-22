#ifndef EVENTS_H_
#define EVENTS_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"
#include "RCC.h"
#include "ADC.h"

/*defaines*/

/*structures*/

/*var*/

/*event var*/
//typedef void (*event_buttons_panel_t)(int vol);
typedef void (*event_ADC_t)(uint16_t adcData, float adcVoltage);
typedef void (*event_buttons_USART_t)(uint16_t vol);

/*event func*/
//void Connect_Event_Buttons_panel(event_buttons_panel_t func);
//void Start_Event_Buttons_panel(int vol);

void Connect_Event_ADC(event_ADC_t func);
void Start_Event_ADC(uint16_t adcData, float adcVoltage);

void Connect_Event_Buttons_USART(event_buttons_USART_t func);
void Start_Event_Buttons_USART(uint16_t vol);

/*func*/


#endif