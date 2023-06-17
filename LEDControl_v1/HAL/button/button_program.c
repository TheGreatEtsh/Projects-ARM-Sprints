





#include "button_interface.h"
#include "gpio_interface.h"

str_gpio_config_t_ str_button_config ;

/**
 *	@brief			This function is initalize button 
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@return			ERROR_OK					        	:	In case of successeion
 *	@return			bUTTON_NOK        			     :	In case of wrong pin index
 */

enu_error_status_t_ button_init(uint8_t_ buttonpin ){

enu_error_status_t_ en_a_error = ERROR_OK;
	if (buttonpin > GPIO_PF7)
	{
		en_a_error = BUTTON_NOK;
	}
	
	else
	{ // button
		str_button_config.enu_pin_index=GPIO_PF0;
    str_button_config.enu_pin_direction= GPIO_INPUT;
		str_button_config.enu_pin_mode=PORT_DIO;
    str_button_config.enu_pin_output_current=GPIO_2mA;
		gpio_pin_init(&str_button_config);
		en_a_error = ERROR_OK;
	}

}


/**
 *	@brief			This function is to get button  state
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@return			BUTTON PRESSED					        	:	In case of button pressed
 *	@return			BUTTON_RELEASED        			     :	In case of button not pressed
 */



enu_error_status_t_ Button_GetState(uint8_t_ buttonpin, enu_gpio_pin_internal_attach_t_ ButtonAttach, uint8_t_ *buttonState)
{
	enu_error_status_t_ en_a_error = ERROR_OK;
	enu_gpio_pin_level_t_ testLevel = GPIO_LOW;
	if (buttonpin > GPIO_PF7)
	{
		en_a_error = BUTTON_NOK;
	}
	
	else
	{ 
	if (ButtonAttach == GPIO_PULLUP)
		testLevel = GPIO_LOW;
	else if (ButtonAttach == GPIO_PULLDOWN)
		testLevel = GPIO_HIGH;
	
	if (gpio_pin_read( buttonpin,buttonState ) == testLevel)
	{
		/* Random short delay */
		for(int i = 0; i < 1000; i++);
		
		if (gpio_pin_read( buttonpin,buttonState ) == testLevel)
		{
			return ERROR_OK;
		}
	}
}
}