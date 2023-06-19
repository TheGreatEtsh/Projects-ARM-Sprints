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
#include "systick_interface.h"
/**----------------------------------------------------------
 *  STATIC FUNCTION PROTOTYPES
 *----------------------------------------------------------*/
static void app_button_task(void);
static void app_systick_task(void);
static void app_led_task(void);
typedef enum
{
	FIRST_PRESS,
	SECOND_PRESS,
	THIRD_PRESS,
	FOURTH_PRESS,
	FIFTH_PRESS
}enu_app_pressing_state_t_;

/**----------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTAIONS
 *----------------------------------------------------------*/
/**
 *	@brief			This function is used to initialize drivers used
 *	@param [in]		none
 *	@param [out]	none
 *	@return			none
 */
void app_init(void)
{
	//button_init(button_task);
	led_init();
	button_init(NULL_PTR);
	systick_init(APP_SYSTICK_TIME);
	systick_set_callback(app_systick_task);
	
	
}

/**----------------------------------------------------------
 *  STATIC FUNCTION IMPLEMENTATION
 *----------------------------------------------------------*/
/**
 *	@brief			This function is the called back when button pressed
 *	@param [in]		none
 *	@param [out]	none
 *	@return			none
 */

static void app_led_task(void)
{
	static enu_app_pressing_state_t_ enu_pressing_state = FIRST_PRESS;
	switch (enu_pressing_state)
	{
	case FIRST_PRESS:
		led_on(RED_LED);
		led_off(GREEN_LED);
		led_off(BLUE_LED);
		enu_pressing_state = SECOND_PRESS;
		break;

	case SECOND_PRESS:
		led_on(GREEN_LED);
		led_off(RED_LED);
		led_off(BLUE_LED);
		enu_pressing_state = THIRD_PRESS;
		break;

	case THIRD_PRESS:
		led_on(BLUE_LED);
		led_off(GREEN_LED);
		led_off(RED_LED);
		enu_pressing_state = FOURTH_PRESS;
		break;

	case FOURTH_PRESS:
		led_on(RED_LED);
		led_on(GREEN_LED);
		led_on(BLUE_LED);
		enu_pressing_state = FIFTH_PRESS;
		break;

	case FIFTH_PRESS:
		led_off(RED_LED);
		led_off(GREEN_LED);
		led_off(BLUE_LED);
		enu_pressing_state = FIRST_PRESS;
		break;
	
	default:
		break;
	}
}
static void app_button_task(void)
{
	static uint8_t_ uint8_still_pressed = 0, uint8_turn_on_counter = 0, uint8_led_is_on = 0;
	uint8_t_ uint8_button_state = 0;
	button_get_state(SW_1,&uint8_button_state);
	if (uint8_button_state == BUTTON_PRESSED)
	{
		if (uint8_still_pressed == FALSE)
		{
			uint8_still_pressed = TRUE;
		}
		else if (uint8_still_pressed == TRUE)
		{
			app_led_task();
			uint8_led_is_on = TRUE;
			uint8_still_pressed = FALSE;
			uint8_turn_on_counter = APP_LED_ON_TIME;
		}
	}
	
	if(uint8_led_is_on == TRUE && uint8_turn_on_counter > 0)
	{
		uint8_turn_on_counter--;
		if(uint8_turn_on_counter == 0)
		{
			led_off(RED_LED);
			led_off(GREEN_LED);
			led_off(BLUE_LED);
			uint8_led_is_on = FALSE;
		}
	}
}

static void app_systick_task(void)
{
	app_button_task();
}
/**********************************************************************************************************************
 *  END OF FILE: app.c
 *********************************************************************************************************************/
