




#include "led_interface.h"
#include "gpio_interface.h"

str_gpio_config_t_ str_ledr_config ;

enu_error_status_t_ led_init(){

enu_error_status_t_ en_a_error = ERROR_OK;
	if (enu_gpio_pin_index_t_.enu_pin_index > GPIO_PF7)
	{
		en_a_error = LED_NOK;
	}
	
	else
	{
		str_ledr_config.enu_pin_index=GPIO_PF1;
    str_ledr_config.enu_pin_direction
         
		en_a_error = ERROR_OK;
	}

}