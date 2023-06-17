


#include "button_config.h"
#include "common.h"

typedef enum
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED = 1
} Button_State;


/**
 *	@brief			This function is initalize button 
 *	@param [in]		ptr_func							:	pointer to callback
 *	@return			ERROR_OK					        	:	In case of successeion
 *	@return			bUTTON_NOK        			     :	In case of wrong pin index
 */

enu_error_status_t_ button_init(void(*ptr_func)(void));





/**
 *	@brief			This function is to get button  state
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@return			BUTTON PRESSED					        	:	In case of button pressed
 *	@return			BUTTON_RELEASED        			     :	In case of button not pressed
 */



enu_error_status_t_ button_pressed(uint8_t_ uint8_button_pin, uint8_t_* uint8_button_state);
