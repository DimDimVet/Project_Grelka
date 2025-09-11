#include "setup_flash_F407.h"

void Set_Flash_Data(int data)
{
	uint32_t prim = __get_PRIMASK();
	
	__disable_irq();
	
	FLASH_Unlock();
	
	arr_time_date[0] = data;

	uint8_t size_temp = sizeof(addr_time_date)/sizeof(addr_time_date[0]);
	
//	FLASH_EraseSector( GetSector( addr_time_date[0] ), VoltageRange_3 );
	
	
	for(uint8_t i = 0; i <  SIZE; i++)
	{
		FLASH_EraseSector( GetSector( addr_time_date[i] ), VoltageRange_3 );
		//delay_ms(50);
	}
	
	for(uint8_t i = 0; i <  SIZE; i++)
	{
		FLASH_ProgramWord(addr_time_date[i], arr_time_date[i]);
		//delay_ms(50);
	}

	FLASH_Lock();
	
	if (!prim) __enable_irq();
	
	__enable_irq();
}

void Get_Flash_Data(PWR_Structure* pwr)
{
	__disable_irq();
	
	FLASH_Unlock();

	uint8_t size_temp = sizeof(addr_time_date)/sizeof(addr_time_date[0]);
	
	for(uint8_t i = 0; i < SIZE; i++)
	{
		arr_time_date[i] = FLASH_Read(addr_time_date[i]);
	}
	
	FLASH_Lock();

	pwr->step_temp = arr_time_date[0];
	
	__enable_irq();
}

//    uint32_t addr = 0x08010000;
//    /*------------*/

//    FLASH_Unlock();
//    // Адрес для записи
//    FLASH_EraseSector( GetSector( addr ), VoltageRange_3 );;
//    FLASH_ProgramWord(addr, 0xDEADBACF);

//    data = FLASH_Read(addr);
//    FLASH_Lock();