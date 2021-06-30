/***** FILE: uart.c *****
 *	This file is a part of Demo1 project.
 *	The file contains functions definition:
 *	- configUart1 ()
 *		(config pins used for uart and USART1 module);
 *	- USART1_IrqHandler ()
 *		(uart interrupt request hanlder,
 *		 in this project only TC irq is used);
 ************************
 */

#include "stm32f10x.h"
#include "uart.h"
#include "main.h"

extern volatile DmaUartState_t dmaUartState;

void configUart1 () {

	// enable clock to uart1 and pins
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;

	// config controller pins to work as uart1 
	// PA10 - Rx - input float
	GPIOA->CRH |=   (GPIO_CRH_CNF10_0);
	GPIOA->CRH &= ~ (GPIO_CRH_MODE10 | GPIO_CRH_CNF10_1);
	// PA9 - Tx - output alternative
	GPIOA->CRH |=   (GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1);
	GPIOA->CRH &= ~ (GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_0);

	// config USART1
	USART1->CR1 |= USART_CR1_UE;
	USART1->BRR = UART1_BRR_VAL;
	// for other settings defaulf values are Ok.
	uartSetTransmitterOnlyMode (USART1);

}

void USART1_IrqHandler () {

	dmaUartState = uartTransmissionComplete;
	USART1->SR &= ~ USART_SR_TC;

}

