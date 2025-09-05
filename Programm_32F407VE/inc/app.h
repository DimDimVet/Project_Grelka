#ifndef APP_H_
#define APP_H_

/*includes*/
#include "HEHAL.h"
#include "events.h"
#include "RCC.h"
#include "GPIO.h"
#include "PWR.h"
#include "appointed_Pin.h"
#include "ADC.h"
#include "I2C.h"
#include "ssd1306.h"
#include "Buttons_panel.h"
/*defaines*/

#define SSD1306_I2C_ADDR 0x78 /*адрес I2C экрана*/

/*structures*/

/*var*/

/*func*/

void Handler_Buttons_panel_Event(void *var, int vol);
void Handler_ADC_Event(uint16_t adcData, float adcVoltage);
#endif