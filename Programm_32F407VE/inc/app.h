#ifndef APP_H_
#define APP_H_

/*includes*/
#include "HEHAL.h"
#include "RCC.h"
#include "GPIO.h"
#include "PWR.h"
#include "Buttons.h"
#include "ADC.h"
#include "I2C.h"
#include "ssd1306.h"
/*defaines*/

#define SSD1306_I2C_ADDR 0x78 /*адрес I2C экрана*/

/*structures*/

/*var*/

/*func*/
void Init_PWR(void);

#endif