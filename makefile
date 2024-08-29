# Makefile for building helloworld with arm-none-eabi-gcc

# Compiler and tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc  # Use gcc for assembling as well
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

BUILD_DIR = build

# Compiler and assembler flags
CFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -fmessage-length=0 -Werror -std=c17
ASFLAGS = $(CFLAGS)  # Reuse the same flags for assembler

# Include directories
INCLUDES = \
-Iplatform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/include/ \
\
-Iapps \
-Iapps/system \
-Iapps/buttons \
-Iapps/cps_network/ \
\
-Idrivers \
-Idrivers/gpio \
-Idrivers/spi \
-Idrivers/uarts \
\
-Ilibs \
\
-Isubmodules/CameraMessages/ \
-Isubmodules/CameraMessages/cpubsub/ \
-Isubmodules/CameraMessages/cpubsub/base64/ \
-Isubmodules/embedlib/log/

# Source files
SRC = \
main.c \
\
apps/apps.c \
apps/system/system.c \
apps/buttons/buttons.c \
apps/buttons/shutter_button.c \
apps/cps_network/net_pub.c \
\
drivers/cps/pipe_interface_freertos.c \
drivers/cps/cps_interface.c \
drivers/logging/logging.c \
drivers/gpio/gpio.c \
drivers/spi/spi.c \
drivers/uarts/uart.c \
\
submodules/CameraMessages/messages.c \
submodules/CameraMessages/cpubsub/cpubsub.c \
submodules/CameraMessages/cpubsub/cpubsub_network.c \
submodules/CameraMessages/cpubsub/pipe.c \
submodules/CameraMessages/cpubsub/base64/base64.c \
submodules/embedlib/log/log.c \


# Directories for prebuilt object files
PREBUILT_OBJ_DIRS = \
platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/lib/ \
platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/libsrc/lwip220_v1_0/src/ \
platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/libsrc/freertos10_xilinx_v1_15/src/ \
platform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/libsrc/xilffs_v5_2/src/ \

# Linker flags
LDFLAGS = -Wl,-build-id=none \
          -specs=Xilinx.spec \
          -Wl,-T,lscript.ld \
          -Lplatform/export/platform/sw/platform/freertos10_xilinx_domain/bsplib/lib

# Object files
C_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
PREBUILT_OBJS = $(foreach dir, $(PREBUILT_OBJ_DIRS), $(wildcard $(dir)/*.o))
OBJ = $(C_OBJS) $(PREBUILT_OBJS)

# Target
TARGET = $(BUILD_DIR)/camera

# VPATH for source files
VPATH = $(dir $(SRC))

# Build rules
all: $(BUILD_DIR) $(TARGET).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(AS) $(ASFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $(OBJ)

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)

# Optional rule to display the disassembly
disasm: $(TARGET).elf
	$(OBJDUMP) -d $< > $(BUILD_DIR)/$(TARGET).asm

.PHONY: all clean disasm
