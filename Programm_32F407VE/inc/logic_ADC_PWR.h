#ifndef LOGIC_ADC_PWR_H_
#define LOGIC_ADC_PWR_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "HEHAL.h"
#include "ADC.h"
#include "PWR.h"
#include "setup_flash_F407.h"

/*defaines*/
/*соот. B57045-K 103-K в делителе с 10к
1,52V = 23C = 9.7k
1,97V = 50C = 5.2k
2,26V = 80C = 3.3k
2,4V = 100C = 2.5k
2,59V = 120C = 1.6k
2,78V = 150C = 0.8k
2,86V = 180C = 0.5k
*/

#define TEMP_23_50(volt) ((volt*1000-1136.667)/16.666)
#define TEMP_51_80(volt) ((volt*1000-1487.586)/9.655)
#define TEMP_81_100(volt) ((volt*1000-1715.736)/ 6.842)
#define TEMP_101_120(volt) ((volt*1000-1390)/ 10)
#define TEMP_121_150(volt) ((volt*1000-1823)/ 6.379)
#define TEMP_151_180(volt) ((volt*1000- 2363.414)/ 2.758)

/*structures*/

/*var*/

/*func*/
void Handler_ADC_PWR(PWR_Structure* pwr, uint16_t adcData);
void Set_Fill_Factor(PWR_Structure* pwr, uint8_t vol, uint8_t step_vol,uint16_t min_temp, uint16_t max_temp);

#endif