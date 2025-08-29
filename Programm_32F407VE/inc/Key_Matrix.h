#ifndef KEY_MATRIX_H_
#define KEY_MATRIX_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "GPIO.h"
#include "RCC.h"

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


#endif