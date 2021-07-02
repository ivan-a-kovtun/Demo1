/***** FILE: button.c *****
 *	This file is a part of Demo1 project.
 *	The file contains functions definition:
 *	- configButtonPort ()
 *		(config PC13 because it is connected to button
 *		 also config external interrupt controller);
 *	- EXTI15_10_IRQHandler ()
 *		(PC13 interrupt request hanlder);
 **************************
 */

#include "button.h"
#include "main.h"
#include "stm32f10x.h"

extern volatile uint16_t B1IsPressed;
extern volatile uint16_t len;

void configButtonPort () {

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;

	// PC13 to float input
	GPIOC->CRH |= GPIO_CRH_CNF13_0;
	GPIOC->CRH &= ~ (GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13);

	EXTI->EMR |= EXTI_EMR_MR13;
	EXTI->IMR |= EXTI_IMR_MR13;
	EXTI->RTSR |= EXTI_RTSR_TR13;
	EXTI->FTSR |= EXTI_FTSR_TR13;

	AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;

}

void EXTI15_10_IRQHandler () {

	B1IsPressed = ! (GPIOC->IDR & GPIO_IDR_IDR13);
	if (B1IsPressed) {
		DMA1_Channel5->CCR &= ~ DMA_CCR5_EN;
		len = BUF_LEN - DMA1_Channel5->CNDTR;
	}
	EXTI->PR = EXTI_PR_PR13;

}

