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
		
		Enable_Periphery_Key(&Key_Str->pins_col[i]);
		
		GPIO_Init(&Key_Str->pins_col[i]);
		//ODR_1(&Key_Str->pins_col[i]);
		delay_ms(1);
	}

	/* Rows: input, pull-down */
	for(int i = 0; i < (Key_Str->rows_count);i++)
	{
		Key_Str->pins_rows[i].Mode = GPIO_MODE_INPUT;
		Key_Str->pins_col[i].Pull = GPIO_PUPDR_PULLDOWN;
		
		Enable_Periphery_Key(&Key_Str->pins_rows[i]);
		
		GPIO_Init(&Key_Str->pins_rows[i]);

		delay_ms(1);
	}
}

void Enable_Periphery_Key(GPIO_Structure *GPIO_Str)
{
    /*RM0090 Reference manual на STM32F407/417*/
    if(GPIO_Str->GPIOx == GPIOA)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOAEN);
        return;
    }

    if(GPIO_Str->GPIOx == GPIOB)
    {
				AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOBEN);
				return;
    }
    if(GPIO_Str->GPIOx == GPIOC)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOCEN);
				return;
    }
		
    if(GPIO_Str->GPIOx == GPIOD)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIODEN);
				return;
    }
		
    if(GPIO_Str->GPIOx == GPIOE)
    {
        AHB1_ENABLE_PERIPHERY(RCC_AHB1ENR_GPIOEEN);
				return;
    }
}

uint32_t temp = 0;
int c = 0;
int r = 0;
int rez =0;
char* Survey_Key(Key_Structure *Key_Str)
{
	rez =0;
//	for(int c = 0; c < (Key_Str->cols_count);c++)
//	{
//		ODR_0(&Key_Str->pins_col[c]);
//	}
	

		
			for( r = 0; r < (Key_Str->rows_count);r++)
			{
				for( c = 0; c < (Key_Str->cols_count);c++)
				{
					ODR_1(&Key_Str->pins_col[c]);
			
					temp = Read_BIT((Key_Str->pins_rows[r].GPIOx->IDR),(1 << Key_Str->pins_rows[r].Pin));
					ODR_0(&Key_Str->pins_col[c]);
					
					if(temp!=0)
					{
						break;
					}
					rez++;
					
					
				}
				
					if(temp!=0)
					{
						break;
					}
			}
			
			//ODR_0(&Key_Str->pins_col[c]);
			//delay_s(1);
	
	
	
				if( (c == 0U) && (r == 0U))
				{
						return "1";
				}
				
				if( (c == 0) && (r == 1))
				{
						return("4");
				}
				
				if( (c == 0) && (r == 2))
				{
						return("7");
				}
				
				if( (c == 0) && (r == 3))
				{
						return("*");
				}
				//
				if((temp != 0) && (c == 1) && (r == 0))
				{
						return("2");
				}
				
				if((temp != 0) && (c == 1) && (r == 1))
				{
						return("5");
				}
				
				if((temp != 0) && (c == 1) && (r == 2))
				{
						return("8");
				}
				
				if((temp != 0) && (c == 1) && (r == 3))
				{
						return("0");
				}
				//
				if((temp != 0) && (c == 2) && (r == 0))
				{
						return("3");
				}
				
				if((temp != 0) && (c == 2) && (r == 1))
				{
						return("6");
				}
				
				if((temp != 0) && (c == 2) && (r == 2))
				{
						return("9");
				}
				
				if((temp != 0) && (c == 2) && (r == 3))
				{
						return "#";
				}
				//
				if((temp != 0) && (c == 3) && (r == 0))
				{
						return "A";
				}
				
				if((temp != 0) && (c == 3) && (r == 1))
				{
						return "B";
				}
				
				if((temp != 0) && (c == 3) && (r == 2))
				{
						return "C";
				}
				
				if((temp != 0) && (c == 3) && (r == 3))
				{
						return "D";
				}

	return 0;
}

void Connect_Exti()
{
	/*Настроим кнопки по прерыванию*/
  ENABLE_BIT(SYSCFG->EXTICR[3],SYSCFG_EXTICR4_EXTI15_PB);/*cвязка PB15 с EXTI*/
  ENABLE_BIT(EXTI->IMR,EXTI_IMR_MR15);/*Разрешение irq*/
  ENABLE_BIT(EXTI->FTSR,EXTI_FTSR_TR15);/*Прерывание по спаду*/
	NVIC_EnableIRQ(EXTI4_IRQn);
}