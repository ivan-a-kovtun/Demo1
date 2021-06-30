

#define BUF_LEN 64

typedef enum DmaUartState_EnumType {

	dmaTransmitsBufferToUart,
	dmaFinishedBufferToUartTransmission,
	uartTransmissionComplete,
	dmaTransmitsFromUartToBuffer,
	bufferOverFlow,

} DmaUartState_t;


