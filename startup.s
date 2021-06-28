/***** FILE: startup.s *****
 * This file is a part of Demo1 project.
 * The file contains:
 * - interrupt vector table;
 * - CopyDataInit, the function copying initial data values from ROM to RAM;
 * - program start point calling CopyDataInit, SystemInit and main functions.
 ************************
 */



.cpu cortex-m3
.thumb



.section .rodata

/* start address for the initialization values of the .data section.
defined in linker script */
.word _InitDataStart

/* start address for the .data section. defined in linker script */
.word _DataStart

/* end address for the .data section. defined in linker script */
.word _DataEnd

/* start address for the .bss section. defined in linker script */
.word _BssStart

/* end address for the .bss section. defined in linker script */
.word _BssEnd



.section .text

.global _vector

_vector:

.word	_stack_base
.word	_reset

.word	hang			@; NMI Handler
.word	hang			@; Hard Fault Handler
.word	hang			@; MPU Fault Handler
.word	hang			@; Bus Fault Handler
.word	hang			@; Usage Fault Handler
.word	0				@; Reserved
.word	0				@; Reserved
.word	0				@; Reserved
.word	0				@; Reserved
.word	hang			@; SVCall Handler
.word	hang			@; Debug Monitor Handler
.word	0				@; Reserved
.word	hang			@; PendSV Handler
.word	hang			@; SysTick Handler

                @; External Interrupts
.word	hang			@; Window Watchdog
.word	hang			@; PVD through EXTI Line detect
.word	hang			@; Tamper
.word	hang			@; RTC
.word	hang			@; Flash
.word	hang			@; RCC
.word	hang			@; EXTI Line 0
.word	hang			@; EXTI Line 1
.word	hang			@; EXTI Line 2
.word	hang			@; EXTI Line 3
.word	hang			@; EXTI Line 4
.word	hang			@; DMA1 Channel 1
.word	hang			@; DMA1 Channel 2
.word	hang			@; DMA1 Channel 3
.word	DMA1_CH4_IrqHandler	@; DMA1 Channel 4
.word	DMA1_CH5_IrqHandler	@; DMA1 Channel 5
.word	hang			@; DMA1 Channel 6
.word	hang			@; DMA1 Channel 7
.word	hang			@; ADC1_2
.word	hang			@; USB High Priority or CAN1 TX
.word	hang			@; USB Low  Priority or CAN1 RX0
.word	hang			@; CAN1 RX1
.word	hang			@; CAN1 SCE
.word	hang			@; EXTI Line 9..5
.word	hang			@; TIM1 Break
.word	hang			@; TIM1 Update
.word	hang			@; TIM1 Trigger and Commutation
.word	hang			@; TIM1 Capture Compare
.word	hang			@; TIM2
.word	hang			@; TIM3
.word	hang			@; TIM4
.word	hang			@; I2C1 Event
.word	hang			@; I2C1 Error
.word	hang			@; I2C2 Event
.word	hang			@; I2C2 Error
.word	hang			@; SPI1
.word	hang			@; SPI2
.word	USART1_IrqHandler	@; USART1
.word	hang			@; USART2
.word	hang			@; USART3
.word	EXTI15_10_IRQHandler	@; EXTI Line 15..10
.word	hang			@; RTC Alarm through EXTI Line
.word	hang			@; USB Wakeup from suspend



.global hang
.extern main

.thumb_func
hang:	b .

.thumb_func
_reset:

		bl CopyDataInit
		bl SystemInit
		bl main
		b .

/* This function copies data initial
 * values from ROM to RAM and
 * fill BSS segment with zeros. */

.thumb_func
CopyDataInit:

		ldr r0, =_InitDataStart
		ldr r1, =_DataStart
		ldr r2, =_DataEnd

		cmp r1, r2
		beq FillingStart

.thumb_func
Copying:

		ldr r3, [r0]
		add r0, r0, #4
		str r3, [r1]
		add r1, r1, #4
		cmp r1, r2
		bne Copying

.thumb_func
FillingStart:

		ldr r1, =_BssStart
		ldr r2, =_BssEnd
		mov r3, #0

		cmp r1, r2
		beq Return

.thumb_func
Filling:

		str r3, [r1]
		add r1, r1, #4
		cmp r1, r2
		bne Filling

.thumb_func
Return:	bx lr


