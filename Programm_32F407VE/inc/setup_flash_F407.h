#ifndef SETUP_FLASH_H_
#define SETUP_FLASH_H_

/*includes*/
#include "flash_F407.h"
#include "RCC.h"
#include "PWR.h"

/*defaines*/
#define PWR_DATA_STEP 0x08010000
//#define ADD_MINUTES 0x08020000
//#define ADD_DATE 0x08030000
//#define ADD_MONTH 0x08040000
//#define ADD_YEAR 0x08050000
#define SIZE 1
/*var*/
static uint32_t addr_time_date[SIZE] = {PWR_DATA_STEP};
static int arr_time_date[SIZE];
/*structures*/

/*func*/
void Set_Flash_Data(int data);
void Get_Flash_Data(PWR_Structure* pwr);

#endif
