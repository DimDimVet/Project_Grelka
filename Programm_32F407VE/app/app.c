#include "app.h"
int countFillFactor=0;
ssd1306_t str_SSD1306;

RCC_Structure rcc_str = {.mDivider_PLLM = 8,.nMultiplier_PLLN = 192,.pDivider_PLLP = 6}; /*структура для RCC*/
PWR_Structure pwr_str = {.TIMx = TIM3,.fill_Factor = 50}; /*структура для ШИМ*/
I2C_Structure i2c_str = {.I2Cx = I2C1};/*Настройки I2C*/

/*Настройки Buttons*/
GPIO_Structure arr_buttons[5] = {{.GPIOx = GPIOD,.Pin = PIN8},{.GPIOx = GPIOB,.Pin = PIN15},{.GPIOx = GPIOD,.Pin = PIN9},{.GPIOx = GPIOD,.Pin = PIN11},{.GPIOx = GPIOD,.Pin = PIN13}};
GPIO_Structure com = {.GPIOx = GPIOD,.Pin = PIN14};

Butt_Panel_Structure buttons = {.buttons_count = 5,.pin_butt = arr_buttons,.pin_com = &com};

//GPIO_Structure cols[4] = {{.GPIOx = GPIOD,.Pin = PIN8},{.GPIOx = GPIOD,.Pin = PIN10},{.GPIOx = GPIOD,.Pin = PIN12},{.GPIOx = GPIOD,.Pin = PIN14}};
//GPIO_Structure rows[4] = {{.GPIOx = GPIOB,.Pin = PIN15},{.GPIOx = GPIOD,.Pin = PIN9},{.GPIOx = GPIOD,.Pin = PIN11},{.GPIOx = GPIOD,.Pin = PIN13}};
//Key_Structure keys = {.cols_count = 4,.rows_count = 4,.pins_col = cols,.pins_rows = rows};



/*main*/
char* temps;
int main()
{
  RCC_Init(&rcc_str);
  Init_Tim_PWR(&pwr_str);
	Init_App_Pin();
	Init_I2C(&i2c_str);
	Buttons_Init(&buttons);
  /**/
  

  str_SSD1306.adress_I2C = SSD1306_I2C_ADDR;
  str_SSD1306.instance = I2C1;
  SSD1306_Init(&str_SSD1306);

  SSD1306_Fill(SSD1306_COLOR_WHITE);
  /* */
  SSD1306_GotoXY(&str_SSD1306, 20, 0);
  SSD1306_Puts(&str_SSD1306, "XZXZXZXZ", &Font_11x18, 0.9);
  SSD1306_GotoXY(&str_SSD1306, 10, 30);
  SSD1306_Puts(&str_SSD1306, "xxx", &Font_16x26, 1);
  SSD1306_UpdateScreen(&str_SSD1306);
  delay_s(1);
  SSD1306_Clear(&str_SSD1306);

  /*------------*/
  ADC_Init(ADC1);
  /*------------*/
Init_Event(my_handler);
Init_Event(my_handler2);
  while (1)
    {
			Handler_LED7();
//			char* temps = Survey_Key(&keys);
			TempChar(temps);
			//delay_ms(1);
			Enable_ADC();
    }

  return 0;
}

void Handler_Key0(void)
{
  Handler_LED7();
  pwr_str.fill_Factor+=10;
	
  if((pwr_str.fill_Factor)<=100)
    {
      Replace_Fill_Factor(&pwr_str);
    }
  else
    {
      pwr_str.fill_Factor=0;
      Replace_Fill_Factor(&pwr_str);
    }
}

void Handler_Key1(void)
{
  Handler_LED7();
  pwr_str.fill_Factor-=10;
	
  if((pwr_str.fill_Factor)>=0)
    {
      Replace_Fill_Factor(&pwr_str);
    }
  else
    {
      pwr_str.fill_Factor=0;
      Replace_Fill_Factor(&pwr_str);
    }
}

char buff_str_temp1[20];
void WorkADC(char* buff_str_temp1)
{
  SSD1306_GotoXY(&str_SSD1306, 0, 20);
  SSD1306_Puts(&str_SSD1306, buff_str_temp1, &Font_7x10, 1);
  SSD1306_UpdateScreen(&str_SSD1306);
}

void event(void *ctx)
{
    temps =(char*)ctx;
}

void my_handler(void *ctx, int event_data)
	{
    temps =(char*)ctx;
}
	
void my_handler2(void *ctx, int event_data)
	{
    temps =(char*)ctx;
}
