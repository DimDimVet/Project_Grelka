#include "logic_ADC_PWR.h"

uint8_t flag_On_Off = OFF;
uint8_t queue_data = 0;

uint16_t count_scoring_ADC;
float rez_tmp[SCORING_ADC];

void On_Off_Factor(PWR_Structure* pwr, uint8_t flag)
{
  pwr->pwr_on = flag;

  Replace_Fill_Factor(pwr);

  Start_Event_Write_To_USART(pwr->pwr_on, FLAG_USART_ON_OFF_PWR);
}

void Set_Fill_Factor(PWR_Structure* pwr, uint8_t vol, uint8_t step_vol, uint16_t min_temp, uint16_t max_temp)
{
  /*Pin8 Enter, pin15 -10, pin9 +10, pin11 -1, pin13 +1*/

  if (vol == PIN15)
    {
      pwr->step_temp -= step_vol;

      if (pwr->step_temp <= min_temp)
        {
          pwr->step_temp = min_temp;
        }

      Start_Event_Write_To_USART(pwr->step_temp, FLAG_USART_BUTTONS); /*передадим в ПК значение с кнопок*/
    }

  if (vol == PIN9)
    {
      pwr->step_temp += step_vol;

      if (pwr->step_temp >= max_temp)
        {
          pwr->step_temp = max_temp;
        }

      Start_Event_Write_To_USART(pwr->step_temp, FLAG_USART_BUTTONS); /*передадим в ПК значение с кнопок*/
    }

  if (vol == PIN11)
    {
      if (flag_On_Off == OFF)
        {
          Start_Event_On_Off_PWR(ON);
          flag_On_Off = !flag_On_Off;
        }
      else
        {
          Start_Event_On_Off_PWR(OFF);
          flag_On_Off = !flag_On_Off;
        }
    }

  if (vol == PIN13)
    {

    }

  if (vol == PIN8)
    {
      Set_Flash_Data(pwr->step_temp);

      Start_Event_Write_To_USART(0, FLAG_USART_FLASH); /*передадим в ПК значение истины записи флеш*/
    }

  Replace_Fill_Factor(pwr);
  Start_Event_Write_To_USART(pwr->fill_Factor, FLAG_USART_FILL_PWR);
}

void Handler_ADC_PWR(PWR_Structure* pwr, uint16_t adcData, float* rez_temperature)
{
  float rez_volt = adcData * 3.0 / 4095;

  if (count_scoring_ADC > SCORING_ADC)
    {
			float tmp = 0;
      count_scoring_ADC = 0;
			
			for(uint16_t i = 0; i < SCORING_ADC; i++)
			{
				tmp = tmp + rez_tmp[i];
			}
			
			rez_temperature[0] = tmp / SCORING_ADC;
			
			 Comporator_Termo(pwr,rez_temperature);
    }
  else
    {
      //{1.52,1.97,2.26,2.4,2.59,2.78,2.86}
      if (_RANGE(rez_volt, 2.86, 3))
        {
          rez_tmp[count_scoring_ADC] = 200;
        }                                                                                                           
      else if (_RANGE(rez_volt, 2.78, 2.86))
        {
          rez_tmp[count_scoring_ADC] = TEMP_151_180(rez_volt);
        }
      else if (_RANGE(rez_volt, 2.59, 2.78))
        {
          rez_tmp[count_scoring_ADC] = TEMP_121_150(rez_volt);
        }
      else if (_RANGE(rez_volt, 2.4, 2.59))
        {
          rez_tmp[count_scoring_ADC] = TEMP_101_120(rez_volt);
        }
      else if (_RANGE(rez_volt, 2.26, 2.4))
        {
          rez_tmp[count_scoring_ADC] = TEMP_81_100(rez_volt);
        }
      else if (_RANGE(rez_volt, 1.97, 2.26))
        {
          rez_tmp[count_scoring_ADC] = TEMP_51_80(rez_volt);
        }
      else if (_RANGE(rez_volt, 1.52, 1.97))
        {
          rez_tmp[count_scoring_ADC] = TEMP_23_50(rez_volt);
        }
      else if (_RANGE(rez_volt, 0, 1.52))
        {
          rez_tmp[count_scoring_ADC] = 10;
        }

      count_scoring_ADC++;
    }

}

void Comporator_Termo(PWR_Structure* pwr, float* rez_temp)
{
	/*если температура ниже порога*/
  if (pwr->step_temp > rez_temp[0])
    {
      uint16_t temp = pwr->step_temp - rez_temp[0];

      if (_RANGE(temp, 50, 200))
        {
          pwr->fill_Factor = 5;
        }

      if (_RANGE(temp, 30, 49))
        {
          pwr->fill_Factor = 3;
        }

      if (_RANGE(temp, 5, 29))
        {
          pwr->fill_Factor = 2;
        }

      if (_RANGE(temp, 0, 4))
        {
          pwr->fill_Factor = 1;
        }
    }
  else
    {
		/*если температура выше порога*/
      uint16_t temp = rez_temp[0] - pwr->step_temp;

      if (_RANGE(temp, 0, 200))
        {
          pwr->fill_Factor = 0;
        }
    }

  Replace_Fill_Factor(pwr);

  Push_Queue_To_Usart(pwr, rez_temp[0]);
}


void Push_Queue_To_Usart(PWR_Structure* pwr, float rez_temp)
{
  queue_data++;

  switch (queue_data)
    {
      case 1:  /*отправим заполнение шим */
        Start_Event_Write_To_USART(pwr->fill_Factor, FLAG_USART_FILL_PWR);
        break;

      case 2:  /*отправим температуру */
        Start_Event_Write_To_USART(rez_temp, FLAG_USART_TEMPERATURE);
        break;

      case 3:  /*отправим порог*/
        Start_Event_Write_To_USART(pwr->step_temp, FLAG_USART_BUTTONS);
        break;

      case 4:  /*отправим статус вкл*/
        Start_Event_Write_To_USART(pwr->pwr_on, FLAG_USART_ON_OFF_PWR);
        break;

      default:
        queue_data = 0;
        break;
    }
}
