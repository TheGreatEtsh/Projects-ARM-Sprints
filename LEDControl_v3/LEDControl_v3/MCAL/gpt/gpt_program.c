/**
 *  FILE DESCRIPTION
 *	-----------------------------------------------------------------------------------------------------------------
 *  @file			gpt_program.c
 *  @date			20/6/2023	9:45
 *	@brief			program file for GPT driver
 *  @email 		ahmedhesham606@icloud.com	
 *	@author		Ahmad Hesham
 */
 
/**----------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------*/
#include "gpt_interface.h"
#include "gpt_config.h"
#include "gpt_private.h"
#include "TM4C123.h"
/**----------------------------------------------------------
 *  LOCAL DATA
 *----------------------------------------------------------*/
static uint8_t_ gl_arr_uint8_gpt_used[12] = {
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE,
										FALSE
									};

static uint32_t_ gl_arr_uint32_number_of_ovfs[12] = {0}, gl_arr_uint32_reloading_value[12] = {0};

static ptr_gpt_callback_t_ gl_arr_ptr_callback[12] = { 
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR,
										NULL_PTR
									};

/**----------------------------------------------------------
 *  GLOBAL DATA
 *----------------------------------------------------------*/

/**----------------------------------------------------------
 *  LOCAL FUNCTION PROTOTYPES
 *----------------------------------------------------------*/

/**----------------------------------------------------------
 *  LOCAL FUNCTIONS
 *----------------------------------------------------------*/

/**----------------------------------------------------------
 *  GLOBAL FUNCTIONS
 *----------------------------------------------------------*/
/**
 *	@brief			This function is used to initialize a specific general purpose timer
 *	@param [in]		ptr_str_gpt_timer_config			:	Ptr to the timer instance structure
 *	@param [out]	none	
 *	@return			ERROR_OK												:	In case of success
 *	@return			GPT_INVALID_TIMER_INDEX					:	In case of choosing wrong channel index
 *	@return			GPT_INITIALIZED									:	In case of choosing initialized channel 
 *	@return			GPT_INVALID_STANDARD						: In case of choosing wrong standard
 *	@return			GPT_INVALID_BLOCKING_MODE				: In case of choosing wrong blocking mode
 *	@return			GPT_INVALID_COUNTING_DIRECTION	: In case of choosing wrong blocking mode
 *	@return			GPT_INVALID_GPT_MODE						: In case of choosing wrong mode
 */
enu_error_status_t_ gpt_init(str_gpt_timer_config_t_* ptr_str_gpt_timer_config)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	enu_gpt_timer_used_t_ enu_timer_used = ptr_str_gpt_timer_config->enu_timer_used;
	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		if (TRUE == gl_arr_uint8_gpt_used[enu_timer_used])
		{
			enu_ret_val = GPT_INITIALIZED;
		}
		else
		{
			/**
			 *	0. Enable clock gate to the preipheral
			 */

			if (GPT_W_TIMER0 > enu_timer_used)
			{
				SET_BIT(RCGCTIMER_, enu_timer_used);
			}
			else
			{
				SET_BIT(RCGCWTIMER_, (enu_timer_used % 6));
			}

			/**
			 *	1. Ensure the timer is disabled (the TnEN bit in GPTMCTL register is cleared before making any changes
			 */
			GPTMCTL(enu_timer_used).R = 0;

			/**
			 *	2. Write the GPTM Configuration Register(GPTMCFG) with a value of 0x0000.0000 for 32 bits or 64 bits for wide
			 *	or 0x00000004 for using 16 bits and 32 bits for wide timers
			 */
			GPTMCFG(enu_timer_used) = 0x00000004;

			/**
			 *	3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
			 * 		a. Assign mode value in TnMR's bits.
			 *		b. Assign direction value in TnCDIR bit
			 */
			if (GPT_PERIODIC == ptr_str_gpt_timer_config->enu_timer_mode || GPT_ONE_SHOT == ptr_str_gpt_timer_config->enu_timer_mode)
			{
				GPTMTAMR(enu_timer_used).B.TAMR = ptr_str_gpt_timer_config->enu_timer_mode;

				if (GPT_COUNT_UP >= ptr_str_gpt_timer_config->enu_counting_direction)
				{
					GPTMTAMR(enu_timer_used).B.TACDIR = ptr_str_gpt_timer_config->enu_counting_direction;

					/**
					 *	4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TNCDIR bits in the GPTMTnMR register
					 * 	to select whether to capture the value of free-running timer, configure an additional trigger
					 * 	or interrupt
					 */
					if (GPT_NON_BLOCKING == ptr_str_gpt_timer_config->enu_blocking_mode)
					{
						SET_BIT(GPTMIMR(enu_timer_used), 0);
						if (GPT_US == ptr_str_gpt_timer_config->enu_counting_standard)
						{
							GPTMTAPR(enu_timer_used) = 15;
						}
						else if (GPT_S == ptr_str_gpt_timer_config->enu_counting_standard)
						{
							GPTMTAPR(enu_timer_used) = 249;
						}
						else if  (GPT_MS == ptr_str_gpt_timer_config->enu_counting_standard)
						{
							GPTMTAPR(enu_timer_used) = 63;
						}
						else
						{
							enu_ret_val = GPT_INVALID_STANDARD;
						}
					}
					else if (GPT_BLOCKING == ptr_str_gpt_timer_config->enu_blocking_mode)
					{
						/*TODO: */
					}
					else
					{
						enu_ret_val = GPT_INVALID_BLOCKING_MODE;
					}
				}
				else
				{
					enu_ret_val = GPT_INVALID_COUNTING_DIRECTION;
				}
			}
			else
			{
				enu_ret_val = GPT_INVALID_GPT_MODE;
			}


			gl_arr_uint8_gpt_used[enu_timer_used] = TRUE;
		}
	}
	return enu_ret_val;
}

/**
 *	@brief			This function is used to stop a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_stop_timer(enu_gpt_timer_used_t_ enu_timer_used)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	
	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		GPTMCTL(enu_timer_used).R = 0;
	}
	return enu_ret_val;
}

/**
 *	@brief			This function is used to load timer interval
 *	@param [in]		enu_timer_used						:	Timer index used
 *	@param [in]		enu_counting_standard			:	Counting Standard -Seconds, mSeconds, uSeconds-
 *	@param [in]		uint32_desired_time				:	Value to be loaded
 *	@param [out]	none
 *	@return			ERROR_OK										:	In case of success
 *	@return			GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 *	@return			GPT_INVALID_VALUE						:	In case of loading Zero
 *	@return			GPT_INVALID_STANDARD				:	In case of choosing a wrong standard
 */
enu_error_status_t_ gpt_set_time(enu_gpt_timer_used_t_ enu_timer_used, enu_gpt_counting_standard_t_ enu_counting_standard, uint64_t_ uint64_desired_time)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	uint32_t_ uint32_tick_time = 0;
	uint64_t_ uint64_number_of_ticks = 0;
	//uint64_t_ uint64_max_delay_time = 0;
	

	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		GPTMCTL(enu_timer_used).R = 0;
		
		if (GPT_US == enu_counting_standard)
		{
			GPTMTAPR(enu_timer_used) = 15;
	
			uint64_number_of_ticks = uint64_desired_time - 1;
			gl_arr_uint32_reloading_value[enu_timer_used] = uint64_number_of_ticks %65536;
			gl_arr_uint32_number_of_ovfs[enu_timer_used] = uint64_number_of_ticks / 65536;
			
			if (0 != gl_arr_uint32_reloading_value[enu_timer_used])
			{
				gl_arr_uint32_number_of_ovfs[enu_timer_used]++;
				GPTMTAILR(enu_timer_used) = gl_arr_uint32_reloading_value[enu_timer_used];
			}
			else
			{
				GPTMTAILR(enu_timer_used) = 0xFFFFFFFF;
			}

		}
		else if (GPT_S == enu_counting_standard)
		{
			GPTMTAPR(enu_timer_used) = 249;

			GPTMTAILR(enu_timer_used) = 64000;
			
			gl_arr_uint32_number_of_ovfs[enu_timer_used] = uint64_desired_time;
		}
		else if (GPT_MS == enu_counting_standard)
		{
			GPTMTAPR(enu_timer_used) = 63;
			
			uint32_tick_time = 64 / 16;
			
			uint64_number_of_ticks = (uint64_desired_time * 1000) / uint32_tick_time;
			uint64_number_of_ticks--;
			gl_arr_uint32_reloading_value[enu_timer_used] = uint64_number_of_ticks % 65536;
			gl_arr_uint32_number_of_ovfs[enu_timer_used] = uint64_number_of_ticks / 65536;

			if (0 != gl_arr_uint32_reloading_value[enu_timer_used])
			{
				gl_arr_uint32_number_of_ovfs[enu_timer_used]++;
				GPTMTAILR(enu_timer_used) = gl_arr_uint32_reloading_value[enu_timer_used];
			}
			else
			{
				GPTMTAILR(enu_timer_used) = 0xFFFFFFFF;
			}

		}
		else
		{
			enu_ret_val = GPT_INVALID_STANDARD;
		}
	
	
	}
	return enu_ret_val;
}

/**
 *	@brief				This function is used to start a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_start_timer(enu_gpt_timer_used_t_ enu_timer_used)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	
	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		GPTMCTL(enu_timer_used).R = 1;
	}
	return enu_ret_val;
}

/**
 *	@brief				This function is used to enable notification from a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_enable_notificatoin(enu_gpt_timer_used_t_ enu_timer_used)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		GPTMCTL(enu_timer_used).R = 0;
		SET_BIT(GPTMIMR(enu_timer_used), 0);
		if (GPT_TIMER0 == enu_timer_used)
		{
			NVIC_EnableIRQ(TIMER0A_IRQn);
			__enable_irq();
		}
		else if	(GPT_TIMER1 == enu_timer_used)
		{
			NVIC_EnableIRQ(TIMER1A_IRQn);
			__enable_irq();
		}
		else if	(GPT_TIMER2 == enu_timer_used)
		{
			NVIC_EnableIRQ(TIMER2A_IRQn);
			__enable_irq();
		}
		else if	(GPT_TIMER3 == enu_timer_used)
		{
			NVIC_EnableIRQ(TIMER3A_IRQn);
			__enable_irq();
		}
		else if	(GPT_TIMER4 == enu_timer_used)
		{
			NVIC_EnableIRQ(TIMER4A_IRQn);
			__enable_irq();
		}
		else if	(GPT_TIMER5 == enu_timer_used)
		{
			NVIC_EnableIRQ(TIMER5A_IRQn);
			__enable_irq();
		}
		else if	(GPT_W_TIMER0 == enu_timer_used)
		{
			NVIC_EnableIRQ(WTIMER0A_IRQn);
			__enable_irq();
		}
		else if	(GPT_W_TIMER1 == enu_timer_used)
		{
			NVIC_EnableIRQ(WTIMER1A_IRQn);
			__enable_irq();
		}
		else if	(GPT_W_TIMER2 == enu_timer_used)
		{
			NVIC_EnableIRQ(WTIMER2A_IRQn);
			__enable_irq();
		}
		else if	(GPT_W_TIMER3 == enu_timer_used)
		{
			NVIC_EnableIRQ(WTIMER3A_IRQn);
			__enable_irq();
		}
		else if	(GPT_W_TIMER4 == enu_timer_used)
		{
			NVIC_EnableIRQ(WTIMER4A_IRQn);
			__enable_irq();
		}
		else if	(GPT_W_TIMER5 == enu_timer_used)
		{
			NVIC_EnableIRQ(WTIMER5A_IRQn);
			__enable_irq();
		}
		else
		{
			/*DO NOTHING*/
		}
	}
	return enu_ret_val;
}


/**
 *	@brief			This function is used to disable notification from a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_disable_notificatoin(enu_gpt_timer_used_t_ enu_timer_used)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		GPTMCTL(enu_timer_used).R = 0;
		CLR_BIT(GPTMIMR(enu_timer_used), 0);
		
		if (GPT_TIMER0 == enu_timer_used)
		{
			NVIC_DisableIRQ(TIMER0A_IRQn);
		}
		else if	(GPT_TIMER1 == enu_timer_used)
		{
			NVIC_DisableIRQ(TIMER1A_IRQn);
		}
		else if	(GPT_TIMER2 == enu_timer_used)
		{
			NVIC_DisableIRQ(TIMER2A_IRQn);
		}
		else if	(GPT_TIMER3 == enu_timer_used)
		{
			NVIC_DisableIRQ(TIMER3A_IRQn);
		}
		else if	(GPT_TIMER4 == enu_timer_used)
		{
			NVIC_DisableIRQ(TIMER4A_IRQn);
		}
		else if	(GPT_TIMER5 == enu_timer_used)
		{
			NVIC_DisableIRQ(TIMER5A_IRQn);
		}
		else if	(GPT_W_TIMER0 == enu_timer_used)
		{
			NVIC_DisableIRQ(WTIMER0A_IRQn);
		}
		else if	(GPT_W_TIMER1 == enu_timer_used)
		{
			NVIC_DisableIRQ(WTIMER1A_IRQn);
		}
		else if	(GPT_W_TIMER2 == enu_timer_used)
		{
			NVIC_DisableIRQ(WTIMER2A_IRQn);
		}
		else if	(GPT_W_TIMER3 == enu_timer_used)
		{
			NVIC_DisableIRQ(WTIMER3A_IRQn);
		}
		else if	(GPT_W_TIMER4 == enu_timer_used)
		{
			NVIC_DisableIRQ(WTIMER4A_IRQn);
		}
		else if	(GPT_W_TIMER5 == enu_timer_used)
		{
			NVIC_DisableIRQ(WTIMER5A_IRQn);
		}
		else
		{
			/*DO NOTHING*/
		}
	}
	return enu_ret_val;
}

/**
 *	@brief				This function is used to set a callback function for a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_set_callback(enu_gpt_timer_used_t_ enu_timer_used, ptr_gpt_callback_t_ ptr_gpt_callback)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	if (GPT_TOTAL_TIMERS <= enu_timer_used)
	{
		enu_ret_val = GPT_INVALID_TIMER_INDEX;
	}
	else
	{
		if (NULL_PTR == ptr_gpt_callback)
		{
			enu_ret_val = PASSING_NULL_PTR;
		}
		else
		{
			gl_arr_ptr_callback[enu_timer_used] = ptr_gpt_callback;
		}
	}
	return enu_ret_val;
}

/**
 *	@brief				This function is used to get an index for unused channel
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_ALL_TIMERS_USED					:	In case of all timers are used
 */
enu_error_status_t_ gpt_get_unused_channel(uint8_t_* uint8_timer_unused)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	for (uint8_t_ uint8_looping_variable = 0; uint8_looping_variable < 12; uint8_looping_variable++)
	{
		enu_ret_val = GPT_ALL_TIMERS_USED;
		if (FALSE == gl_arr_uint8_gpt_used[uint8_looping_variable])
		{
			enu_ret_val = ERROR_OK;
			*uint8_timer_unused = uint8_looping_variable;
			break;
		}
	}
	return enu_ret_val;
}

void TIMER0A_Handler (void)
{
	static uint32_t_ uint32_ovf_counter = 0;
	uint32_ovf_counter ++;
	if(uint32_ovf_counter == gl_arr_uint32_number_of_ovfs[GPT_TIMER0])
	{
		if (NULL_PTR != gl_arr_ptr_callback[GPT_TIMER0])
		{
			gl_arr_ptr_callback[GPT_TIMER0]();
		}
		else
		{
			/*DO NOTHING*/
		}
		uint32_ovf_counter = 0;
		GPTMCTL(GPT_TIMER0).R = 0;
		GPTMTAILR(GPT_TIMER0) = gl_arr_uint32_reloading_value[GPT_TIMER0];
		GPTMCTL(GPT_TIMER0).R = 1;
	}
	else if (gl_arr_uint32_number_of_ovfs[GPT_TIMER0]!= 0)
	{
		GPTMCTL(GPT_TIMER0).R = 0;
		GPTMTAILR(GPT_TIMER0) = 0xFFFF;
		GPTMCTL(GPT_TIMER0).R = 1;
	}
	SET_BIT(GPTMICR(GPT_TIMER0), 0);

}

void TIMER1A_Handler (void)
{
	static uint32_t_ uint32_ovf_counter = 0;
	uint32_ovf_counter ++;
	if(uint32_ovf_counter == gl_arr_uint32_number_of_ovfs[GPT_TIMER1])
	{
		if (NULL_PTR != gl_arr_ptr_callback[GPT_TIMER1])
		{
			gl_arr_ptr_callback[GPT_TIMER1]();
		}
		else
		{
			/*DO NOTHING*/
		}
		uint32_ovf_counter = 0;
		GPTMCTL(GPT_TIMER1).R = 0;
		GPTMTAILR(GPT_TIMER1) = gl_arr_uint32_reloading_value[GPT_TIMER1];
		GPTMCTL(GPT_TIMER1).R = 1;
	}
	else if (gl_arr_uint32_number_of_ovfs[GPT_TIMER1]!= 0)
	{
		GPTMCTL(GPT_TIMER1).R = 0;
		GPTMTAILR(GPT_TIMER1) = 0xFFFF;
		GPTMCTL(GPT_TIMER1).R = 1;
	}
	SET_BIT(GPTMICR(GPT_TIMER1), 0);

}
/**********************************************************************************************************************
 *  END OF FILE: gpt_program.c
 *********************************************************************************************************************/
