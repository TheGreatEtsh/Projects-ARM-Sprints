/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *		\file			systick_private.h
 * 		\date			19/6/2023
 *  	\brief			
 *		\email 			ahmedhesham606@icloud.com
 *  	\author			Ahmad Hesham
 *		\description
 * 
 *********************************************************************************************************************/
#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define CORTEXM_CORE_PERIPHERALS_BASE_ADDRESS			0xE000E000

#define STCTRL			(*((volatile uint32_t_*)(CORTEXM_CORE_PERIPHERALS_BASE_ADDRESS+0x010)))
#define STRELOAD		(*((volatile uint32_t_*)(CORTEXM_CORE_PERIPHERALS_BASE_ADDRESS+0x014)))
#define	STCURRENT		(*((volatile uint32_t_*)(CORTEXM_CORE_PERIPHERALS_BASE_ADDRESS+0x018)))






/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif  /* SYSTICK_PRIVATE_H*/

/**********************************************************************************************************************
 *  END OF FILE: systick_private.h
 *********************************************************************************************************************/
