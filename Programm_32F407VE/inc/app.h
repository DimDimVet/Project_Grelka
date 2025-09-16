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
#include "usart.h"


/*defaines*/
#define SSD1306_I2C_ADDR 0x78 /*адрес I2C экрана*/

#define STEP_VOL 5
#define MAX_STEP_TEMP 180
#define MIN_STEP_TEMP 50

/*Скорость USART*/
#define BAUND_RATE 9600
/*Размер буфера USART*/
#define SIZE_BUFF_USART 36
/*новая строка*/
#define NEW_STRING_CONSOLE "\r"
/*символ очистки консоли*/
#define CLEAR_CONSOLE "\r\033[K"
/*structures*/

/*var*/
static char receivedChar_;
static char *receivedChar = &receivedChar_;
static char rezultReadConsol[SIZE_BUF_USART];
static char rezultReadI2C[SIZE_BUF_USART];
/*func*/

void Handler_ADC_Event(uint16_t adcData, float adcVoltage);
void Write_Terminal_USART(char *str1, char *str2, char *str3);

#endif