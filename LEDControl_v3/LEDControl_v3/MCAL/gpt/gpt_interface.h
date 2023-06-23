/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *	@file			gpt_interface.h
 * 	@date			20/6/2023	10:14
 *  @brief			Interface file for GPT driver
 *	@email 			ahmedhesham606@icloud.com
 *  @author			Ahmad Hesham
 * 
 */
#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

/**----------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------*/
#include "..\..\LIB\common.h"
#include "..\..\LIB\bit_math.h"



/**----------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
 *----------------------------------------------------------*/
typedef void (*ptr_gpt_callback_t_) (void);

typedef enum
{
	GPT_TIMER0 = 0,
	GPT_TIMER1,
	GPT_TIMER2,
	GPT_TIMER3,
	GPT_TIMER4,
	GPT_TIMER5,
	GPT_W_TIMER0,
	GPT_W_TIMER1,
	GPT_W_TIMER2,
	GPT_W_TIMER3,
	GPT_W_TIMER4,
	GPT_W_TIMER5,
	GPT_TOTAL_TIMERS
}enu_gpt_timer_used_t_;

typedef enum
{
	GPT_ONE_SHOT = 0x1,
	GPT_PERIODIC = 0x2
}enu_gpt_timer_mode_t_;

typedef enum
{
	GPT_S = 0,
	GPT_MS,
	GPT_US
}enu_gpt_counting_standard_t_;

typedef enum
{
	GPT_COUNT_DOWN,
	GPT_COUNT_UP
}enu_gpt_counting_direction_t_;

typedef enum
{
	GPT_NON_BLOCKING,
	GPT_BLOCKING
}enu_gpt_blocking_mode_t_;
typedef struct
{
	enu_gpt_timer_used_t_			enu_timer_used;
	enu_gpt_timer_mode_t_			enu_timer_mode;
	enu_gpt_counting_direction_t_	enu_counting_direction;
	enu_gpt_blocking_mode_t_		enu_blocking_mode;
	enu_gpt_counting_standard_t_	enu_counting_standard;
	ptr_gpt_callback_t_				ptr_gpt_callback;
	uint64_t_						uint64_desired_time;
}str_gpt_timer_config_t_;



/**----------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
 *----------------------------------------------------------*/

/**
 *	@brief				This function is used to initialize a specific general purpose timer
 *	@param [in]		ptr_str_gpt_timer_config				:	Ptr to the timer instance structure
 *	@param [out]	none	
 *	@return				ERROR_OK												:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX					:	In case of choosing wrong channel index
 *	@return				GPT_INITIALIZED									:	In case of choosing initialized channel 
 *	@return				GPT_INVALID_STANDARD						: In case of choosing wrong standard
 *	@return				GPT_INVALID_BLOCKING_MODE				: In case of choosing wrong blocking mode
 *	@return				GPT_INVALID_COUNTING_DIRECTION	: In case of choosing wrong blocking mode
 *	@return				GPT_INVALID_GPT_MODE						: In case of choosing wrong mode
 */
enu_error_status_t_ gpt_init(str_gpt_timer_config_t_* ptr_str_gpt_timer_config);

/**
 *	@brief				This function is used to stop a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_stop_timer(enu_gpt_timer_used_t_ enu_timer_used);

/**
 *	@brief				This function is used to load timer interval
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [in]		enu_counting_standard				:	Counting Standard -Seconds, mSeconds, uSeconds-
 *	@param [in]		uint32_desired_time					:	Value to be loaded  
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 *	@return				GPT_INVALID_VALUE						:	In case of loading Zero
 *	@return				GPT_INVALID_STANDARD				:	In case of choosing a wrong standard
 */
enu_error_status_t_ gpt_set_time(enu_gpt_timer_used_t_ enu_timer_used, enu_gpt_counting_standard_t_ enu_counting_standard, uint64_t_ uint64_desired_time);

/**
 *	@brief				This function is used to start a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_start_timer(enu_gpt_timer_used_t_ enu_timer_used);

/**
 *	@brief				This function is used to enable notification from a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_enable_notificatoin(enu_gpt_timer_used_t_ enu_timer_used);

/**
 *	@brief				This function is used to disable notification from a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_disable_notificatoin(enu_gpt_timer_used_t_ enu_timer_used);

/**
 *	@brief				This function is used to set a callback function for a specific general purpose timer
 *	@param [in]		enu_timer_used							:	Timer index used
 *	@param [out]	none
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_INVALID_TIMER_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpt_set_callback(enu_gpt_timer_used_t_ enu_timer_used, ptr_gpt_callback_t_ ptr_gpt_callback);

/**
 *	@brief				This function is used to get an index for unused channel
 *	@param [in]		none
 *	@param [out]	ptr_uint8_timer_unused			:	Timer index unused
 *	@return				ERROR_OK										:	In case of success
 *	@return				GPT_ALL_TIMERS_USED					:	In case of all timers are used
 */
enu_error_status_t_ gpt_get_unused_channel(uint8_t_* ptr_uint8_timer_unused);
	
#endif  /* GPT_INTERFACE_H */

/**********************************************************************************************************************
 *  END OF FILE: gpt_interface.h
 *********************************************************************************************************************/
