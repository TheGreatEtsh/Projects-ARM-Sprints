/**********************************************************************************************************************
*  FILE DESCRIPTION
*  -----------------------------------------------------------------------------------------------------------------*/
/**      \file			M_GPT_Program.c
*        \date			22/11/2022
*		 \brief			
*        \email 		ahmedhesham606@icloud.com	
*		 \author		Ahmad Hesham
*		 \description
* 
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "systick_interface.h"
#include "systick_private.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
*  LOCAL DATA
*********************************************************************************************************************/
void (*SysTick0_void_CallBack)(void) = NULL_PTR;
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint32_t_ gl_uint32_current_delay_used = 0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

enu_error_status_t_ systick_init(uint32_t_ uint32_delay_time_ms)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	if (uint32_delay_time_ms != 0)
	{
		gl_uint32_current_delay_used = uint32_delay_time_ms;
		/*Disable the counter*/
		CLR_BIT(STCTRL, 0);
		/*Reload the counter*/
		STRELOAD = (XTAL/4 * 1000 * uint32_delay_time_ms) - 1;
		/*Clear Current register*/
		CLR_BIT(STCURRENT,0) ;
		/*Enable Interrupt*/
		SET_BIT(STCTRL, 1);
		/*Choose PIOSC*/
		CLR_BIT(STCTRL, 2);
		/*Enable the counter*/
		SET_BIT(STCTRL, 0);
	}
	else
	{
		enu_ret_val = SYSTICK_WRONG_VALUE;
	}
	return enu_ret_val;
}

enu_error_status_t_ systick_disable(void)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	CLR_BIT(STCTRL, 0);
	CLR_BIT(STCTRL, 0);
	return enu_ret_val;
}

enu_error_status_t_ systick_reload(uint32_t_ uint32_delay_time_ms)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	if (uint32_delay_time_ms != 0)
	{
		/*Disable the counter*/
		CLR_BIT(STCTRL, 0);
		/*Reload the counter*/
		STRELOAD = (XTAL/4 * 1000 * uint32_delay_time_ms) - 1;
		/*Clear Current register*/
		CLR_BIT(STCURRENT,0) ;
		/*Enable Interrupt*/
		SET_BIT(STCTRL, 1);
		/*Choose PIOSC*/
		CLR_BIT(STCTRL, 2);
		/*Enable the counter*/
		SET_BIT(STCTRL, 0);
	}
	else
	{
		enu_ret_val = SYSTICK_WRONG_VALUE;
	}
	return enu_ret_val;
}
enu_error_status_t_ systick_enable(void)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	systick_reload(gl_uint32_current_delay_used);
	return enu_ret_val;
}
enu_error_status_t_ systick_set_callback(void (*a_void_ptr) (void))
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	if (a_void_ptr != NULL_PTR)
	{
		SysTick0_void_CallBack = a_void_ptr;
	}
	else
	{
		enu_ret_val = PASSING_NULL_PTR;
	}
	return enu_ret_val;
}
void SysTick_Handler  (void)        
{
	if (SysTick0_void_CallBack != NULL_PTR)
	{
		SysTick0_void_CallBack();
	}
}	
/**********************************************************************************************************************
 *  END OF FILE: M_GPT_Program.c
 *********************************************************************************************************************/
