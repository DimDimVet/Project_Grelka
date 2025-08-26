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
#define Clear_REG(REG)        ((REG) = (0x0))	
/*Вкл. периферии*/
#define AHB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->AHB1ENR |= _RCC_PERIPHERY_)/*вкл что то по AHB1*/
#define APB1_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB1ENR |= _RCC_PERIPHERY_)/*вкл что то по APB1*/
#define APB2_ENABLE_PERIPHERY(_RCC_PERIPHERY_) (RCC->APB2ENR |= _RCC_PERIPHERY_)/*вкл что то по APB2*/
/*var*/

/*structures*/
typedef enum
{
	OK_       = 0x00U,
  ERROR_    = 0x01U,
}Rezult_t;

/*func*/
void Сonverter_Int_Str(char *str, int val);
void Sprintf_M(char *buff, const char *prefix, int val);
void Sprintf_str_to_str(int size_buf,char *buff, char *str1, char *str2, char *str3,char *str4,char *str5,char *str6);

#endif


/*includes*/

/*defaines*/

/*structures*/

/*var*/

/*func*/