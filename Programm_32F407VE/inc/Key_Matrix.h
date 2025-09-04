#ifndef KEY_MATRIX_H_
#define KEY_MATRIX_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"
#include "RCC.h"
#include "ADC.h"

/*defaines*/


/*structures*/
typedef struct
{
	uint8_t cols_count;
	uint8_t rows_count;
	/* Cols: output push-pull */
	GPIO_Structure* pins_col; /*пин столбца 1*/
	/* Rows: input, pull-down */
	GPIO_Structure* pins_rows; /*пин строки 1*/

} Key_Structure;

/*var*/

/*func*/
void Key_Init(Key_Structure *Key_Str);
void Enable_Periphery_Key(GPIO_Structure *GPIO_Str);
char* Survey_Key(Key_Structure *Key_Str);

#endif