# STM32F10x UART+DMA low level programming demo

This is an echo project. Microcontroller reads a data string from external device and writes it to a buffer using UART and DMA. When a button "USER" is pressed, microcontroller echos the data.

## Hardware

I used Nucleo-F103RB board with STM32F103RBT6 microcontoller.
The button "USER" at port C pin 13 (PC13 == 1 when button is not pressed). 
Pins PA9 and PA10 (UART1 Tx and Rx) are connected to usb-uart adapter connected to a computer.

## Libraries

The project is created using CMSIS library.

## Build and upload

For building you need arm-none-eabi-gcc and ~-gcc-as compilers.
For uploading you can use st-flash utility.

For building just write "make".
For uploading using st-flash write "make upload".

