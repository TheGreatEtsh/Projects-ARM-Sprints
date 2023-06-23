/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *	@file			pwm_interface.h
 * 	@date			22/6/2023	1:01 PM
 *  @brief			Interface file for PWM Manager driver
 *	@email 			ahmedhesham606@icloud.com
 *  @author			Ahmad Hesham
 *
 */
#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

/**----------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------*/
#include "../../LIB/common.h"
#include "../../MCAL/gpio/gpio_interface.h"



typedef struct
{
	uint8_t_				uint8_pwm_timer_index;
	enu_gpio_pin_index_t_	uint8_pwm_pin_index;
	uint32_t_				uint32_pwm_frequency;
	uint8_t_				uint8_pwm_duty_cycle;
}str_pwm_config_t_;


/**
 *	@brief				This function is used to initialize a pwm pin
 *	@param [in]		ptr_str_pwm_config							:	Ptr to the pwm instance structure
 *	@param [out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_TIMER_INIT_FAILED						:	In case of the timer initialization failed
 *	@return				PWM_PIN_INIT_FAILED							:	In case of the pin initialization failed 
 *	@return				PWM_INIT_FAILED									: In case of there is a timer available
 */
enu_error_status_t_ pwm_init(str_pwm_config_t_* ptr_str_pwm_config);

/**
 *	@brief				This function is used to set duty cycle
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[in]	uint8_pwm_duty_cycle						: desired duty cycle
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_INVALID_DUTY_CYCLE					:	In case of choosing wrong duty cycle
 */
enu_error_status_t_ pwm_set_duty_cycle(uint8_t_ uint8_pwm_timer_index, uint8_t_ uint8_pwm_duty_cycle);

/**
 *	@brief				This function is used to set frequency used
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[in]	uint32_pwm_frequency						: desired frequency
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_INVALID_FREQUENCY						:	In case of the timer initialization failed
 */
enu_error_status_t_ pwm_set_frequency(uint8_t_ uint8_pwm_timer_index, uint32_t_ uint32_pwm_frequency);

/**
 *	@brief				This function is used to start outputing pwm
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_FAILED											:	In case of PWM failed to start
 */
enu_error_status_t_ pwm_start(uint8_t_ uint8_pwm_timer_index);

/**
 *	@brief				This function is used to stop outputing pwm
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_FAILED											:	In case of PWM failed to stop
 */
enu_error_status_t_ pwm_stop(uint8_t_ uint8_pwm_timer_index);


#endif  /* PWM_INTERFACE_H */

 /**----------------------------------------------------------
 *  END OF FILE: pwm_interface.h
 *----------------------------------------------------------*/
