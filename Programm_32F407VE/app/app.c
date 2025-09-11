#include "app.h"

/*структура для RCC*/
RCC_Structure rcc_str = {.mDivider_PLLM = 8, .nMultiplier_PLLN = 192, .pDivider_PLLP = 6}; /*структура для RCC*/
/*структура для ШИМ*/
PWR_Structure pwr_str = {.TIMx = TIM3, .fill_Factor = 50,.step_temp = MIN_STEP_TEMP};
/*Настройки SSD1306*/
SSD1306_Structure ssd = {.adress_I2C = SSD1306_I2C_ADDR, .instance = I2C1};
Screen_Structure main_screen = {.str0 = "*Project:*", .x0 = 10, .str2 = "GRELKA", .x2 = 30};
Screen_Structure current_screen = {};
/*Настройки I2C*/
I2C_Structure i2c_str = {.I2Cx = I2C1};
/*Настройки Buttons*/
/*Pin8 Enter, pin15 +10, pin9 -10, pin11 +1, pin13 -1*/
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
	
	Get_Flash_Data(&pwr_str);
  /**/
  Main_Screen(&ssd, &main_screen, 1);
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

void Handler_Key0(void)//temp
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

void Handler_Key1(void)//temp
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
  char buff_str_temp1[50];
  char buff_str_PWR[50];
	char buff_str_Step[50];
  sprintf(buff_str_temp, "Volt=%.2fV %s", adcVoltage, temps);
	
	sprintf(buff_str_Step, "Step temp=%d", pwr_str.step_temp);
  sprintf(buff_str_PWR, "Fill PWR=%.2d", pwr_str.fill_Factor);
  sprintf(buff_str_temp1, "=%.2d", adcData / 4095);
  //
  current_screen.str0 = buff_str_temp;
  current_screen.x0 = 10;

  current_screen.str1 = buff_str_temp;
  current_screen.x1 = 10;

  current_screen.str2 = buff_str_temp;
  current_screen.x2 = 10;

  current_screen.str3 = buff_str_temp;
  current_screen.x3 = 10;

  current_screen.str4 = buff_str_Step;
  current_screen.x4 = 10;

  current_screen.str5 = buff_str_PWR;
  current_screen.x5 = 10;

  Work_Screen(&ssd, &current_screen);

  Handler_ADC_PWR(&pwr_str, adcData);

}

void Handler_Buttons_panel_Event(void *var, int vol)
{
		//temps = (char*)var;
	delay_ms(150);
	Set_Fill_Factor(&pwr_str,vol);
	
	sprintf(temps, "%d", pwr_str.step_temp);

}

void Event_Tst(uint8_t data)
{
	Set_Fill_Factor(&pwr_str,data);
}

void Set_Fill_Factor(PWR_Structure* pwr, uint8_t vol)
{
	/*Pin8 Enter, pin15 -10, pin9 +10, pin11 -1, pin13 +1*/

	 if(vol == PIN15)
	 {
			 pwr->step_temp -= 5;
			 if(pwr->step_temp <= MIN_STEP_TEMP)
			 {
				 pwr->step_temp = MIN_STEP_TEMP;
			 }
			 //Set_Flash_Data(pwr_str.step_temp);
	 }
	 
	 if(vol == PIN9)
	 {
			 pwr->step_temp += 5;
			 if(pwr->step_temp >= MAX_STEP_TEMP)
			 {
				 pwr->step_temp = MAX_STEP_TEMP;
			 }
			 //Set_Flash_Data(pwr_str.step_temp);
	 }
	 
	 if(vol == PIN11)
	 {
		 
	 }
	 
	 if(vol == PIN13)
	 {
		 
	 }
	 
	 if(vol == PIN8)
	 {
		 Set_Flash_Data(pwr->step_temp);
	 }
	 //pwr_str.step_temp = temp;
	 Replace_Fill_Factor(pwr);
}

void Handler_ADC_PWR(PWR_Structure* pwr, uint16_t adcData)
{
  float rez_volt = adcData * 3.0 / 4095;

  float rez_temp;
  //{1.52,1.97,2.26,2.4,2.59,2.78,2.86}
  if (_RANGE(rez_volt,2.86,3))
    {
      rez_temp = 200;
    }
  else if (_RANGE(rez_volt,2.78,2.86))
    {
      rez_temp = TEMP_151_180(rez_volt);
    }
  else if (_RANGE(rez_volt,2.59,2.78))
    {
      rez_temp = TEMP_121_150(rez_volt);
    }
  else if (_RANGE(rez_volt,2.4,2.59))
    {
      rez_temp = TEMP_101_120(rez_volt);
    }
  else if (_RANGE(rez_volt,2.26,2.4))
    {
      rez_temp = TEMP_81_100(rez_volt);
    }
  else if (_RANGE(rez_volt, 1.97,2.26))
    {
      rez_temp = TEMP_51_80(rez_volt);
    }
  else if (_RANGE(rez_volt, 1.52,1.97))
    {
      rez_temp = TEMP_23_50(rez_volt);
    }
  else if (_RANGE(rez_volt, 0,1.52))
    {
      rez_temp = 10;
    }


  if (pwr->step_temp > rez_temp)
    {
      uint16_t temp = pwr->step_temp - rez_temp;

      if (_RANGE(temp, 20,200))
        {
          pwr_str.fill_Factor = 45;
        }

      if (_RANGE(temp, 10,20))
        {
          pwr_str.fill_Factor = 15;
        }

      if (_RANGE(temp, 5,10))
        {
          pwr_str.fill_Factor = 5;
        }

      if (_RANGE(temp, 2,5))
        {
          pwr_str.fill_Factor = 1;
        }
    }
  else
    {
      uint16_t temp = rez_temp - pwr->step_temp;

      if (_RANGE(temp, 2,5))
        {
          pwr_str.fill_Factor = 1;
        }

      if (_RANGE(temp, 5,200))
        {
          pwr_str.fill_Factor = 0;
        }
    }
}
