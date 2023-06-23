
#include "pwm_interface.h"
#include "../../MCAL/gpt/gpt_interface.h"

static uint8_t_ gl_arr_uint32_pwm_time_on[12];
static enu_gpio_pin_index_t_ gl_arr_enu_pin_index[12];


static void pwm0_task(void);
static void pwm1_task(void);
static void pwm2_task(void);
static void pwm3_task(void);
static void pwm4_task(void);
static void pwm5_task(void);
static void pwm6_task(void);
static void pwm7_task(void);
static void pwm8_task(void);
static void pwm9_task(void);
static void pwm10_task(void);
static void pwm11_task(void);

/**
 *	@brief				This function is used to initialize a pwm pin
 *	@param [in]		ptr_str_pwm_config							:	Ptr to the pwm instance structure
 *	@param [out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_TIMER_INIT_FAILED						:	In case of the timer initialization failed
 *	@return				PWM_PIN_INIT_FAILED							:	In case of the pin initialization failed 
 *	@return				PWM_INIT_FAILED									: In case of there is a timer available
 */
enu_error_status_t_ pwm_init(str_pwm_config_t_* ptr_str_pwm_config)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	if (ERROR_OK == gpt_get_unused_channel(&ptr_str_pwm_config->uint8_pwm_timer_index))
	{
		str_gpio_config_t_ str_pwm_pin;
		str_pwm_pin.enu_pin_direction = GPIO_OUTPUT;
		str_pwm_pin.enu_pin_index = ptr_str_pwm_config->uint8_pwm_pin_index;
		str_pwm_pin.enu_pin_output_current = GPIO_2mA;
		str_pwm_pin.enu_pin_mode = GPIO_DIO;
		gl_arr_enu_pin_index[ptr_str_pwm_config->uint8_pwm_timer_index] = ptr_str_pwm_config->uint8_pwm_pin_index;
		enu_ret_val = gpio_pin_init(&str_pwm_pin);
		if(ERROR_OK == enu_ret_val)
		{
			str_gpt_timer_config_t_ str_pwm_timer;
			str_pwm_timer.enu_timer_used = ptr_str_pwm_config->uint8_pwm_timer_index;
			str_pwm_timer.enu_timer_mode = GPT_PERIODIC;
			str_pwm_timer.enu_blocking_mode = GPT_NON_BLOCKING;
			str_pwm_timer.enu_counting_direction = GPT_COUNT_DOWN;

			if (ptr_str_pwm_config->uint32_pwm_frequency <= 10)
			{
				str_pwm_timer.enu_counting_standard = GPT_MS;
			}
			else
			{
				str_pwm_timer.enu_counting_standard = GPT_US;
			}
			enu_ret_val = gpt_init(&str_pwm_timer);
			if (ERROR_OK == enu_ret_val)
			{
				pwm_set_duty_cycle(ptr_str_pwm_config->uint8_pwm_timer_index, ptr_str_pwm_config->uint8_pwm_duty_cycle);
				pwm_set_frequency(ptr_str_pwm_config->uint8_pwm_timer_index, ptr_str_pwm_config->uint32_pwm_frequency);
				gpt_enable_notificatoin(ptr_str_pwm_config->uint8_pwm_timer_index);
				
				if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_TIMER0)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm0_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_TIMER1)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm1_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_TIMER2)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm2_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_TIMER3)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm3_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_TIMER4)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm4_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_TIMER5)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm5_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_W_TIMER0)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm6_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_W_TIMER1)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm7_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_W_TIMER2)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm8_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_W_TIMER3)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm9_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_W_TIMER4)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm10_task);
				}
				else if (ptr_str_pwm_config->uint8_pwm_timer_index == GPT_W_TIMER5)
				{
					gpt_set_callback(ptr_str_pwm_config->uint8_pwm_timer_index, pwm11_task);
				}

			}
			else
			{
				enu_ret_val = PWM_TIMER_INIT_FAILED;
			}
		}
		else
		{
			enu_ret_val = PWM_PIN_INIT_FAILED;
		}

	}
	else
	{
		enu_ret_val = PWM_INIT_FAILED;
	}
	return enu_ret_val;
}

/**
 *	@brief				This function is used to set frequency used
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[in]	uint32_pwm_frequency						: desired frequency
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_INVALID_FREQUENCY						:	In case of the timer initialization failed
 */
enu_error_status_t_ pwm_set_frequency(uint8_t_ uint8_pwm_timer_index, uint32_t_ uint32_pwm_frequency)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	
	uint64_t_ uint64_tick_time = 0;
	enu_gpt_counting_standard_t_ enu_counting_standard;

	if (uint32_pwm_frequency <= 10)
	{
		enu_counting_standard = GPT_MS;
		uint64_tick_time = (10 / uint32_pwm_frequency) ;
	}
	else
	{
		enu_counting_standard = GPT_US;
		uint64_tick_time = (10000 / uint32_pwm_frequency ) ;
	}

	
	enu_ret_val = gpt_set_time(uint8_pwm_timer_index, enu_counting_standard, uint64_tick_time);
	
	if(enu_ret_val != ERROR_OK)
	{
		enu_ret_val = PWM_INVALID_FREQUENCY;
	}
	else
	{
		/*SUCCESS*/
	}

	return enu_ret_val;

}

/**
 *	@brief				This function is used to set duty cycle
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[in]	uint8_pwm_duty_cycle						: desired duty cycle
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_INVALID_DUTY_CYCLE					:	In case of choosing wrong duty cycle
 */
enu_error_status_t_ pwm_set_duty_cycle(uint8_t_ uint8_pwm_timer_index, uint8_t_ uint8_pwm_duty_cycle)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	if (uint8_pwm_duty_cycle > 100)
	{
		enu_ret_val = PWM_INVALID_DUTY_CYCLE;
	}
	else
	{
		gl_arr_uint32_pwm_time_on[uint8_pwm_timer_index] = uint8_pwm_duty_cycle;
	}
	return enu_ret_val;
}


/**
 *	@brief				This function is used to start outputing pwm
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_FAILED											:	In case of PWM failed to start
 */
enu_error_status_t_ pwm_start(uint8_t_ uint8_pwm_timer_index)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	
	enu_ret_val = gpt_start_timer(uint8_pwm_timer_index);
	
	if(enu_ret_val != ERROR_OK)
	{
		enu_ret_val = PWM_FAILED;
	}
	else
	{
		/*SUCCESS*/
	}
	
	return enu_ret_val;
}

/**
 *	@brief				This function is used to stop outputing pwm
 *	@param 	[in]	uint8_pwm_timer_index						:	Timer used 
 *	@param 	[out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				PWM_FAILED											:	In case of PWM failed to stop
 */
enu_error_status_t_ pwm_stop(uint8_t_ uint8_pwm_timer_index)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	
	enu_ret_val = gpt_stop_timer(uint8_pwm_timer_index);
	
	enu_ret_val = gpio_pin_write(gl_arr_enu_pin_index[uint8_pwm_timer_index], GPIO_LOW);
	
	if(enu_ret_val != ERROR_OK)
	{
		enu_ret_val = PWM_FAILED;
	}
	else
	{
		/*SUCCESS*/
	}
	
	return enu_ret_val;
}

void pwm0_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[0])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[0], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[0], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm1_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[1])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[1], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[1], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm2_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[2])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[2], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[2], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}
void pwm3_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[3])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[3], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[3], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm4_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[4])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[4], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[4], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm5_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[5])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[5], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[5], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm6_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[6])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[6], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[6], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm7_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[7])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[7], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[7], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm8_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[8])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[8], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[8], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm9_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[9])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[9], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[9], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm10_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[10])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[10], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[10], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}

void pwm11_task(void)
{
	static uint8_t_ uint8_flag = 0, uint8_counter;
	uint8_counter++;
	if (uint8_counter <= gl_arr_uint32_pwm_time_on[11])
	{
		if (uint8_flag == 0)
		{
			uint8_flag = 1;
			gpio_pin_write(gl_arr_enu_pin_index[11], GPIO_HIGH);
		}
	}
	else
	{
		if (uint8_flag == 1)
		{
			uint8_flag = 0;
			gpio_pin_write(gl_arr_enu_pin_index[11], GPIO_LOW);
		}
		if (uint8_counter == 100)
		{
			uint8_counter = 0;
		}
	}
}
