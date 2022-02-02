##
#
#
# @file
# @version 0.1
MCU=cortex-m3
ARCH=armv7-m

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as


BUILD_DIR=build
DEF=-DSTM32F10X_MD

CFLAGS = -std=gnu99 -mthumb -mcpu=$(MCU) --specs=nosys.specs $(DEF)
CFLAGS += -O0 -g
ASFLAGS = -mthumb -mcpu=$(MCU) -g -Wall

OBJ=core_cm3.o startup_stm32f10x_md.o system_stm32f10x.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $<
%.o: %.s
	$(AS) $(ASFLAGS) -c -o $(BUILD_DIR)/$@ $<

all: $(OBJ)
# end
