




#include "led_interface.h"
#include "gpio_interface.h"

str_gpio_config_t_ str_ledr_config ;
str_gpio_config_t_ str_ledg_config ;
str_gpio_config_t_ str_ledb_config ;

/**
 *	@brief			This function is initalize pin 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */



enu_error_status_t_ led_init(uint8_t_ ledpin_index ){

enu_error_status_t_ en_a_error = ERROR_OK;
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ledpin_index % 10;
	uint8_port_num = ledpin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		en_a_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			en_a_error = LED_NOK;
		}
	
	else
	{ // red led 
		str_ledr_config.enu_pin_index=GPIO_PF1;
    str_ledr_config.enu_pin_direction= GPIO_OUTPUT;
		str_ledr_config.enu_pin_mode=GPIO_DIO;
    str_ledr_config.enu_pin_output_current=GPIO_2mA;
		gpio_pin_init(&str_ledr_config);
		//blue led 
		str_ledb_config.enu_pin_index=GPIO_PF2;
    str_ledb_config.enu_pin_direction= GPIO_OUTPUT;
		str_ledb_config.enu_pin_mode=GPIO_DIO;
    str_ledb_config.enu_pin_output_current=GPIO_2mA;
		gpio_pin_init(&str_ledb_config);
		//green led
    str_ledg_config.enu_pin_index=GPIO_PF3;
    str_ledg_config.enu_pin_direction= GPIO_OUTPUT;
		str_ledg_config.enu_pin_mode=GPIO_DIO;
    str_ledg_config.enu_pin_output_current=GPIO_2mA;
		gpio_pin_init(&str_ledg_config);
		en_a_error = ERROR_OK;
	}

}
}
/**
 *	@brief			This function is turn on led 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

enu_error_status_t_ led_on(uint8_t_ ledpin_index ){
	
	enu_error_status_t_ en_a_error = ERROR_OK;
		uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ledpin_index % 10;
	uint8_port_num = ledpin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		en_a_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			en_a_error = LED_NOK;
		}
	
	else
	{ 
		gpio_pin_Write( ledpin_index, GPIO_HIGH);
		en_a_error = ERROR_OK;
	}
}}
	
/**
 *	@brief			This function is turn off led 
 *	@param [in]		ledpin				        	:	Pin index used
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			LED_NOK        			:	In case of wrong pin index
 */

	enu_error_status_t_ led_off(uint8_t_ ledpin_index ){
	
	enu_error_status_t_ en_a_error = ERROR_OK;
		uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ledpin_index % 10;
	uint8_port_num = ledpin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		en_a_error = LED_NOK;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			en_a_error = LED_NOK;
		}
	else
	{ 
		gpio_pin_Write( ledpin_index, GPIO_LOW);
		en_a_error = ERROR_OK;
	}
	
}}