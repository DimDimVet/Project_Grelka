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
	
#endif


/*includes*/

/*defaines*/

/*structures*/

/*var*/

/*func*/