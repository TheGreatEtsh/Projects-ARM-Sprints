#include "systick_handler_interface.h"


enu_error_status_t_ handler_init_systick(uint32_t_ uint32_delay_time_ms)
{
	return systick_init(uint32_delay_time_ms);
}
enu_error_status_t_ handler_reload_systick(uint32_t_ uint32_delay_time_ms)
{
	return systick_reload(uint32_delay_time_ms);
}
enu_error_status_t_ handler_disable_systick(void)
{
	return systick_disable();
}
enu_error_status_t_ handler_enable_systick(void)
{
	return systick_enable();
}
enu_error_status_t_ handler_set_callback_systick(void (*a_void_ptr) (void))
{
	return systick_set_callback(a_void_ptr);
}






