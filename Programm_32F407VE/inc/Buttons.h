#ifndef BUTTONS_H_
#define BUTTONS_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"
#include "PWR.h"

/*defaines*/

/*structures*/

/*var*/

/*func*/
void Init_Buttons(void);
void KeyConfigInPin(void);
void LedConfigOutPin(void);
void Handler_Key0(void);
void Handler_Key1(void);
#endif