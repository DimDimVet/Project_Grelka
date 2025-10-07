#ifndef USART_H_
#define USART_H_

#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "RCC.h"
#include "appointed_Pin.h"

#define SIZE_BUF_USART 10
#define SIZE_BUF_USART_MAX 100
#define SIZE_BUF_INFO 35

void Init_USART1(uint16_t baudRate);
void Enable_RCC_USART1(void);
void Config_GPIO_USART1(void);
void Config_USART1(uint16_t baudRate);

char USART1_ReadChar();
void USART1_SetString(char *str);

/*event для передачи прерываения при чтении usart,*/
typedef void (*event_read_USART_t)(char ch);

void Connect_Event_Read_USART(event_read_USART_t func);
void Start_Event_Read_USART(char ch);

void ExecutorTerminal_USART_Irq(void);
#endif