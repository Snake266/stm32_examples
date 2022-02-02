#This is example of Makefile that just work
MCU := cortex-m3
ARCH := armv7-m

CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
OBJCOPY := arm-none-eabi-objcopy
LD :=arm-none-eabi-ld
SIZE := arm-none-eabi-size
SF := st-flash

TARGET := blink

INC_DIR := ../system
INC := -I$(INC_DIR)
OBJ_DIR := $(INC_DIR)/build
SYSTEM_OBJ := $(wildcard $(OBJ_DIR)/*.o)
DEF := -DSTM32F10X_MD

CFLAGS = -std=gnu99 -mthumb -mcpu=$(MCU) --specs=nosys.specs $(DEF) $(INC)
CFLAGS += -Wall
CFLAGS += -O0
CFLAGS += -g
CFLAGS += -nostartfiles -nostdlib

ASFLAGS = -mthumb -mcpu=$(MCU) -g -Wall

FLASH_ADDR=0x08000000

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).elf: main.o
	$(LD) -Tscript.ld -g -o $(TARGET).elf $(SYSTEM_OBJ) main.o

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

all: $(TARGET).bin
	$(SIZE) $(TARGET).elf

clear:
	@rm *.o *.elf *.bin

flash:
	$(SF) write $(TARGET).bin $(FLASH_ADDR)

.PHONY: clear flash all
# end
