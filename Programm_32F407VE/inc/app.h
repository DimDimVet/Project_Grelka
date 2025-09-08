#ifndef APP_H_
#define APP_H_

/*includes*/
#include "HEHAL.h"
#include "events.h"
#include "RCC.h"
#include "GPIO.h"
#include "PWR.h"
#include "appointed_Pin.h"
#include "ADC.h"
#include "I2C.h"
#include "ssd1306.h"
#include "Buttons_panel.h"

/*defaines*/
#define SSD1306_I2C_ADDR 0x78 /*адрес I2C экрана*/



#define TEMP_23_50(volt) ((volt*1000-1136,667)/16,666)
#define TEMP_51_80(volt) ((volt*1000-1487,586)/9,655)
#define TEMP_81_100(volt) ((volt*1000-1715,736)/ 6,842)
#define TEMP_101_120(volt) ((volt*1000-1390)/ 10)
#define TEMP_121_150(volt) ((volt*1000-1823)/ 6,379)
#define TEMP_151_180(volt) ((volt*1000- 2363,414)/ 2,758)
#define LENGTH_VOLT_ARR 7
/*structures*/

/*var*/
/*соот. B57045-K 103-K в делителе с 10к
1,52V = 23C = 9.7k
1,97V = 50C = 5.2k
2,26V = 80C = 3.3k
2,4V = 100C = 2.5k
2,59V = 120C = 1.6k
2,78V = 150C = 0.8k
2,86V = 180C = 0.5k
*/
static float range_volt[LENGTH_VOLT_ARR]={1.52,1.97,2.26,2.4,2.59,2.78,2.86};
/*func*/

void Handler_Buttons_panel_Event(void *var, int vol);
void Handler_ADC_Event(uint16_t adcData, float adcVoltage);
void Handler_ADC_PWR(PWR_Structure* pwr, uint16_t adcData, uint16_t step_temp);
#endif