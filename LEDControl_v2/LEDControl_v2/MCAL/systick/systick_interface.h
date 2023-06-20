/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *		@file					systick_interface.h
 * 		@date					6/19/2023
 *  	@brief			
 *		@email 				ahmedhesham606@icloud.com
 *  	@author				Ahmad Hesham
 *		@description	
 * 
 */
#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "common.h"
#include "bit_math.h"
#include "systick_config.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**
 *	@brief				This function is used to initialize system tick and load its counter
 *	@param [in]		uint32_delay_time_ms	:	desired time to interrupt after it
 *	@param [out]	none
 *	@return				ERROR_OK							:	In case of success
 *	@return				SYSTICK_WRONG_VALUE		:	In case of uint32_delay_time_ms = 0
 */
enu_error_status_t_ systick_init(uint32_t_ uint32_delay_time_ms);

/**
 *	@brief				This function is used to reload systick
 *	@param [in]		uint32_delay_time_ms	:	desired time to interrupt after it
 *	@param [out]	none
 *	@return				ERROR_OK							:	In case of success
 *	@return				SYSTICK_WRONG_VALUE		:	In case of uint32_delay_time_ms = 0
 */
enu_error_status_t_ systick_reload(uint32_t_ uint32_delay_time_ms);

/**
 *	@brief				This function is used to disable systick
 *	@param [in]		none
 *	@param [out]	none
 *	@return				ERROR_OK							:	In case of success
 */
enu_error_status_t_ systick_disable(void);

/**
 *	@brief				This function is used to enable systick
 *	@param [in]		none
 *	@param [out]	none
 *	@return				ERROR_OK							:	In case of success
 */
enu_error_status_t_ systick_enable(void);

/**
 *	@brief				This function is used to set callback funtion for systick interrupt
 *	@param [in]		none
 *	@param [out]	none
 *	@return				ERROR_OK							:	In case of success
 * 	@return				PASSING_NULL_PTR			: In case of passing null pointer
 */
enu_error_status_t_ systick_set_callback(void (*a_void_ptr) (void));
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif  /* M_SYSTICK_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: M_SysTick_Interface.h
 *********************************************************************************************************************/
