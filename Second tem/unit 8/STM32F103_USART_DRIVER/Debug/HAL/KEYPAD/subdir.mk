################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEYPAD/KEYPAD.c 

OBJS += \
./HAL/KEYPAD/KEYPAD.o 

C_DEPS += \
./HAL/KEYPAD/KEYPAD.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KEYPAD/%.o HAL/KEYPAD/%.su HAL/KEYPAD/%.cyclo: ../HAL/KEYPAD/%.c HAL/KEYPAD/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-KEYPAD

clean-HAL-2f-KEYPAD:
	-$(RM) ./HAL/KEYPAD/KEYPAD.cyclo ./HAL/KEYPAD/KEYPAD.d ./HAL/KEYPAD/KEYPAD.o ./HAL/KEYPAD/KEYPAD.su

.PHONY: clean-HAL-2f-KEYPAD

