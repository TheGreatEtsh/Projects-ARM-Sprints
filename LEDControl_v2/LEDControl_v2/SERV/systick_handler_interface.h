#include"systick_interface.h"



enu_error_status_t_ handler_init_systick(uint32_t_ uint32_delay_time_ms);
enu_error_status_t_ handler_reload_systick(uint32_t_ uint32_delay_time_ms);
enu_error_status_t_ handler_disable_systick(void);
enu_error_status_t_ handler_enable_systick(void);
enu_error_status_t_ handler_set_callback_systick(void (*a_void_ptr) (void));

