





#include "button_interface.h"
#include "gpio_interface.h"

void (*ptr_func_button_callback)(void) = NULL_PTR;

str_gpio_config_t_ gl_str_button_config ;


/**
 *	@brief			This function is used for initalizing button
 *	@param [in]		ptr_func						:	pointer to callback
 *	@return			ERROR_OK					    :	In case of successeion
 *  @return			PASSING_NULL_PTR				:	In case of passing null pointer
 *	@return			BUTTON_NOK        			    :	In case of wrong pin index
 */
enu_error_status_t_ button_init(void(*ptr_func)(void))
{

	enu_error_status_t_ enu_error = ERROR_OK;
	
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = SW_1 % 10;
	uint8_port_num = SW_1 / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_error = BUTTON_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_error = BUTTON_NOK;
		}
		else
		{ // button
			gl_str_button_config.enu_pin_index = SW_1;
			gl_str_button_config.enu_pin_direction = GPIO_INPUT;
			gl_str_button_config.enu_pin_mode = GPIO_DIO;
			gl_str_button_config.enu_pin_internal_attach = GPIO_PULLUP;
			gpio_pin_init(&gl_str_button_config);
			gpio_pin_enable_notification(SW_1);

			if (NULL_PTR == ptr_func)
			{
				enu_error = PASSING_NULL_PTR;
			}
			else
			{
				gpio_pin_set_callback(SW_1, ptr_func);
				ptr_func_button_callback = ptr_func;
			}
		}
	}
	return enu_error;
}

/**
 *	@brief			This function is used for getting button  state
 *	@param [in]		buttonpin				        	:	Pin index used
 *	@param [out]	ptr_uint8_button_state				:	returns button state
 *	@return			ERROR_OK					    :	In case of successeion
 *	@return			BUTTON_NOK        			    :	In case of wrong pin index
 */
enu_error_status_t_ button_get_state(uint8_t_ uint8_button_pin, uint8_t_ *uint8_button_state)
{
	enu_error_status_t_ enu_error = ERROR_OK;
	enu_gpio_pin_level_t_ enu_test_level = GPIO_LOW;
	enu_gpio_pin_internal_attach_t_ enu_button_attach = gl_str_button_config.enu_pin_internal_attach;
	uint8_t_ uint8_pin_state;

	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = uint8_button_pin % 10;
	uint8_port_num = uint8_button_pin / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_error = BUTTON_NOK;	
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_error = BUTTON_NOK;
		}
	
		else
		{ 
			if (enu_button_attach == GPIO_PULLUP)
			{
				enu_test_level = GPIO_LOW;
			}
			else if (enu_button_attach == GPIO_PULLDOWN)
			{
				enu_test_level = GPIO_HIGH;
			}
			else
			{
				enu_error = BUTTON_NOK;
			}
			gpio_pin_read(uint8_button_pin, &uint8_pin_state);
			if (uint8_pin_state == enu_test_level)
			{
				*uint8_button_state = BUTTON_PRESSED;
			}
			else
			{
				*uint8_button_state = BUTTON_RELEASED;
			}
		}
//				/* Random short delay */
//				for(uint32_t_ uint32_looping_variable = 0; uint32_looping_variable < 1000; uint32_looping_variable++);
//				gpio_pin_read(uint8_button_pin, uint8_button_state);
//				if (*uint8_button_state == enu_test_level)
//				{
//					while (*uint8_button_state == enu_test_level)
//					{
//						gpio_pin_read(uint8_button_pin, uint8_button_state);
//					}
//					ptr_func_button_callback();
//				}
//				else
//				{
//					/*DO NOTHING*/
//				}
//			}
//			else
//			{
//				/*DO NOTHING*/
//			}
//		}
	}
	return enu_error;
}

