#include "app.h"
int countFillFactor=0;
ssd1306_t str_SSD1306;

RCC_Structure rcc_str = {.mDivider_PLLM = 8,.nMultiplier_PLLN = 192,.pDivider_PLLP = 6}; /*структура для RCC*/
PWR_Structure pwr_str = {.TIMx = TIM3,.fill_Factor = 50}; /*структура для ШИМ*/
I2C_Structure i2c_str = {.I2Cx = I2C1};/*Настройки I2C*/

/*Настройки Key*/
/*map  cols[0] - rows[0] "1"  cols[1] - rows[0] "2"  cols[2] - rows[0] "3"  cols[3] - rows[0] "A"
		   cols[0] - rows[1] "4"  cols[1] - rows[1] "5"  cols[2] - rows[1] "6"  cols[3] - rows[1] "B"
		   cols[0] - rows[2] "7"  cols[1] - rows[2] "8"  cols[2] - rows[2] "9"  cols[3] - rows[2] "C"
		   cols[0] - rows[3] "*"  cols[1] - rows[3] "0"  cols[2] - rows[3] "#"  cols[3] - rows[3] "D" */

GPIO_Structure cols[4] = {{.GPIOx = GPIOD,.Pin = PIN8},{.GPIOx = GPIOD,.Pin = PIN10},{.GPIOx = GPIOD,.Pin = PIN12},{.GPIOx = GPIOD,.Pin = PIN14}};
GPIO_Structure rows[4] = {{.GPIOx = GPIOB,.Pin = PIN15},{.GPIOx = GPIOD,.Pin = PIN9},{.GPIOx = GPIOD,.Pin = PIN11},{.GPIOx = GPIOD,.Pin = PIN13}};
Key_Structure keys = {.cols_count = 4,.rows_count = 4,.pins_col = cols,.pins_rows = rows};

char keymap1[16] = {
  '1'
};


/*main*/

int main()
{
  RCC_Init(&rcc_str);
  Init_Tim_PWR(&pwr_str);
	Init_App_Pin();
	Init_I2C(&i2c_str);
	Key_Init(&keys);
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

  while (1)
    {
			Handler_LED7();
			char* temps = Survey_Key(&keys);
			TempChar(temps);
			Reset_Key(&keys);
			
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