/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *      @File  			gpio_interface.h
 *      @date			15/6/2023	5:58
 *  	@brief			The main include file to interface with GPIO peripheral
 *		@author			Ahmad Hesham
 *      @email			ahmedhesham606@icloud.com
 */

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/**----------------------------------------------------------
 * INCLUDES
 *----------------------------------------------------------*/
#include "..\..\LIB\common.h"
#include "..\..\LIB\bit_math.h"

/**----------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
 *----------------------------------------------------------*/


#define ENABLE_PORT		1
#define DISABLE_PORT	0

 


  

/**----------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
 *----------------------------------------------------------*/

/**
 * Choose DIO, or Alternative Function Select check data sheet page 1351
 */
typedef enum {
	GPIO_DIO = 0,
	GPIO_U0Rx = 1,
	GPIO_U0Tx = 1,
	GPIO_PB0_U1Rx = 1,
	GPIO_PB1_U1Tx = 1,
	GPIO_TCK_SWCLK = 1,
	GPIO_TMS_SWDIO = 1,
	GPIO_TDI = 1,
	GPIO_TDO_SWO = 1,
	GPIO_U4Rx = 1,
	GPIO_U4Tx = 1,
	GPIO_U3Rx = 1,
	GPIO_U3Tx = 1,
	GPIO_SSI3CLK = 1,
	GPIO_SSI3Fss = 1,
	GPIO_SSI3Rx = 1,
	GPIO_SSI3Tx = 1,
	GPIO_U6Rx = 1,
	GPIO_U6Tx = 1,
	GPIO_U2Rx = 1,
	GPIO_U2Tx = 1,
	GPIO_U7Rx = 1,
	GPIO_U7Tx = 1,
	GPIO_U5Rx = 1,
	GPIO_U5Tx = 1,
	GPIO_U1RTS = 1,
	GPIO_U1CTS = 1,
	GPIO_SSI0CLK = 2,
	GPIO_SSI0Fss = 2,
	GPIO_SSI0Rx = 2,
	GPIO_SSI0Tx = 2,
	GPIO_SSI2CLK = 2,
	GPIO_SSI2Fss = 2,
	GPIO_SSI2Rx = 2,
	GPIO_SSI2Tx = 2,
	GPIO_PC4_U1Rx = 2,
	GPIO_PC5_U1Tx = 2,
	GPIO_SSI1CLK = 2,
	GPIO_SSI1Fss = 2,
	GPIO_SSI1Rx = 2,
	GPIO_SSI1Tx = 2,
	//	GPIO_PF1_SSI1CLK = 2,
	//	GPIO_PF2_SSI1Fss = 2,
	//	GPIO_PF3_SSI1Rx	= 2,
	//	GPIO_PF4_SSI1Tx	= 2,
	GPIO_I2C1SCL = 3,
	GPIO_I2C1SDA = 3,
	GPIO_I2C0SCL = 3,
	GPIO_I2C0SDA = 3,
	GPIO_I2C3SCL = 3,
	GPIO_I2C3SDA = 3,
	GPIO_I2C2SCL = 3,
	GPIO_I2C2SDA = 3,
	GPIO_CAN0Rx = 3,
	GPIO_CAN0Tx = 3,
	GPIO_M0FAULT0 = 4,
	GPIO_M0PWM5 = 4,
	GPIO_M0PWM4 = 4,
	GPIO_M0PWM7 = 4,
	GPIO_M0PWM6 = 4,
	GPIO_M0PWM3 = 4,
	GPIO_M0PWM2 = 4,
	GPIO_M0PWM1 = 4,
	GPIO_M0PWM0 = 4,
	GPIO_M1FAULT0 = 5,
	GPIO_M1PWM5 = 5,
	GPIO_M1PWM4 = 5,
	GPIO_M1PWM7 = 5,
	GPIO_M1PWM6 = 5,
	GPIO_M1PWM3 = 5,
	GPIO_M1PWM2 = 5,
	GPIO_M1PWM1 = 5,
	GPIO_M1PWM0 = 5,
	GPIO_IDX0 = 6,
	GPIO_PhA0 = 6,
	GPIO_PhB0 = 6,
	GPIO_IDX1 = 6,
	GPIO_PhA1 = 6,
	GPIO_PhB1 = 6,
	GPIO_T2CCP0 = 7,
	GPIO_T2CCP1 = 7,
	GPIO_T3CCP0 = 7,
	GPIO_T3CCP1 = 7,
	GPIO_T1CCP0 = 7,
	GPIO_T1CCP1 = 7,
	GPIO_T0CCP0 = 7,
	GPIO_T0CCP1 = 7,
	GPIO_T4CCP0 = 7,
	GPIO_T4CCP1 = 7,
	GPIO_T5CCP0 = 7,
	GPIO_T5CCP1 = 7,
	GPIO_WT2CCP0 = 7,
	GPIO_WT2CCP1 = 7,
	GPIO_WT3CCP0 = 7,
	GPIO_WT3CCP1 = 7,
	GPIO_WT1CCP0 = 7,
	GPIO_WT1CCP1 = 7,
	GPIO_WT0CCP0 = 7,
	GPIO_WT0CCP1 = 7,
	GPIO_WT4CCP0 = 7,
	GPIO_WT4CCP1 = 7,
	GPIO_WT5CCP0 = 7,
	GPIO_WT5CCP1 = 7,
	GPIO_USB0EPEN = 8,
	GPIO_NMI = 8,
	GPIO_PE4_CAN0 = 8,
	GPIO_PE5_CAN0 = 8,
	GPIO_USB0PFLT = 8,
	GPIO_PC4_U1RT = 8,
	GPIO_PC5_U1CT = 8,
	GPIO_PB4_CAN0 = 8,
	GPIO_PB5_CAN0 = 8,
	GPIO_CAN1Rx = 8,
	GPIO_CAN1Tx = 8,
	GPIO_C0o = 9,
	GPIO_C1o = 9,
	GPIO_TRD1 = 14,
	GPIO_TRD0 = 14,
	GPIO_TRCLK = 14
}enu_gpio_pin_mode_t_;

/**
 * GPIO_INPUT OR GPIO_OUTPUT
 */
typedef enum {
	GPIO_INPUT = 0,
	GPIO_OUTPUT
}enu_gpio_pin_direction_t_;

/**
 * GPIO_LOW OR GPIO_HIGH
 */
typedef enum {
	GPIO_LOW = 0,
	GPIO_HIGH
}enu_gpio_pin_level_t_;

/**
 * GPIO_PULLDOWN, GPIO_PULLUP OR GPIO_OPENDRAIN
 */
typedef enum {
	GPIO_PULLDOWN = 1,
	GPIO_PULLUP,
	GPIO_OPENDRAIN
}enu_gpio_pin_internal_attach_t_;

/**
 * GPIO_2mA, GPIO_4mA OR GPIO_8mA
 */
typedef enum {
	GPIO_2mA = 2,
	GPIO_4mA = 4,
	GPIO_8mA = 8
}enu_gpio_pin_output_current_t_;

typedef enum {
	GPIO_PA0 = 0,
	GPIO_PA1 = 1,
	GPIO_PA2 = 2,
	GPIO_PA3 = 3,
	GPIO_PA4 = 4,
	GPIO_PA5 = 5,
	GPIO_PA6 = 6,
	GPIO_PA7 = 7,
	
	GPIO_PB0 = 10,
	GPIO_PB1 = 11,
	GPIO_PB2 = 12,
	GPIO_PB3 = 13,
	GPIO_PB4 = 14,
	GPIO_PB5 = 15,
	GPIO_PB6 = 16,
	GPIO_PB7 = 17,
	
	GPIO_PC0 = 20,
	GPIO_PC1 = 21,
	GPIO_PC2 = 22,
	GPIO_PC3 = 23,
	GPIO_PC4 = 24,
	GPIO_PC5 = 25,
	GPIO_PC6 = 26,
	GPIO_PC7 = 27,
	
	GPIO_PD0 = 30,
	GPIO_PD1 = 31,
	GPIO_PD2 = 32,
	GPIO_PD3 = 33,
	GPIO_PD4 = 34,
	GPIO_PD5 = 35,
	GPIO_PD6 = 36,
	GPIO_PD7 = 37,

	GPIO_PE0 = 40,
	GPIO_PE1 = 41,
	GPIO_PE2 = 42,
	GPIO_PE3 = 43,
	GPIO_PE4 = 44,
	GPIO_PE5 = 45,
	GPIO_PE6 = 46,
	GPIO_PE7 = 47,
	
	GPIO_PF0 = 50,
	GPIO_PF1 = 51,
	GPIO_PF2 = 52,
	GPIO_PF3 = 53,
	GPIO_PF4 = 54,
	GPIO_PF5 = 55,
	GPIO_PF6 = 56,
	GPIO_PF7 = 57
}enu_gpio_pin_index_t_;

typedef struct {
	enu_gpio_pin_index_t_			enu_pin_index;
	enu_gpio_pin_mode_t_			enu_pin_mode;
	enu_gpio_pin_direction_t_		enu_pin_direction;
	enu_gpio_pin_output_current_t_	enu_pin_output_current;
	enu_gpio_pin_internal_attach_t_	enu_pin_internal_attach;
}str_gpio_config_t_;


/**----------------------------------------------------------
 *  GLOBAL DATA PROTOTYPES
 *----------------------------------------------------------*/
typedef void(*ptr_gpio_callback_t_)(void);


/**----------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
 *----------------------------------------------------------*/


/**
 *	@brief			This function is used to initialize a specific pin 
 *	@param [in]		ptr_str_gpio_config				:	Ptr to the gpio instance structure
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 *	@return			GPIO_INVALID_PIN_MODE			:	In case of wrong mode choosen
 *	@return			GPIO_INVALID_PIN_DIRECTION		:	In case of wrong direction choosen
 *	@return			GPIO_INVALID_OP_CURRENT			:	In case of wrong current choosen
 *	@return			GPIO_INVALID_INTERNAL_ATTACH	:	In case of wrong internal attach
 */
enu_error_status_t_ gpio_pin_init(str_gpio_config_t_* ptr_str_gpio_config);

/**
 *	@brief			This function is used to Write a specific output on a pin
 *	@param [in]		uint8_pin_index					:	Pin index used
 *	@param [in]		enu_pin_level					:	Output level to be written
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 *	@return			GPIO_INVALID_PIN_LEVEL			:	In case of wrong output level choosen
 */
enu_error_status_t_ gpio_pin_write(uint8_t_ uint8_pin_index, enu_gpio_pin_level_t_ enu_pin_level);

/**
 *	@brief			This function is used to toggle output level on a pin
 *	@param [in]		uint8_pin_index					:	Pin Index used
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpio_pin_toggle(uint8_t_ uint8_pin_index);

/**
 *	@brief			This function is used to get pin's input value
 *	@param [in]		uint8_pin_index					:	Pin index used
 *	@param [out]	uint8_pin_state					:	Pin level state
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpio_pin_read(uint8_t_ uint8_pin_index, uint8_t_* uint8_pin_state);

/**
 *	@brief			This function is used to enable pin's interrupt
 *	@param [in]		uint8_pin_index					:	Pin index used
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpio_pin_enable_notification(uint8_t_ uint8_pin_index);

/**
 *	@brief			This function is used to set callback function for a specific pin's interrupt handler
 *	@param [in]		uint8_pin_index					:	Pin index used
 *  @param [in]		ptr_callback					:	pointer to a callback function
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 *  @return			PASSING_NULL_PTR				:	In case of passing null pointer
 */
enu_error_status_t_ gpio_pin_set_callback(uint8_t_ uint8_pin_index, ptr_gpio_callback_t_ ptr_callback);



#endif  /* GPIO_INTERFACE_H */

/**----------------------------------------------------------
 *  END OF FILE: gpio_interface.h
 *----------------------------------------------------------*/
