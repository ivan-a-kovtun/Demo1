
BUILD_DIR := build

INCLUDE_DIRS += -Icmsis

CFLAGS += -g -O2 -mthumb -mcpu=cortex-m3

all:
	mkdir -p $(BUILD_DIR)
	arm-none-eabi-as -g boot.s -o $(BUILD_DIR)/boot.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDE_DIRS) -c main.c -o $(BUILD_DIR)/main.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDE_DIRS) -c SystemInit.c -o $(BUILD_DIR)/SystemInit.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDE_DIRS) -c uart.c -o $(BUILD_DIR)/uart.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDE_DIRS) -c dma.c -o $(BUILD_DIR)/dma.o
	arm-none-eabi-gcc $(CFLAGS) $(INCLUDE_DIRS) -c button.c -o $(BUILD_DIR)/button.o
	arm-none-eabi-ld -g -o $(BUILD_DIR)/out.elf -T mem.ld $(BUILD_DIR)/boot.o $(BUILD_DIR)/SystemInit.o $(BUILD_DIR)/main.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/dma.o $(BUILD_DIR)/button.o
	arm-none-eabi-objdump -D $(BUILD_DIR)/out.elf > $(BUILD_DIR)/out.lst
	arm-none-eabi-objcopy $(BUILD_DIR)/out.elf $(BUILD_DIR)/out.bin -O binary

clean:
	rm -r $(BUILD_DIR)

upload:
	st-flash write $(BUILD_DIR)/out.bin 0x08000000


