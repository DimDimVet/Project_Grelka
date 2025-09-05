#include "app.h"
int countFillFactor = 0;

/*структура для RCC*/
RCC_Structure rcc_str = {.mDivider_PLLM = 8, .nMultiplier_PLLN = 192, .pDivider_PLLP = 6}; /*структура для RCC*/
/*структура для ШИМ*/
PWR_Structure pwr_str = {.TIMx = TIM3, .fill_Factor = 50}; 
/*Настройки SSD1306*/
SSD1306_Structure ssd = {.adress_I2C = SSD1306_I2C_ADDR, .instance = I2C1};
Screen_Structure main_screen = {.str0 = "*Project:*", .x0 = 10, .str2 = "GRELKA", .x2 = 30};
Screen_Structure current_screen = {};
/*Настройки I2C*/
I2C_Structure i2c_str = {.I2Cx = I2C1};
/*Настройки Buttons*/
GPIO_Structure arr_buttons[5] = {{.GPIOx = GPIOD, .Pin = PIN8}, {.GPIOx = GPIOB, .Pin = PIN15}, {.GPIOx = GPIOD, .Pin = PIN9}, {.GPIOx = GPIOD, .Pin = PIN11}, {.GPIOx = GPIOD, .Pin = PIN13}};
GPIO_Structure com = {.GPIOx = GPIOD, .Pin = PIN14};
Butt_Panel_Structure buttons = {.buttons_count = 5, .pin_butt = arr_buttons, .pin_com = &com};

/*main*/
char *temps;
int main()
{
  RCC_Init(&rcc_str);
  Init_Tim_PWR(&pwr_str);
  Init_App_Pin();
  Init_I2C(&i2c_str);
  SSD1306_Init(&ssd);
  Buttons_Init(&buttons);
  Connect_Event_Buttons_panel(Handler_Buttons_panel_Event);
  Connect_Event_ADC(Handler_ADC_Event);
  /**/
  Main_Screen(&ssd, &main_screen, 5);
  /*------------*/
  ADC_Init(ADC1);
  /*------------*/

  while (1)
    {
      Handler_LED7();
      Enable_ADC();
    }

  return 0;
}

void Handler_Key0(void)
{
  Handler_LED7();
  pwr_str.fill_Factor += 10;

  if ((pwr_str.fill_Factor) <= 100)
    {
      Replace_Fill_Factor(&pwr_str);
    }
  else
    {
      pwr_str.fill_Factor = 0;
      Replace_Fill_Factor(&pwr_str);
    }
}

void Handler_Key1(void)
{
  Handler_LED7();
  pwr_str.fill_Factor -= 10;

  if ((pwr_str.fill_Factor) >= 0)
    {
      Replace_Fill_Factor(&pwr_str);
    }
  else
    {
      pwr_str.fill_Factor = 0;
      Replace_Fill_Factor(&pwr_str);
    }
}

void Handler_ADC_Event(uint16_t adcData, float adcVoltage)
{
  char buff_str_temp[50];
  sprintf(buff_str_temp, "Volt=%.2fV %s", adcVoltage, temps);
  //
  current_screen.str0 = buff_str_temp;
  current_screen.x0 = 10;

  current_screen.str1 = buff_str_temp;
  current_screen.x1 = 10;

  current_screen.str2 = buff_str_temp;
  current_screen.x2 = 10;

  current_screen.str3 = buff_str_temp;
  current_screen.x3 = 10;

  current_screen.str4 = buff_str_temp;
  current_screen.x4 = 10;

  current_screen.str5 = buff_str_temp;
  current_screen.x5 = 10;

  Work_Screen(&ssd, &current_screen);

}

void Handler_Buttons_panel_Event(void *var, int vol)
{
  temps = (char*)var;
}

