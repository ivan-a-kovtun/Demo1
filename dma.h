/***** FILE: dma.h *****
 *	This file is a part of Demo1 project.
 *	The file contains:
 *
 *	- functions declaration (every of them has void type):
 *		configDma ();
 *		startDmaTransmit (char *text, uint16_t textLength);
 *		startDmaReceive (char *startPoint, uint16_t maxLength);
 *		startDmaUart1Tx (char *text, uint16_t textLength);
 *		startDmaUart1Rx (char *startPoint, uint16_t maxLength);
 *
 *	- inline functions definition (every of them has void type):
 *		startDmaUart1Tx (char *text, uint16_t textLength);
 *		startDmaUart1Rx (char *startPoint, uint16_t maxLength);
 ***********************
 */


#ifndef DEMO1_DMA_H
#define DEMO1_DMA_H


#include "stm32f10x.h"


// --- function declarations

void configDma ();
void startDmaTransmit (char *text, uint16_t textLength);
void startDmaReceive (char *startPoint, uint16_t maxLength);

inline void startDmaUart1Tx (char *text, uint16_t textLength);
inline void startDmaUart1Rx (char *startPoint, uint16_t maxLength);


// --- inline function definitions

inline void startDmaUart1Tx (char *text, uint16_t textLength) {

	// stop DMA1 Ch5 (Uart1 Rx)
	DMA1_Channel5->CCR &= ~ DMA_CCR5_EN;

	// start DMA1 Ch4 (Uart1 Tx)
	DMA1_Channel4->CPAR = &(USART1->DR);
	DMA1_Channel4->CMAR = text;
	DMA1_Channel4->CNDTR = textLength;
	DMA1_Channel4->CCR |= DMA_CCR4_EN;

}

inline void startDmaUart1Rx (char *startPoint, uint16_t maxLength) {

	// start DMA1 Ch5 (Uart1 Rx)
	DMA1_Channel5->CPAR = &(USART1->DR);
	DMA1_Channel5->CMAR = startPoint;
	DMA1_Channel5->CNDTR = maxLength;
	DMA1_Channel5->CCR |= DMA_CCR5_EN;

}


#endif

