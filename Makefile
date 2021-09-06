TARGET = bootloader_and_app
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CP = $(GCC_PATH)/$(PREFIX)objcopy
else
CP = $(PREFIX)objcopy
endif

BUILD_DIR = build
BOOTLOADER_DIR = bootloader
DEMO_APP_DIR = demo_app
BOOTLOADER_BIN =  $(BOOTLOADER_DIR)/build/bin/bootloader.bin
DEMO_APP_BIN = $(DEMO_APP_DIR)/build/bin/demo_app.bin

# $@ - Target name
# $< - First dependency name (source file name)
all: $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR) $(BOOTLOADER_BIN) $(DEMO_APP_BIN)
	cat $(BOOTLOADER_BIN) $(DEMO_APP_BIN) > $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)
	$(CP) --input-target=binary --output-target=ihex $(BUILD_DIR)/$(TARGET).bin $@

$(BOOTLOADER_BIN):
	cd $(BOOTLOADER_DIR) && $(MAKE)

$(DEMO_APP_BIN):
	cd $(DEMO_APP_DIR) && $(MAKE)

$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)
	cd $(BOOTLOADER_DIR) && $(MAKE) clean
	cd $(DEMO_APP_DIR) && $(MAKE) clean

