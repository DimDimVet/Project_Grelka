/*includes*/
#include "Key_Matrix.h"

/*defaines*/

/*structures*/

/*var*/

/*func*/
void Key_Init(Key_Structure *Key_Str)
{
	/* Cols: output push-pull */
	for(int i = 0; i < (Key_Str->cols_count);i++)
	{
		Key_Str->pins_col[i].Mode = GPIO_MODE_OUTPUT;
		Key_Str->pins_col[i].Speed = GPIO_SPEED_LOW;
		Key_Str->pins_col[i].Otyper = GPIO_OTYPER_PUSHPULL;
		Key_Str->pins_col[i].Pull = GPIO_PUPDR_NOPULL;
		
		GPIO_Init(&Key_Str->pins_col[i]);
		delay_ms(1);
	}
	
	/* Rows: input, pull-down */
	for(int i = 0; i < (Key_Str->rows_count);i++)
	{
		Key_Str->pins_rows[i].Mode = GPIO_MODE_INPUT;
		Key_Str->pins_col[i].Pull = GPIO_PUPDR_PULLDOWN;
		
		GPIO_Init(&Key_Str->pins_rows[i]);
		delay_ms(1);
	}
	

}