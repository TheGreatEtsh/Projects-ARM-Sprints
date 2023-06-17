/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *      @File  			nvic_interface.h
 *      @date			15/6/2023	5:58
 *  	@brief			Interface file for NVIC driver
 *		@author			Ahmad Hesham
 *      @email			ahmedhesham606@icloud.com
 */


#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/**----------------------------------------------------------
 * INCLUDES
 *----------------------------------------------------------*/
#include "..\..\LIB\common.h"
#include "..\..\LIB\bit_math.h"

/**----------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
 *----------------------------------------------------------*/








/**----------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
 *----------------------------------------------------------*/
 


/**----------------------------------------------------------
 *  GLOBAL DATA PROTOTYPES
 *----------------------------------------------------------*/



/**----------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
 *----------------------------------------------------------*/
/**
 *	@brief			This function is used to initialize a specific pin
 *	@param [in]		ptr_str_gpio_config				:	Ptr to the gpio instance structure
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 *	@return			GPIO_INVALID_PIN_MODE			:	In case of wrong mode choosen
 *	@return			GPIO_INVALID_PIN_DIRECTION		:	In case of wrong direction choosen
 *	@return			GPIO_INVALID_OP_CURRENT			:	In case of wrong current choosen
 *	@return			GPIO_INVALID_INTERNAL_ATTACH	:	In case of wrong internal attach
 */


#endif  /* NVIC_INTERFACE_H */

/**----------------------------------------------------------
 *  END OF FILE: nvic_interface.h
 *----------------------------------------------------------*/
