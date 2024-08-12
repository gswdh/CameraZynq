# Makefile for building helloworld with arm-none-eabi-gcc

# Compiler and tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc  # Use gcc for assembling as well
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

# Compiler and assembler flags
CFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -fmessage-length=0 -Werror
ASFLAGS = $(CFLAGS)  # Reuse the same flags for assembler

# Include directories
INCLUDES = \
-Iplatform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/arm/cortexa9/ \
-Iplatform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/ \
-Iplatform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/include/ \
-Iplatform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/iicps_v3_19/src/ \
# -I~/Xilinx/Vitis/2024.1/gnu/aarch32/lin/gcc-arm-none-eabi/x86_64-oesdk-linux/usr/lib/arm-xilinx-eabi/gcc/arm-xilinx-eabi/12.2.0/include \
# -I~/Xilinx/Vitis/2024.1/gnu/aarch32/lin/gcc-arm-none-eabi/x86_64-oesdk-linux/usr/lib/arm-xilinx-eabi/gcc/arm-xilinx-eabi/12.2.0/include-fixed \
# -I~/Xilinx/Vitis/2024.1/gnu/aarch32/lin/gcc-arm-none-eabi/x86_64-oesdk-linux/usr/include/

# Linker flags
LDFLAGS = -Wl,-build-id=none \
          -specs=Xilinx.spec \
          -Wl,-T,lscript.ld \
          -Lplatform/export/platform/sw/platform/standalone_domain/bsplib/lib

# Directories
SRC_DIRS = \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/uartps_v3_14/src \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/iicps_v3_19/src

BUILD_DIR = build

# Source files
SRC = \
main.c \
platform.c \
$(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

ASM_SRC = \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/arm/cortexa9/gcc/asm_vectors.S \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/arm/cortexa9/gcc/boot.S \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/arm/cortexa9/gcc/translation_table.S \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/arm/cortexa9/gcc/xil-crt0.S \
platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/arm/cortexa9/gcc/cpu_init.S \

# Object files
C_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
ASM_OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(ASM_SRC:.S=.o)))
OBJ = $(C_OBJS) $(ASM_OBJS)

# Target
TARGET = $(BUILD_DIR)/camera

# Build rules
all: $(BUILD_DIR) $(TARGET).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/uartps_v3_14/src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/iicps_v3_19/src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: platform/ps7_cortexa9_0/standalone_domain/bsp/ps7_cortexa9_0/libsrc/standalone_v9_1/src/arm/cortexa9/gcc/%.S
	$(AS) $(ASFLAGS) $(INCLUDES) -c $< -o $@

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
