/**
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *	@file			gpt_private.h
 * 	@date			20/6/2023	9:52
 * 	@brief			Consists of private data for GPT peripheral
 *	@email 			ahmedhesham606@icloud.com
 * 	@author			Ahmad Hesham
 */
#ifndef GPT_PRIVATE_H
#define GPT_PRIVATE_H

/**----------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
 *----------------------------------------------------------*/
 #include "common.h"
typedef struct
{
	uint32_t_ TAMR		: 2;
	uint32_t_ TACMR		: 1;
	uint32_t_ TAAMS		: 1;
	uint32_t_ TACDIR	: 1;
	uint32_t_ TAMIE		: 1;
	uint32_t_ TAWOT		: 1;
	uint32_t_ TASNAPS	: 1;
	uint32_t_ TAILD		: 1;
	uint32_t_ TAPWMIE	: 1;
	uint32_t_ TAMRSU	: 1;
	uint32_t_ TAPLO		: 1;
	uint32_t_			: 20;
}GPTMTAMR_BF;

typedef union
{
	uint32_t_		R;
	GPTMTAMR_BF		B;
}GPTMTAMR_TAG;

typedef struct
{
	uint32_t_ TBMR 		: 2;
	uint32_t_ TBCMR 	: 1;
	uint32_t_ TBAMS 	: 1;
	uint32_t_ TBCDIR 	: 1;
	uint32_t_ TBMIE 	: 1;
	uint32_t_ TBWOT 	: 1;
	uint32_t_ TBSNAPS 	: 1;
	uint32_t_ TBILD 	: 1;
	uint32_t_ TBPWMIE 	: 1;
	uint32_t_ TBMRSU 	: 1;
	uint32_t_ TBPLO 	: 1;
	uint32_t_ 			: 20;
}GPTMTBMR_BF;

typedef union
{
	uint32_t_		R;
	GPTMTBMR_BF		B;
}GPTMTBMR_TAG;

typedef struct
{
	uint32_t_ TAEN 		: 1;
	uint32_t_ TASTALL 	: 1;
	uint32_t_ TAEVENT 	: 2;
	uint32_t_ RTCEN 	: 1;
	uint32_t_ TAOTE 	: 1;
	uint32_t_ TAPWML 	: 1;
	uint32_t_ 			: 1;
	uint32_t_ TBEN 		: 1;
	uint32_t_ TBSTALL 	: 1;
	uint32_t_ TBEVENT 	: 2;
	uint32_t_ 			: 1;
	uint32_t_ TBOTE 	: 1;
	uint32_t_ TBPWML 	: 1;
	uint32_t_ 			: 17;
}GPTMCTL_BF;

typedef union
{
	uint32_t_		R;
	GPTMCTL_BF	B;
}GPTMCTL_TAG;

/**----------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
 *----------------------------------------------------------*/


#define GPT_OFFSET(x)	(x<8? ((0x40030000)+((x)*0x1000)):((0x4004C000)+((x-8)*0x1000)))

#define GPTMCFG_OFFSET									0x00000000
#define GPTMTAMR_OFFSET									0x00000004
#define GPTMTBMR_OFFSET									0x00000008
#define GPTMCTL_OFFSET									0x0000000C
#define GPTMIMR_OFFSET									0x00000018
#define GPTMICR_OFFSET									0x00000024
#define GPTMTAILR_OFFSET								0x00000028
#define GPTMTBILR_OFFSET								0x0000002C
#define GPTMTAPR_OFFSET									0X00000038
#define GPTMTAV_OFFSET									0x00000050
#define GPTMTBV_OFFSET									0x00000054


#define GPTMCFG(x)		(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMCFG_OFFSET)))
#define GPTMTAMR(x)		(*((volatile GPTMTAMR_TAG*)(GPT_OFFSET(x)+GPTMTAMR_OFFSET)))
#define GPTMTBMR(x)		(*((volatile GPTMTBMR_TAG*)(GPT_OFFSET(x)+GPTMTBMR_OFFSET)))
#define GPTMCTL(x)		(*((volatile GPTMCTL_TAG*)(GPT_OFFSET(x)+GPTMCTL_OFFSET)))
#define GPTMICR(x)		(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMICR_OFFSET)))
#define GPTMIMR(x)		(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMIMR_OFFSET)))
#define GPTMTAILR(x)	(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMTAILR_OFFSET)))
#define GPTMTBILR(x)	(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMTBILR_OFFSET)))
#define GPTMTAPR(x)		(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMTAPR_OFFSET)))
#define GPTMTAV(x)		(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMTAV_OFFSET)))
#define GPTMTBV(x)		(*((volatile uint32_t_*)(GPT_OFFSET(x)+GPTMTBV_OFFSET)))

#define RCGCTIMER_		(*((volatile uint32_t_*)(0x400FE000+0x604)))
#define RCGCWTIMER_		(*((volatile uint32_t_*)(0x400FE000+0x65C)))




#endif  /* GPT_PRIVATE_H */
/**********************************************************************************************************************
 *  END OF FILE: gpt_private.h
 *********************************************************************************************************************/
