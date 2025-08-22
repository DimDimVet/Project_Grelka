#ifndef GPIO_H_
#define GPIO_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"

/*defaines*/

/*номера пинов*/
#define PIN0                 0  
#define PIN1                 1  
#define PIN2                 2  
#define PIN3                 3  
#define PIN4                 4  
#define PIN5                 5  
#define PIN6                 6  
#define PIN7                 7  
#define PIN8                 8  
#define PIN9                 9  
#define PIN10                10  
#define PIN11                11  
#define PIN12                12  
#define PIN13                13  
#define PIN14                14  
#define PIN15                15  

/*RM0090 Reference manual STM32F405/415, STM32F407/417, STM32F427/437 and STM32F429/439*/
/*8.4 GPIO registers*/
/*8.4.1 Регистр режимов (GPIOx_MODER) (x = A..I/J/K) Address offset: 0x00*/
#define GPIO_MODE_INPUT (0) /*Input (reset state)*/
#define GPIO_MODE_OUTPUT (1) /*General purpose output mode*/
#define GPIO_MODE_AF (2) /*Alternate function mode*/
#define GPIO_MODE_ANALOG (3) /*Analog mode*/

/*8.4.2 Регистр типа выхода порта GPIO (GPIOx_OTYPER)(x = A..I/J/K) Address offset: 0x04*/
#define GPIO_OUTPUT_TYPE_Pos 0x04
#define GPIO_OUTPUT_PP (0) /*Output push-pull (reset state)*/
#define GPIO_OUTPUT_OD (1) /*Output open-drain*/
#define GPIO_OUTPUT_TYPE (0x1UL << GPIO_OUTPUT_TYPE_Pos)//temp

/*8.4.3 GPIO port output speed register (GPIOx_OSPEEDR)(x = A..I/J/K) Address offset: 0x08*/
#define GPIO_SPEED_Pos 0x08
#define GPIO_SPEED_LOW (0) /* Low speed*/
#define GPIO_SPEED_MEDIUM (1) /*Medium speed*/
#define GPIO_SPEED_HIGH (2) /*High speed*/
#define GPIO_SPEED_VERY_HIGH (3) /*AVery high speed*/

/*8.4.4 Регистр подтягивания(pull-up)/опускания(pull-down) порта GPIO (GPIOx_PUPDR)(x = A..I/J/K) Address offset: 0x0C*/
#define GPIO_NOPULL (0) /* No pull-up, pull-down*/
#define GPIO_PULLUP (1) /*Pull-up*/
#define GPIO_PULLDOWN (2) /*Pull-down*/

/*8.4.5 Регистр входных данных порта GPIO (GPIOx_IDR) (x = A..I/J/K) Address offset: 0x10*/
/*Эти биты доступны только для чтения и доступны только в режиме слова. Они содержат входное значение соответствующего порта ввода/вывода.*/
#define GPIO_IDR_Pos 0x10
/*#define GPIO_IDR_ID0*/

/*8.4.6 Регистр выходных данных порта GPIO (GPIOx_ODR) (x = A..I/J/K) Address offset: 0x14*/
/*Эти биты могут быть прочитаны и записаны программным обеспечением.*/
#define GPIO_ODR_Pos 0x14
/*#define GPIO_ODR_OD0*/

/*8.4.7 Регистр установки/сброса бита порта GPIO (GPIOx_BSRR) (x = A..I/J/K) Address offset: 0x18*/
/*Эти биты доступны только для записи и могут быть доступны в режиме слова, полуслова или байта. Чтение этих битов возвращает значение 0x0000.*/
#define GPIO_BSRR_Pos 0x18
/*#define GPIO_BSRR_BS0 = 0x1 - установить бит в 1*/
/*#define GPIO_BSRR_BR0 = 0x1 - сбросить бит в 0*/

/*8.4.8 Регистр блокировки конфигурации порта GPIO (GPIOx_LCKR)(x = A..I/J/K) Address offset: 0x1C*/
/*Эти биты доступны только для записи и могут быть доступны в режиме слова, полуслова или байта. Чтение этих битов возвращает значение 0x0000.*/
#define GPIO_LCKR_Pos 0x1C
/*#define GPIO_LCKR_LCKK = 0x1 - заблокировать весь порт. Регистр GPIOx_LCKR заблокирован до сброса микроконтроллера или сброса периферийного устройства.*/
/*#define GPIO_LCKR_LCK0 = 0x1 - заблокировать бит, Эти биты доступны для чтения и записи, но могут быть записаны только тогда, когда бит LCKK равен «0».*/

/*8.4.9 Альтернативная функция GPIO нижнего регистра 0-7 (GPIOx_AFRL) (x = A..I/J/K) Address offset: 0x20*/
#define GPIO_AFRL_AFRL_Pos 0x20
#define GPIO_AFRL_AF0 (0x0 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF1 (0x1 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF2 (0x2 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF3 (0x3 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF4 (0x4 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF5 (0x5 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF6 (0x6 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF7 (0x7 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF8 (0x8 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF9 (0x9 << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF10 (0xA << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF11 (0xB << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF12 (0xC << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF13 (0xD << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF14 (0xE << GPIO_AFRL_Pos)
#define GPIO_AFRL_AF15 (0xF << GPIO_AFRL_Pos)

/*8.4.10 Альтернативная функция GPIO верхнего регистра 8-15 (GPIOx_AFRH)(x = A..I/J) Address offset: 0x24*/
#define GPIO_AFRH_Pos 0x24
#define GPIO_AFRH_AF0 (0x0 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF1 (0x1 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF2 (0x2 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF3 (0x3 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF4 (0x4 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF5 (0x5 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF6 (0x6 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF8 (0x8 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF9 (0x9 << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF10 (0xA << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF11 (0xB << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF12 (0xC << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF13 (0xD << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF14 (0xE << GPIO_AFRH_Pos)
#define GPIO_AFRH_AF15 (0xF << GPIO_AFRH_Pos)

/*var*/

/*structures*/
typedef struct
{
	GPIO_TypeDef* GPIOx;       /*Указывает настраиваемые порт GPIO GPIO_TypeDef*/
	
  uint32_t Pin;       /*Указывает настраиваемые контакты GPIO */

  uint32_t Mode;      /*Задает режим работы для выбранных контактов */

  uint32_t Pull;      /*Задает активацию подтягивания вверх(Pull-up) или опускания(Pull-Down) вниз для выбранных контактов.*/
	
	uint32_t Otyper;    /*Задать выход или открытый коллектор*/

  uint32_t Speed;     /*Задает скорость для выбранных контактов */

  uint32_t Alternate;  /*Периферийное устройство, подключаемое к выбранным контактам */
	
}GPIO_Structure;

/*func*/
void GPIO_Init(GPIO_Structure *GPIO_Str);

#endif