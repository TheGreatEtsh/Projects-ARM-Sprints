/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 * 
 *  @File:  		gpio_private.h
 *  @date:		    6/15/2023	5:33 PM
 *	@brief:			Consist of Private data of GPIO peripheral
 *  @email: 		ahmedhesham606@icloud.com
 *	@author:		Ahmad Hesham
 */
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/**
 *  GLOBAL CONSTANT MACROS
 */

#define GPIO_APB

#ifdef GPIO_APB
	#define GPIO_OFFSET(x)	(x<4? ((0X40004000)+ ((x)* 0x1000)): ((0X40024000)+((x-4)*0x1000)))
#elif GPIO_AHB
	#error "Not Supported Yet"
#else
	#error "Please choose a bus for GPIOs"
#endif

#define SYS_CTRL_BASE_ADDRESS			0X400FE000

#define GPIO_UNLOCKING_VALUE			0x4C4F434B

#define RCGCGPIO_		(*((volatile uint32_t_*) (SYS_CTRL_BASE_ADDRESS+0x608)))
#define PRGPIO_			(*((volatile uint32_t_*) (SYS_CTRL_BASE_ADDRESS+0xA08)))



#define GPIODATA(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x3FC)))
#define GPIODIR(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x400)))
#define GPIOAFSEL(x)	(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x420)))
#define GPIODEN(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x51C)))
#define GPIOPCTL(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x52C)))
#define GPIODR2R(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x500)))
#define GPIODR4R(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x504)))
#define GPIODR8R(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x508)))
#define GPIOODR(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x50C)))
#define GPIOPUR(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x510)))
#define GPIOPDR(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x514)))
#define GPIOIM(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x410)))
#define GPIOIS(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x404)))
#define GPIOIBE(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x408)))
#define GPIORIS(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x414)))
#define GPIOICR(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x41C)))
#define GPIOLOCK(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x520)))
#define GPIOCR(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x524)))
#define GPIOIEV(x)		(*((volatile uint32_t_*) (GPIO_OFFSET(x)+0x40C)))





#endif  /* GPIO_PRIVATE_H */
/**
 *  END OF FILE: gpio_private.h
 */
