

#include "common.h"
#include "led_config.h"
#include "gpio_interface.h"




/**
 *	@brief			This function is initalize pin 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

enu_error_status_t_ led_init(void);

/**
 *	@brief			This function is turn on led 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

enu_error_status_t_ led_on(uint8_t_ ledpin_index );

/**
 *	@brief			This function is turn off led 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

enu_error_status_t_ led_off(uint8_t_ ledpin_index );
