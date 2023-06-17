


#include "button_config.h"
#include "common.h"
#include "gpio_interface.h"

typedef enum
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED = 1
} Button_State;


/**
 *	@brief			This function is initalize button 
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@return			ERROR_OK					        	:	In case of successeion
 *	@return			bUTTON_NOK        			     :	In case of wrong pin index
 */

enu_error_status_t_ button_init(uint8_t_ buttonpin );





/**
 *	@brief			This function is to get button  state
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@return			BUTTON PRESSED					        	:	In case of button pressed
 *	@return			BUTTON_RELEASED        			     :	In case of button not pressed
 */



enu_error_status_t_ Button_GetState(uint8_t_ buttonpin, enu_gpio_pin_internal_attach_t_ ButtonAttach, uint8_t_ *buttonState);