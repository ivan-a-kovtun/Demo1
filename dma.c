/***** FILE: dma.c *****
 *	This file is a part of Demo1 project.
 *	The file contains functions definition:
 *	- configDma ()
 *		(config 4 and 5 channels of DMA1);
 *	- startDmaTransmit (char *text, uint16_t textLength)
 *		(start data transmitting from the buffer
 *		 to an exteral device using DMA and UART);
 *	- startDmaReceive (char *startPoint, uint16_t maxLength)
 *		(start data reception from an exteral device
 *		 and write the data to the buffer using DMA and UART);
 *	- DMA1_CH4_IrqHandler (),
 *	- DMA1_CH5_IrqHandler ()
 *		(Both are DMA1 interrupt request handlers
 *		 for 4 and for 5 channel respectively,
 *		 in this project only TC irq is used);
 ***********************
 *	Note: startDmaTransmit and startDmaReceive
 *	use inline functions defined in "dma.h" and "uart.h"
 ***********************
 */

#include "stm32f10x.h"
#include "dma.h"
#include "uart.h"
#include "main.h"

extern volatile DmaUartState_t dmaUartState;

void configDma () {


	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	// DMA1_CH4 == uart1_Tx
	DMA1_Channel4->CCR |= DMA_CCR4_DIR | DMA_CCR4_MINC | DMA_CCR4_TCIE;

	// DMA1_CH5 == uart1_Rx
	DMA1_Channel5->CCR |= DMA_CCR5_MINC | DMA_CCR5_TCIE;

}

void startDmaTransmit (char *text, uint16_t textLength) {

	dmaUartState = dmaTransmitsBufferToUart;
	uartSetTransmitterOnlyMode (USART1);
	startDmaUart1Tx (text, textLength);

}

void startDmaReceive (char *startPoint, uint16_t maxLength) {

	dmaUartState = dmaTransmitsFromUartToBuffer;
	uartSetRecieverOnlyMode (USART1);
	startDmaUart1Rx (startPoint, maxLength);

}


// --- Interrupt handlers

void DMA1_CH4_IrqHandler () {

	dmaUartState = dmaFinishedBufferToUartTransmission;
	DMA1_Channel4->CCR &= ~ DMA_CCR4_EN;
	DMA1->IFCR = DMA_IFCR_CTCIF4;

}

void DMA1_CH5_IrqHandler () {

	dmaUartState = bufferOverFlow;
	DMA1_Channel5->CCR &= ~ DMA_CCR5_EN;
	DMA1->IFCR = DMA_IFCR_CTCIF5;

}


