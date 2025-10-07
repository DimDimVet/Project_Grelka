#ifndef HEHAL_H_
#define HEHAL_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"

/*defaines*/
/*Битовые операции*/
#define ENABLE_BIT(reg, bit) ((reg) |= (uint32_t)(bit))
#define DISABLE_BIT(reg, bit) ((reg) &= ~(uint32_t)(bit))
#define Read_BIT(reg, bit)    ((reg) & (bit))
/*Регистовые операции*/
#define Write_REG(REG, VAL)   ((REG) = (VAL))
#define Read_REG(REG)         ((REG))
#define Clear_REG(REG)        ((REG) = (0))
/*Логика*/
#define _RANGE(vol,min,max) ((vol > min) && (vol < max))
/*Вкл. периферии*/
#define AHB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->AHB1ENR |= _RCC_PERIPHERY_)/*вкл что то по AHB1*/
#define APB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB1ENR |= _RCC_PERIPHERY_)/*вкл что то по APB1*/
#define APB2_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB2ENR |= _RCC_PERIPHERY_)/*вкл что то по APB2*/

#define ON 1
#define OFF 0

/*var*/

/*structures*/
typedef enum
{
  _OK       = 0U,
  _ERROR    = 1U,
  _ERROR_BUSY = 2U,
  _ERROR_TIMEOUT = 3U,
} RezultError;

/*func*/
void Сonverter_Int_Str(char *str, int val);
void Sprintf_M(char *buff, const char *prefix, int val);
void Sprintf_str_to_str(int size_buf, char *buff, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6);

#endif

/*!E --style=gnu --indent=spaces=2*/
/*!E --style=gnu --indent=spaces=2 --indent-switches --break-blocks --pad-oper --pad-comma --pad-header --align-pointer=name --align-reference=name --convert-tabs --keep-one-line-blocks --keep-one-line-statements*/

/*includes*/

/*defaines*/

/*structures*/

/*var*/

/*func*/