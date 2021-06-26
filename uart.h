/***** FILE: uart.h *****
 *	This file is a part of Demo1 project.
 *	The file contains:
 *
 *	- Values definition:
 *		UART1_BRR_VAL
 *		(the value must be written to baud rate register);
 *
 *	- functions declaration (every of them has void type):
 *		configUart1 ();
 *		uartSetTransmitterOnlyMode (USART_TypeDef* uartX);
 *		uartSetRecieverOnlyMode (USART_TypeDef* uartX);
 *
 *	- inline functions definition (every of them has void type):
 *		uartSetTransmitterOnlyMode (USART_TypeDef* uartX);
 *		uartSetRecieverOnlyMode (USART_TypeDef* uartX);
 ************************
 */


#ifndef DEMO1_UART_H
#define DEMO1_UART_H


#include "stm32f10x.h"


// --- Values definition

#define F_CK 32000000
#define BAUD 9600
#define USARTDIVX16 (F_CK/BAUD)
#define UART1_BRR_VAL (USARTDIVX16)


// --- functions declaration

void configUart1 ();

inline void uartSetTransmitterOnlyMode (USART_TypeDef* uartX);
inline void uartSetRecieverOnlyMode (USART_TypeDef* uartX);


// --- inline functions definition

inline void uartSetTransmitterOnlyMode (USART_TypeDef* uartX) {

	uartX->CR1 = ( (uartX->CR1) & (~USART_CR1_RE) )  |  USART_CR1_TE | USART_CR1_TCIE;
	uartX->CR3 = ( (uartX->CR3) & (~USART_CR3_DMAR) )  |  USART_CR3_DMAT;

}

inline void uartSetRecieverOnlyMode (USART_TypeDef* uartX) {

	uartX->CR1 = ( (uartX->CR1) & (~USART_CR1_TE) & (~USART_CR1_TCIE) )  |  USART_CR1_RE;
	uartX->CR3 = ( (uartX->CR3) & (~USART_CR3_DMAT) )  |  USART_CR3_DMAR;

}


#endif

