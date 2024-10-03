# Makefile for building helloworld with arm-none-eabi-gcc

DEBUG = 1

# Compiler and tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc  # Use gcc for assembling as well
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

BUILD_DIR = build

# Compiler and assembler flags
CFLAGS = -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -fmessage-length=0 -Werror -std=c17
ASFLAGS = $(CFLAGS)  # Reuse the same flags for assembler

# Get the current Git commit hash (short format)
GIT_HASH := $(shell git rev-parse --short HEAD)

# Get the current Git commit date and time (escape spaces)
GIT_COMMIT_TIME := $(shell git log -1 --format=%cd --date=format:'%Y-%m-%d %H:%M:%S' | sed 's/ /_/g')

# Get the most recent Git tag, or commit hash if no tag exists (with -dirty if applicable)
GIT_TAG := $(shell git describe --tags --always --dirty)

# Get the current Git branch name
GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)

# Check if the working directory is dirty (has uncommitted changes)
GIT_DIRTY := $(shell test -n "$$(git status --porcelain)" && echo "dirty" || echo "clean")

# Get the username (author of the build)
USER := $(shell whoami)

# Get the hostname of the machine where the build is taking place
HOSTNAME := $(shell hostname)

# Get the current build date and time
BUILD_TIME := $(shell date '+%Y-%m-%d_%H:%M:%S')

# Add the Git information as defines to CFLAGS (escape double quotes properly)
CFLAGS += -DGIT_HASH=\"$(GIT_HASH)\"
CFLAGS += -DGIT_COMMIT_TIME=\"$(GIT_COMMIT_TIME)\"
CFLAGS += -DGIT_TAG=\"$(GIT_TAG)\"
CFLAGS += -DGIT_BRANCH=\"$(GIT_BRANCH)\"
CFLAGS += -DGIT_DIRTY=\"$(GIT_DIRTY)\"
CFLAGS += -DUSER=\"$(USER)\"
CFLAGS += -DHOSTNAME=\"$(HOSTNAME)\"
CFLAGS += -DBUILD_TIME=\"$(BUILD_TIME)\"

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG
endif

# Include directories
INCLUDES = \
-Iplatform/ps7_cortexa9_0/freertos10_xilinx_domain/bsp/ps7_cortexa9_0/include/ \
\
-Iapps \
-Iapps/system \
-Iapps/buttons \
-Iapps/cps_network/ \
-Iapps/disp/ \
-Iapps/debugging/ \
\
-Idrivers \
-Idrivers/gpio \
-Idrivers/spi \
-Idrivers/uarts \
-Idrivers/gui \
\
-Ilibs \
\
-Isubmodules/CameraMessages/ \
-Isubmodules/CameraMessages/cpubsub/ \
-Isubmodules/CameraMessages/cpubsub/base64/ \
-Isubmodules/embedlib/log/ \
-Isubmodules/embedlib/ssd1309z/ \
-Isubmodules/embedlib/dmgui/ \


# Source files
SRC = \
main.c \
\
apps/apps.c \
apps/system/system.c \
apps/system/actions.c \
apps/buttons/buttons.c \
apps/buttons/shutter_button.c \
apps/cps_network/net_pub.c \
apps/disp/display.c \
apps/debugging/debugging.c \
\
drivers/cps/pipe_interface_freertos.c \
drivers/cps/cps_interface.c \
drivers/logging/logging.c \
drivers/gpio/gpio.c \
drivers/spi/spi.c \
drivers/uarts/uart.c \
drivers/disp/disp_interface.c \
drivers/gui/gui.c \
\
submodules/CameraMessages/messages.c \
submodules/CameraMessages/cpubsub/cpubsub.c \
submodules/CameraMessages/cpubsub/cpubsub_network.c \
submodules/CameraMessages/cpubsub/pipe.c \
submodules/CameraMessages/cpubsub/base64/base64.c \
submodules/embedlib/log/log.c \
submodules/embedlib/ssd1309z/ssd1309z.c \
submodules/embedlib/dmgui/dmgui.c \


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
