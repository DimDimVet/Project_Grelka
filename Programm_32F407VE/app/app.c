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
	Init_USART1(BAUND_RATE);
  Init_Tim_PWR(&pwr_str);
  Init_App_Pin();
  Init_I2C(&i2c_str);
  SSD1306_Init(&ssd);
	
  Buttons_Init(&buttons);
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

void Write_Terminal_USART(char *str1, char *str2, char *str3)
{
	char buff_str[SIZE_BUFF_USART];
	
	USART1_SetString(NEW_STRING_CONSOLE);
	
	Sprintf_str_to_str(SIZE_BUFF_USART,buff_str,str1," ",str2," ",str3," /stop");
	
	USART1_SetString(buff_str);

}

//void Handler_Key0(void)//temp
//{
//  Handler_LED7();
//  pwr_str.fill_Factor += 10;

//  if ((pwr_str.fill_Factor) <= 100)
//    {
//      Replace_Fill_Factor(&pwr_str);
//    }
//  else
//    {
//      pwr_str.fill_Factor = 0;
//      Replace_Fill_Factor(&pwr_str);
//    }
//}

//void Handler_Key1(void)//temp
//{
//  Handler_LED7();
//  pwr_str.fill_Factor -= 10;

//  if ((pwr_str.fill_Factor) >= 0)
//    {
//      Replace_Fill_Factor(&pwr_str);
//    }
//  else
//    {
//      pwr_str.fill_Factor = 0;
//      Replace_Fill_Factor(&pwr_str);
//    }
//}

void Handler_ADC_Event(uint16_t adcData, float adcVoltage)
{
  char buff_str_temp[50];
  char buff_str_temp1[50];
  char buff_str_PWR[50];
	char buff_str_Step[50];
  sprintf(buff_str_temp, "Volt=%.2fV %s", adcVoltage, temps);
	
	sprintf(buff_str_Step, "Step temp=%d  ", pwr_str.step_temp);
  sprintf(buff_str_PWR, "Fill PWR=%.2d", pwr_str.fill_Factor);
  sprintf(buff_str_temp1, "=%.2d", adcData / 4095);
  //
	//SSD1306_Clear(&ssd);
	
  current_screen.str0 = buff_str_temp;
  current_screen.x0 = 10;

  current_screen.str1 = buff_str_temp;
  current_screen.x1 = 10;

  current_screen.str2 = buff_str_temp;
  current_screen.x2 = 10;

  current_screen.str3 = rezultReadConsol;
  current_screen.x3 = 10;
	
  current_screen.str4 = buff_str_Step;
  current_screen.x4 = 10;

  current_screen.str5 = buff_str_PWR;
  current_screen.x5 = 10;

  Work_Screen(&ssd, &current_screen);

  Handler_ADC_PWR(&pwr_str, adcData);
	
}

void Event_Buttons_panel(uint8_t pin)
{
	Write_Terminal_USART("ASD","_FGT","33");
	Set_Fill_Factor(&pwr_str,pin,STEP_VOL,MIN_STEP_TEMP,MAX_STEP_TEMP);
	
}
/*temp*/
void ExecutorTerminal_USART_Irq(void)
{
    USART1_ReadChar(receivedChar); // Читаем из консоли

    if (count_size_buf >= SIZE_BUF_USART)
    {
        count_size_buf = 0;

        __disable_irq();

//        while (I2C_Master_Transmit(I2C1, I2C_ADDRESS, (uint8_t*)rezultReadConsol, BUFFER_SIZE_I2C, 10) != 0)
//        {
//            Error_Handler();
//        }


//        while (I2C_Master_Receive(I2C1, I2C_ADDRESS, (uint8_t*)rezultReadI2C, BUFFER_SIZE_I2C, 10) != 0)
//        {
//            Error_Handler();
//        }

        __enable_irq();

        USART1_SetString(rezultReadI2C);

    }
    else
    {
        rezultReadConsol[count_size_buf] = receivedChar_;
        count_size_buf++;
    }
}
