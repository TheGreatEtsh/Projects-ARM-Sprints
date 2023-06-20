#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H



#include "button_config.h"
#include "common.h"

typedef enum
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED = 1
} enu_button_state_t_;


/**
 *	@brief			This function is used for initalizing button 
 *	@param [in]		ptr_func						:	pointer to callback
 *	@return			ERROR_OK					    :	In case of successeion
 *  @return			PASSING_NULL_PTR				:	In case of passing null pointer
 *	@return			BUTTON_NOK        			    :	In case of wrong pin index
 */
enu_error_status_t_ button_init(void(*ptr_func)(void));

/**
 *	@brief			This function is used for getting button  state
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@param [out]	ptr_uint8_button_state				:	returns button state 
 *	@return			ERROR_OK					    :	In case of successeion
 *	@return			BUTTON_NOK        			    :	In case of wrong pin index
 */
enu_error_status_t_ button_get_state(uint8_t_ uint8_button_pin, uint8_t_* ptr_uint8_button_state);

#endif  /* BUTTON_INTERFACE_H */

/**----------------------------------------------------------
 *  END OF FILE: button_interface.h
 *----------------------------------------------------------*/
