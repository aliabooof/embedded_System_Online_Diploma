################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32_F103C6_DRIVERS/UART/subdir.mk
-include STM32_F103C6_DRIVERS/RCC/subdir.mk
-include STM32_F103C6_DRIVERS/GPIO/subdir.mk
-include STM32_F103C6_DRIVERS/EXTI/subdir.mk
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


BUILD_ARTIFACT_NAME := SPI DRIVER
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SPI\ DRIVER.elf \

MAP_FILES += \
SPI\ DRIVER.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SPI\ DRIVER.list \

OBJCOPY_HEX += \
SPI\ DRIVER.hex \


# All Target
all: main-build

# Main-build Target
main-build: SPI\ DRIVER.elf secondary-outputs

# Tool invocations
SPI\ DRIVER.elf SPI\ DRIVER.map: $(OBJS) $(USER_OBJS) C:\Users\aliab\OneDrive\Desktop\lesson\ 5\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SPI DRIVER.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\aliab\OneDrive\Desktop\lesson 5\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SPI DRIVER.map" -Wl,--gc-sections -static -L"C:\Users\aliab\OneDrive\Desktop\lesson 5\STM32_F103C6_DRIVERS\inc" --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SPI\ DRIVER.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SPI DRIVER.list"
	@echo 'Finished building: $@'
	@echo ' '

SPI\ DRIVER.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "SPI DRIVER.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SPI\ DRIVER.elf SPI\ DRIVER.hex SPI\ DRIVER.list SPI\ DRIVER.map SPI\\ DRIVER.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
