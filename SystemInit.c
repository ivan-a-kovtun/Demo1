/***** FILE: SystemInit.c *****
 *	This file is a part of Demo1 project.
 *	The file contains SystemInit function.
 ******************************
 *	SystemInit fuction configure and turn on PLL.
 *	HSI (8 MHZ) is used, PLL out is 32 MHz.
 *	And there is a clock divider by 2 between HSI and PLL.
 ******************************
 *	SYSCLK  =  HSI(8) / 2 * PLL(8)  ==  32 MHz  
 ******************************
 */



#include "stm32f10x.h"

void SystemInit () {

	// config PLL
	RCC->CFGR |= RCC_CFGR_PLLMULL8;

	// run PLL;
	RCC->CR |= RCC_CR_PLLON;

	// wait until PLL is ready;
	while ( ! (RCC->CR & RCC_CR_PLLRDY) );

	// Config FLASH access. It is needed because SYSCLK = 32 > 24 (MHz).
	FLASH->ACR |= 0x01;

	// select PLL as SYSCLK source;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// wait until system clock is switched;
	while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

}


