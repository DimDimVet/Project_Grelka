#ifndef HEHAL_H_
#define HEHAL_H_

/*includes*/
#include "stm32f407xx.h"
#include "stm32f4xx.h"

/*defaines*/
#define ENABLE_BIT(reg, bit) ((reg) |= (bit)) 
#define DISABLE_BIT(reg, bit) ((reg) &= ~(bit)) 
#define Read_BIT(reg, bit)    ((reg) & (bit)) 
#define Write_REG(REG, VAL)   ((REG) = (VAL))
#define Read_REG(REG)         ((REG))
#define Clear_REG(REG)        ((REG) = (0x0))	

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