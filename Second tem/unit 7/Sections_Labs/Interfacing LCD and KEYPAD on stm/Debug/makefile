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
-include STM32F103_DRIVERS/GPIO_DRIVER/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
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


BUILD_ARTIFACT_NAME := Interfacing LCD and KEYPAD on stm
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Interfacing\ LCD\ and\ KEYPAD\ on\ stm.elf \

MAP_FILES += \
Interfacing\ LCD\ and\ KEYPAD\ on\ stm.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Interfacing\ LCD\ and\ KEYPAD\ on\ stm.list \

OBJCOPY_HEX += \
Interfacing\ LCD\ and\ KEYPAD\ on\ stm.hex \

OBJCOPY_BIN += \
Interfacing\ LCD\ and\ KEYPAD\ on\ stm.bin \


# All Target
all: main-build

# Main-build Target
main-build: Interfacing\ LCD\ and\ KEYPAD\ on\ stm.elf secondary-outputs

# Tool invocations
Interfacing\ LCD\ and\ KEYPAD\ on\ stm.elf Interfacing\ LCD\ and\ KEYPAD\ on\ stm.map: $(OBJS) $(USER_OBJS) D:\courses\EmbadedSystemDiploma\C_Programming\embedded_System_Online_Diploma\Second\ tem\unit\ 7\Interfacing\ LCD\ and\ KEYPAD\ on\ stm\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "Interfacing LCD and KEYPAD on stm.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\courses\EmbadedSystemDiploma\C_Programming\embedded_System_Online_Diploma\Second tem\unit 7\Interfacing LCD and KEYPAD on stm\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Interfacing LCD and KEYPAD on stm.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Interfacing\ LCD\ and\ KEYPAD\ on\ stm.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Interfacing LCD and KEYPAD on stm.list"
	@echo 'Finished building: $@'
	@echo ' '

Interfacing\ LCD\ and\ KEYPAD\ on\ stm.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Interfacing LCD and KEYPAD on stm.hex"
	@echo 'Finished building: $@'
	@echo ' '

Interfacing\ LCD\ and\ KEYPAD\ on\ stm.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Interfacing LCD and KEYPAD on stm.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Interfacing\ LCD\ and\ KEYPAD\ on\ stm.bin Interfacing\ LCD\ and\ KEYPAD\ on\ stm.elf Interfacing\ LCD\ and\ KEYPAD\ on\ stm.hex Interfacing\ LCD\ and\ KEYPAD\ on\ stm.list Interfacing\ LCD\ and\ KEYPAD\ on\ stm.map Interfacing\\ LCD\\ and\\ KEYPAD\\ on\\ stm.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
