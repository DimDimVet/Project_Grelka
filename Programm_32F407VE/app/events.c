#include "events.h"

/*события Buttons_panel*/

//event_buttons_panel_t event_buttons_panel;

//void Connect_Event_Buttons_panel(event_buttons_panel_t func)
//{
//	event_buttons_panel = func;
//}

//void Start_Event_Buttons_panel(int vol)
//{
//	 event_buttons_panel(vol);
//}

/*события ADC*/

event_ADC_t event_ADC;

void Connect_Event_ADC(event_ADC_t func)
{
	event_ADC = func;
}

void Start_Event_ADC(uint16_t adcData, float adcVoltage)
{
	 event_ADC(adcData,adcVoltage);
}

/*события Buttons_panel передача в USART*/

event_write_to_USART_t event_write_USART;

void Connect_Event_Write_To_USART(event_write_to_USART_t func)
{
	event_write_USART = func;
}

void Start_Event_Write_To_USART(uint16_t vol, char* flag)
{
	 event_write_USART(vol,flag);
}