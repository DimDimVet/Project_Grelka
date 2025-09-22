#include "logic_ADC_PWR.h"

void Set_Fill_Factor(PWR_Structure* pwr, uint8_t vol, uint8_t step_vol,uint16_t min_temp, uint16_t max_temp)
{
	/*Pin8 Enter, pin15 -10, pin9 +10, pin11 -1, pin13 +1*/

	 if(vol == PIN15)
	 {
			 pwr->step_temp -= step_vol;
			 
			 if(pwr->step_temp <= min_temp)
			 {
				 pwr->step_temp = min_temp;
			 }
			 
			 Start_Event_Buttons_USART(pwr->step_temp);/*передадим в ПК значение с кнопок*/
	 }
	 
	 if(vol == PIN9)
	 {
			 pwr->step_temp += step_vol;
			 
			 if(pwr->step_temp >= max_temp)
			 {
				 pwr->step_temp = max_temp;
			 }
			 
			 Start_Event_Buttons_USART(pwr->step_temp);/*передадим в ПК значение с кнопок*/
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
		 
		 Start_Event_Buttons_USART(FLASH_FLAG);/*передадим в ПК значение с кнопок,*/
	 }
	 
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
          pwr->fill_Factor = 45;
        }

      if (_RANGE(temp, 10,20))
        {
          pwr->fill_Factor = 15;
        }

      if (_RANGE(temp, 5,10))
        {
          pwr->fill_Factor = 5;
        }

      if (_RANGE(temp, 2,5))
        {
          pwr->fill_Factor = 1;
        }
    }
  else
    {
      uint16_t temp = rez_temp - pwr->step_temp;

      if (_RANGE(temp, 2,5))
        {
          pwr->fill_Factor = 1;
        }

      if (_RANGE(temp, 5,200))
        {
          pwr->fill_Factor = 0;
        }
    }
		
		Replace_Fill_Factor(pwr);
}
