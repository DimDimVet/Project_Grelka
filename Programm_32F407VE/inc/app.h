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
/*Конец строчного пакета*/
#define STOP_FLAG_USART '#'
/*значение пакета*/
#define BTN_PLUS_FLAG_USART "\nBtnPlus"
#define BTN_MINUS_FLAG_USART "\nBtnMinus"
#define BTN_FLESH_FLAG_USART "\nBtnFlesh"
#define BTN_ON_OFF_FLAG_USART "\nBtnOnOff"

/*новая строка*/
#define NEW_STRING_CONSOLE "\r"
/*символ очистки консоли*/
#define CLEAR_CONSOLE "\r\033[K"
/*structures*/

/*var*/

/*func*/

void Handler_ADC_Event(uint16_t adcData, float adcVoltage);
void Set_Flag_PWR(uint8_t flag);
void Write_To_USART(uint16_t vol, char* flag);
void Read_USART(char ch);
void Decoder_Usart(char *data,uint16_t leght);
uint16_t Comparator_Arr(char* arr1, char* arr2, uint16_t len);

#endif