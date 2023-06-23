/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *      @File  			app.h
 *      @date			18/6/2023	2:26 PM
 *  	@brief			interface file for application
 *		@author			Ahmad Hesham
 *      @email			ahmedhesham606@icloud.com
 */



#include "app.h"
#include "led_interface.h"
#include "button_interface.h"
#include "gpt_interface.h"
#include "pwm_interface.h"
/**----------------------------------------------------------
 *  STATIC FUNCTION PROTOTYPES
 *----------------------------------------------------------*/
static void app_button_task(void);
typedef enum
{
	FIRST_PRESS,
	SECOND_PRESS,
	THIRD_PRESS,
	FOURTH_PRESS,
	FIFTH_PRESS
}enu_app_pressing_state_t_;


str_pwm_config_t_ str_pwm_green_led;
/**----------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTAIONS
 *----------------------------------------------------------*/
/**
 *	@brief				This function is used to initialize drivers used
 *	@param [in]		none
 *	@param [out]	none
 *	@return				none
 */
void app_init(void)
{
	button_init(app_button_task);
	
	str_pwm_green_led.uint8_pwm_pin_index = GPIO_PF3;
	str_pwm_green_led.uint32_pwm_frequency = 2;
	str_pwm_green_led.uint8_pwm_duty_cycle = 0;
	
	pwm_init(&str_pwm_green_led);
	pwm_start(str_pwm_green_led.uint8_pwm_timer_index);
}

/**----------------------------------------------------------
 *  STATIC FUNCTION IMPLEMENTATION
 *----------------------------------------------------------*/

/**
 *	@brief				This function is the called to perform buttons task -get buttons state-
 *	@param [in]		none
 *	@param [out]	none
 *	@return				none
 */
static void app_button_task(void)
{
	static enu_app_pressing_state_t_ enu_pressing_state= FIRST_PRESS;
	volatile uint8_t_ uint8_button_state;
	
	if(enu_pressing_state == FIRST_PRESS)
	{
		pwm_set_duty_cycle(str_pwm_green_led.uint8_pwm_timer_index,30);
		enu_pressing_state = SECOND_PRESS;
	}
	else if (enu_pressing_state == SECOND_PRESS)
	{
		pwm_set_duty_cycle(str_pwm_green_led.uint8_pwm_timer_index,60);
		enu_pressing_state = THIRD_PRESS;
	}
	else if (enu_pressing_state == THIRD_PRESS)
	{
		pwm_set_duty_cycle(str_pwm_green_led.uint8_pwm_timer_index,90);
		enu_pressing_state = FOURTH_PRESS;
	}
	else if (enu_pressing_state == FOURTH_PRESS)
	{
		pwm_set_duty_cycle(str_pwm_green_led.uint8_pwm_timer_index,0);
		enu_pressing_state = FIRST_PRESS;
	}
	for(volatile uint32_t_ uint32_looping_var = 0; uint32_looping_var < 1000; uint32_looping_var++)
	{
		for(volatile uint32_t_ uint32_looping_var = 0; uint32_looping_var < 500; uint32_looping_var++)
		{
		}
	}
	button_get_state(SW_1, &uint8_button_state);
	while(uint8_button_state == BUTTON_PRESSED)
	{
		button_get_state(SW_1, &uint8_button_state);
	}
}

/**********************************************************************************************************************
 *  END OF FILE: app.c
 *********************************************************************************************************************/
