/***** FILE: main.c *****
 *	This file is a part of Demo1 project.
 *	The file contains main function.
 ************************
 */

#include "stm32f10x.h"
#include "dma.h"
#include "uart.h"
#include "button.h"
#include <string.h>

const char bufStart[] = "\n\r>>>";

char buffer[BUF_LEN];
volatile uint16_t B1IsPressed = 0;
volatile uint16_t dmaUartState;
volatile uint16_t len;

void main() {

	configUart1 ();
	configDma ();
	configButtonPort ();

	// cofig NVIC
	__enable_irq ();
	NVIC_EnableIRQ (DMA1_Channel4_IRQn);
	NVIC_EnableIRQ (DMA1_Channel5_IRQn);
	NVIC_EnableIRQ (USART1_IRQn);
	NVIC_EnableIRQ (EXTI15_10_IRQn);

	strcpy (buffer, bufStart);
	len = strlen (bufStart);

	startDmaTransmit (buffer, len);

	while (1) {

		if (dmaUartState == 2) {
			len = strlen (bufStart);
			startDmaReceive (buffer + len, BUF_LEN - len);
		}

		if (B1IsPressed) {
			B1IsPressed = 0;
			startDmaTransmit (buffer, len);
		}

	}
}

