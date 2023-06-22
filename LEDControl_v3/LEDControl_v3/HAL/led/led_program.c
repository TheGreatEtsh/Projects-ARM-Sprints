




#include "led_interface.h"
#include "gpio_interface.h"

str_gpio_config_t_ gl_str_ledr_config ;
str_gpio_config_t_ gl_str_ledg_config ;
str_gpio_config_t_ gl_str_ledb_config ;

/**
 *	@brief			This function is initalize pin 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */



enu_error_status_t_ led_init(void)
{

	enu_error_status_t_ enu_error = ERROR_OK;
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = RED_LED % 10;
	uint8_port_num = RED_LED / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_error = LED_NOK;
		}
	
		else
		{ // red led 
			gl_str_ledr_config.enu_pin_index= RED_LED;
			gl_str_ledr_config.enu_pin_direction= GPIO_OUTPUT;
			gl_str_ledr_config.enu_pin_mode=GPIO_DIO;
			gl_str_ledr_config.enu_pin_output_current=GPIO_2mA;
			gpio_pin_init(&gl_str_ledr_config);
			//blue led 
			gl_str_ledb_config.enu_pin_index= BLUE_LED;
			gl_str_ledb_config.enu_pin_direction= GPIO_OUTPUT;
			gl_str_ledb_config.enu_pin_mode=GPIO_DIO;
			gl_str_ledb_config.enu_pin_output_current=GPIO_2mA;
			gpio_pin_init(&gl_str_ledb_config);
			//green led
			gl_str_ledg_config.enu_pin_index= GREEN_LED;
			gl_str_ledg_config.enu_pin_direction= GPIO_OUTPUT;
			gl_str_ledg_config.enu_pin_mode=GPIO_DIO;
			gl_str_ledg_config.enu_pin_output_current=GPIO_2mA;
			gpio_pin_init(&gl_str_ledg_config);
			
		}
	}
	return enu_error;
}
/**
 *	@brief			This function is turn on led 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

enu_error_status_t_ led_on(uint8_t_ ledpin_index ){
	
	enu_error_status_t_ enu_error = ERROR_OK;
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ledpin_index % 10;
	uint8_port_num = ledpin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_error = LED_NOK;
		}
	
		else
		{ 
			gpio_pin_write( ledpin_index, GPIO_HIGH);
		}
	}
	return enu_error;
}
	
/**
 *	@brief			This function is turn off led 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

	enu_error_status_t_ led_off(uint8_t_ ledpin_index ){
	
	enu_error_status_t_ enu_error = ERROR_OK;
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ledpin_index % 10;
	uint8_port_num = ledpin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_error = LED_NOK;
		}
		else
		{ 
			gpio_pin_write( ledpin_index, GPIO_LOW);
		}
	
	}
	return enu_error;
}
	
enu_error_status_t_ led_toggle(uint8_t_ ledpin_index)
{
	enu_error_status_t_ enu_error = ERROR_OK;
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ledpin_index % 10;
	uint8_port_num = ledpin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_error = LED_NOK;
		}
		else
		{ 
			gpio_pin_toggle( ledpin_index);
		}
	
	}
	return enu_error;
}
