/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *      @File  			gpio_program.c
 *      @date			16/6/2023	11:41
 *  	@brief			program file for GPIO driver
 *		@author			Ahmad Hesham
 *      @email			ahmedhesham606@icloud.com
 */

/**----------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTATIONS
 *----------------------------------------------------------*/
#include "gpio_interface.h"
#include "gpio_private.h"
#include "nvic_interface.h"
#include "TM4C123.h"

ptr_gpio_callback_t_ gpiof_callback = NULL_PTR;

/**----------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTATIONS
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
enu_error_status_t_ gpio_pin_init(str_gpio_config_t_* ptr_str_gpio_config)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = ptr_str_gpio_config->enu_pin_index % 10;
	uint8_port_num = ptr_str_gpio_config->enu_pin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_ret_val = GPIO_INVALID_PIN_INDEX;
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_ret_val = GPIO_INVALID_PIN_INDEX;
		}
		else
		{
			/*STEP 1: Enable clock to GPIO Port Used using RCGCGPIO register*/
			if (1 == GET_BIT(RCGCGPIO_, uint8_port_num))
			{
				/*ENABLED*/
			}
			else
			{
				SET_BIT(RCGCGPIO_, uint8_port_num);
			}

			/*STEP 2: Assigning pin direction, Output Current, and Pin Internal Attach*/
			if (GPIO_OUTPUT == ptr_str_gpio_config->enu_pin_direction)
			{
				SET_BIT(GPIODIR(uint8_port_num), uint8_pin_num);
				
				/*STEP 3: Assigning whether the pin is working digital or Alternative function*/
				switch (ptr_str_gpio_config->enu_pin_mode)
				{
				case GPIO_DIO:
					GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
					CLR_BIT(GPIOAFSEL(uint8_port_num), uint8_pin_num);
					
					break;
				default:
					GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
					SET_BIT(GPIOAFSEL(uint8_port_num), uint8_pin_num);
					GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
					(GPIOPCTL(uint8_port_num) &= (~((uint32_t_)15 << (4 * uint8_pin_num))));
					(GPIOPCTL(uint8_port_num) |= ((uint32_t_)ptr_str_gpio_config->enu_pin_mode << (4 * uint8_pin_num))); 	
					break;
				}
				

				switch (ptr_str_gpio_config->enu_pin_output_current)
				{
				case GPIO_2mA:
					SET_BIT(GPIODR2R(uint8_port_num), uint8_pin_num);
					break;

				case GPIO_4mA:
					SET_BIT(GPIODR4R(uint8_port_num), uint8_pin_num);
					break;

				case GPIO_8mA:
					SET_BIT(GPIODR8R(uint8_port_num), uint8_pin_num);
					break;

				default:
					enu_ret_val = GPIO_INVALID_OP_CURRENT;
					break;
				}
			}
			else if (GPIO_INPUT == ptr_str_gpio_config->enu_pin_direction)
			{
				CLR_BIT(GPIODIR(uint8_port_num), uint8_pin_num);

				/*STEP 3: Assigning whether the pin is working digital or Alternative function*/
				switch (ptr_str_gpio_config->enu_pin_mode)
				{
				case GPIO_DIO:
					GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
					CLR_BIT(GPIOAFSEL(uint8_port_num), uint8_pin_num);
					break;
				default:
					GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
					SET_BIT(GPIOAFSEL(uint8_port_num), uint8_pin_num);
					GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
					(GPIOPCTL(uint8_port_num) &= (~((uint32_t_)15 << (4 * uint8_pin_num))));
					(GPIOPCTL(uint8_port_num) |= ((uint32_t_)ptr_str_gpio_config->enu_pin_mode << (4 * uint8_pin_num)));
					break;
				}

				switch (ptr_str_gpio_config->enu_pin_internal_attach)
				{
				case GPIO_PULLDOWN:
					SET_BIT(GPIOPDR(uint8_port_num), uint8_pin_num);
					break;

				case GPIO_PULLUP:
					SET_BIT(GPIOPUR(uint8_port_num), uint8_pin_num);
					break;

				case GPIO_OPENDRAIN:
					SET_BIT(GPIOODR(uint8_port_num), uint8_pin_num);
					break;

				default:
					enu_ret_val = GPIO_INVALID_INTERNAL_ATTACH;
					break;
				}
			}
			else
			{
				GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
				enu_ret_val = GPIO_INVALID_PIN_DIRECTION;
			}

			SET_BIT(GPIODEN(uint8_port_num), uint8_pin_num);
			GPIOLOCK(uint8_port_num) = GPIO_UNLOCKING_VALUE;	GPIOCR(uint8_port_num) = 0x1;
		}
	}

	return enu_ret_val;
	
}

/**
 *	@brief			This function is used to Write a specific output on a pin
 *	@param [in]		uint8_pin_index					:	Pin index used
 *	@param [in]		enu_pin_level					:	Output level to be written
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 *	@return			GPIO_INVALID_PIN_LEVEL			:	In case of wrong output level choosen
 */
enu_error_status_t_ gpio_pin_write(uint8_t_ uint8_pin_index, enu_gpio_pin_level_t_ enu_pin_level)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = uint8_pin_index % 10;
	uint8_port_num = uint8_pin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_ret_val = GPIO_INVALID_PIN_INDEX;
		
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_ret_val = GPIO_INVALID_PIN_INDEX;
		}
		else
		{
			if (enu_pin_level == GPIO_HIGH)
			{
				GPIODATA(uint8_port_num) |= enu_pin_level << uint8_pin_num;	//SET_BIT(GPIODATA(uint8_port_num), uint8_port_num);
			}
			else if (enu_pin_level == GPIO_LOW)
			{
				//GPIODATA(uint8_port_num) = enu_pin_level << uint8_pin_num; 
				//GPIODATA(uint8_port_num) = 0 << uint8_pin_num;
				CLR_BIT(GPIODATA(uint8_port_num), uint8_pin_num);
			}
			else
			{
				enu_ret_val = GPIO_INVALID_PIN_LEVEL;
			}
		}
	}

	return enu_ret_val;
}

/**
 *	@brief			This function is used to toggle output level on a pin
 *	@param [in]		uint8_pin_index					:	Pin Index used
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpio_pin_toggle(uint8_t_ uint8_pin_index)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;
	
	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = uint8_pin_index % 10;
	uint8_port_num = uint8_pin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_ret_val = GPIO_INVALID_PIN_INDEX;
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_ret_val = GPIO_INVALID_PIN_INDEX;
		}
		else
		{
			if (GPIO_LOW == (GPIODATA(uint8_port_num) >> uint8_pin_num))
			{
				gpio_pin_write(uint8_pin_index, GPIO_HIGH);
			}
			else
			{
				gpio_pin_write(uint8_pin_index, GPIO_LOW);
			}
		}
	}

	return enu_ret_val;
}

/**
 *	@brief			This function is used to get pin's input value
 *	@param [in]		uint8_pin_index					:	Pin index used
 *	@param [out]	uint8_pin_state					:	Pin level state
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpio_pin_read(uint8_t_ uint8_pin_index, uint8_t_* uint8_pin_state)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = uint8_pin_index % 10;
	uint8_port_num = uint8_pin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_ret_val = GPIO_INVALID_PIN_INDEX;
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_ret_val = GPIO_INVALID_PIN_INDEX;
		}
		else
		{
			//*uint8_pin_state = GPIODATA(uint8_port_num) >> uint8_pin_num; 
			*uint8_pin_state = GET_BIT(GPIODATA(uint8_port_num), uint8_port_num);
		}
	}

	return enu_ret_val;
}

/**
 *	@brief			This function is used to enable pin's interrupt
 *	@param [in]		uint8_pin_index					:	Pin index used
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *	@return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 */
enu_error_status_t_ gpio_pin_enable_notification(uint8_t_ uint8_pin_index)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = uint8_pin_index % 10;
	uint8_port_num = uint8_pin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_ret_val = GPIO_INVALID_PIN_INDEX;
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_ret_val = GPIO_INVALID_PIN_INDEX;
		}
		else
		{
			CLR_BIT(GPIOIM(uint8_port_num), uint8_pin_num); 
			CLR_BIT(GPIOIS(uint8_port_num), uint8_pin_num); 
			CLR_BIT(GPIOIBE(uint8_port_num), uint8_pin_num); 
			CLR_BIT(GPIOIEV(uint8_port_num), uint8_pin_num);
			SET_BIT(GPIOICR(uint8_port_num), uint8_pin_num); 
			SET_BIT(GPIOIM(uint8_port_num), uint8_pin_num);
			NVIC_EnableIRQ(GPIOF_IRQn);
			__enable_irq();
		}
	}

	return enu_ret_val;
}

/**
 *	@brief			This function is used to set callback function for a specific pin's interrupt handler
 *	@param [in]		uint8_pin_index					:	Pin index used
 *  @param [in]		ptr_callback					:	pointer to a callback function
 *	@param [out]	none
 *	@return			ERROR_OK						:	In case of successeion
 *  @return			GPIO_INVALID_PIN_INDEX			:	In case of wrong pin index
 *	@return			PASSING_NULL_PTR				:	In case of passing null pointer
 */
enu_error_status_t_ gpio_pin_set_callback(uint8_t_ uint8_pin_index, ptr_gpio_callback_t_ ptr_callback)
{
	enu_error_status_t_ enu_ret_val = ERROR_OK;

	uint8_t_ uint8_pin_num = 0, uint8_port_num = 0;
	uint8_pin_num = uint8_pin_index % 10;
	uint8_port_num = uint8_pin_index / 10;

	if (uint8_port_num > 5 || uint8_pin_num > 7)
	{
		enu_ret_val = GPIO_INVALID_PIN_INDEX;
	}
	else
	{
		if (((5 == uint8_port_num) && (uint8_pin_num > 4)) || ((4 == uint8_port_num) && (uint8_pin_num > 5)))
		{
			enu_ret_val = GPIO_INVALID_PIN_INDEX;
		}
		else
		{
			if (ptr_callback == NULL_PTR)
			{
				enu_ret_val = PASSING_NULL_PTR;
			}
			else
			{
				gpiof_callback = ptr_callback;
			}
		}
	}

	return enu_ret_val;
}
void GPIOF_Handler(void)
{
	if (NULL_PTR != gpiof_callback)
	{
		gpiof_callback();
		
	}
	GPIOICR(5) = 0xFF;
}

/**********************************************************************************************************************
 *  END OF FILE: gpio_program.c
 *********************************************************************************************************************/
