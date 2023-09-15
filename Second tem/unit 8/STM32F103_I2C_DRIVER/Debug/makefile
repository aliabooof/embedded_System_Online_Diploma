################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32F103_DRIVERS/USART_DRIVER/subdir.mk
-include STM32F103_DRIVERS/SPI_DRIVER/subdir.mk
-include STM32F103_DRIVERS/RCC_DRIVER/subdir.mk
-include STM32F103_DRIVERS/I2C_DRIVER/subdir.mk
-include STM32F103_DRIVERS/GPIO_DRIVER/subdir.mk
-include STM32F103_DRIVERS/EXTI_DRIVER/subdir.mk
-include HAL/EEPROM/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := STM32F103_I2C_DRIVER
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32F103_I2C_DRIVER.elf \

MAP_FILES += \
STM32F103_I2C_DRIVER.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F103_I2C_DRIVER.list \

OBJCOPY_HEX += \
STM32F103_I2C_DRIVER.hex \

OBJCOPY_BIN += \
STM32F103_I2C_DRIVER.bin \

OBJCOPY_VERILOG += \
STM32F103_I2C_DRIVER.verilog \

OBJCOPY_SREC += \
STM32F103_I2C_DRIVER.srec \

OBJCOPY_SYMBOLSREC += \
STM32F103_I2C_DRIVER.symbolsrec \


# All Target
all: main-build

# Main-build Target
main-build: STM32F103_I2C_DRIVER.elf secondary-outputs

# Tool invocations
STM32F103_I2C_DRIVER.elf STM32F103_I2C_DRIVER.map: $(OBJS) $(USER_OBJS) D:\courses\EmbadedSystemDiploma\C_Programming\embedded_System_Online_Diploma\Second\ tem\unit\ 8\STM32F103_I2C_DRIVER\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "STM32F103_I2C_DRIVER.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\courses\EmbadedSystemDiploma\C_Programming\embedded_System_Online_Diploma\Second tem\unit 8\STM32F103_I2C_DRIVER\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F103_I2C_DRIVER.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F103_I2C_DRIVER.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F103_I2C_DRIVER.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32F103_I2C_DRIVER.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "STM32F103_I2C_DRIVER.hex"
	@echo 'Finished building: $@'
	@echo ' '

STM32F103_I2C_DRIVER.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32F103_I2C_DRIVER.bin"
	@echo 'Finished building: $@'
	@echo ' '

STM32F103_I2C_DRIVER.verilog: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O verilog $(EXECUTABLES) "STM32F103_I2C_DRIVER.verilog"
	@echo 'Finished building: $@'
	@echo ' '

STM32F103_I2C_DRIVER.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "STM32F103_I2C_DRIVER.srec"
	@echo 'Finished building: $@'
	@echo ' '

STM32F103_I2C_DRIVER.symbolsrec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O symbolsrec $(EXECUTABLES) "STM32F103_I2C_DRIVER.symbolsrec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32F103_I2C_DRIVER.bin STM32F103_I2C_DRIVER.elf STM32F103_I2C_DRIVER.hex STM32F103_I2C_DRIVER.list STM32F103_I2C_DRIVER.map STM32F103_I2C_DRIVER.srec STM32F103_I2C_DRIVER.symbolsrec STM32F103_I2C_DRIVER.verilog default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN) $(OBJCOPY_VERILOG) $(OBJCOPY_SREC) $(OBJCOPY_SYMBOLSREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
