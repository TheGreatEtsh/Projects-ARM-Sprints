/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *      @File  			app.h
 *      @date			18/6/2023	2:26 PM
 *  	@brief			interface file for application
 *		@author			Ahmad Hesham
 *      @email			ahmedhesham606@icloud.com
 */
#ifndef APP_H
#define APP_H

#define APP_SYSTICK_TIME				50
#define APP_LED_ON_TIME					1000/APP_SYSTICK_TIME
#define APP_BUTTON_PERIODICTY		50/APP_SYSTICK_TIME

/**----------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
 *----------------------------------------------------------*/
/**
 *	@brief			This function is used to initialize drivers used
 *	@param [in]		none
 *	@param [out]	none
 *	@return			none
 */
void app_init(void);

#endif  /* APP_H */

/**----------------------------------------------------------
 *  END OF FILE: app.h
 *----------------------------------------------------------*/
