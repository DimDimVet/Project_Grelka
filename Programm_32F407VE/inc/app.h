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
#include "logic_ADC_PWR.h"


/*defaines*/
#define SSD1306_I2C_ADDR 0x78 /*адрес I2C экрана*/

#define STEP_VOL 5
#define MAX_STEP_TEMP 180
#define MIN_STEP_TEMP 50

/*structures*/

/*var*/

/*func*/

void Handler_ADC_Event(uint16_t adcData, float adcVoltage);

#endif