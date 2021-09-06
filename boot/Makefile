TARGET = bootloader
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

BUILD_DIR = build
BUILD_BIN_DIR = $(BUILD_DIR)/bin

# Debug Instead cflag -O2 set -O0 -ggdb3
OPT = -O0 -ggdb3
#OPT = -O3
#OPT = -Os
# MCPU = MDR1986VE1T

# Select MCU architecture
# Instead cflag -mcpu=cortex-m3 use:
# -mcpu=cortex-m0     # MDR1986BE4
# -mcpu=cortex-m1     # MDR1986VE1T, MDR1986VE3
# -mcpu=cortex-m3     # MDR1986VE9x, MDR1901VC1T
# Instead compiler definition -DUSE_MDR1986VE9x use:
# -DUSE_MDR1901VC1T   # MDR1901VC1T
# -DUSE_MDR1986VE1T   # MDR1986VE1T
# -DUSE_MDR1986VE3    # MDR1986VE3
# -DUSE_MDR1986BE4    # MDR1986BE4
# -DUSE_MDR1986VE9x   # MDR1986VE9x
MCU = -mcpu=cortex-m1

# defines
AS_DEFS = 
C_DEFS = \
-DUSE_MDR1986VE1T

# includes
AS_INCLUDES = 
C_INCLUDES =  \
-Iemdr1986x-std-per-lib/CMSIS/CM1/CoreSupport \
-Iemdr1986x-std-per-lib/CMSIS/CM1/DeviceSupport/MDR1986VE1T/inc \
-Iemdr1986x-std-per-lib/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup \
-Iemdr1986x-std-per-lib/MDR32F9Qx_StdPeriph_Driver/inc \
-Iapp 

# sources
C_SOURCES = \
emdr1986x-std-per-lib/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/system_MDR1986VE1T.c \
emdr1986x-std-per-lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_port.c \
emdr1986x-std-per-lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_rst_clk.c \
emdr1986x-std-per-lib/MDR32F9Qx_StdPeriph_Driver/src/MDR32F9Qx_eeprom.c \
app/inits.c \
app/main.c \
app/MDR1986VE1T_IT.c


ASM_SOURCES = emdr1986x-std-per-lib/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/startup_MDR1986VE1T.S


# compile gcc flags
CFLAGS =    $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -mthumb -ffunction-sections -fdata-sections -Wall -Wextra -pedantic -Wshadow -Wredundant-decls -Wno-missing-field-initializers -Wno-packed-bitfield-compat -pipe -D__STARTUP_CLEAR_BSS -D__START=main

# Generate dependency information
# CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# link script
LDSCRIPT = emdr1986x-std-per-lib/CMSIS/CM1/DeviceSupport/MDR1986VE1T/startup/gcc/MDR1986VE1T_bootloader.ld
LDFLAGS = -T$(LDSCRIPT) $(MCU) -lm --specs=nosys.specs -Wl,--gc-sections -ffreestanding -nostartfiles -Wl,-Map=$(BUILD_BIN_DIR)/$(TARGET).map

OBJECTS =  $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

# $@ - Target name
# $< - First dependency name (source file name)

all: $(BUILD_BIN_DIR)/$(TARGET).elf $(BUILD_BIN_DIR)/$(TARGET).hex $(BUILD_BIN_DIR)/$(TARGET).bin

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_BIN_DIR)/$(TARGET).elf: $(OBJECTS) Makefile | $(BUILD_BIN_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_BIN_DIR)/%.hex: $(BUILD_BIN_DIR)/%.elf | $(BUILD_BIN_DIR)
	$(HEX) $< $@
	
$(BUILD_BIN_DIR)/%.bin: $(BUILD_BIN_DIR)/%.elf | $(BUILD_BIN_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@

$(BUILD_BIN_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)

prog: $(BUILD_BIN_DIR)/$(TARGET).elf
	./openocd/openocd_prog.sh $(BUILD_BIN_DIR)/$(TARGET).elf


# dependencies
# -include $(wildcard $(BUILD_DIR)/*.d)
