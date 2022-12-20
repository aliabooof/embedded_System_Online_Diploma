################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
external_interrupt.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
external_interrupt.list \

OBJCOPY_BIN += \
external_interrupt.bin \


# All Target
all: external_interrupt.elf secondary-outputs

# Tool invocations
external_interrupt.elf: $(OBJS) $(USER_OBJS) D:\EmbadedSystemDiploma\C_Programming\embedded_System_Online_Diploma\C_Programming\unit6\lab1\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "external_interrupt.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\EmbadedSystemDiploma\C_Programming\embedded_System_Online_Diploma\C_Programming\unit6\lab1\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="external_interrupt.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

external_interrupt.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "external_interrupt.list"
	@echo 'Finished building: $@'
	@echo ' '

external_interrupt.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "external_interrupt.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
