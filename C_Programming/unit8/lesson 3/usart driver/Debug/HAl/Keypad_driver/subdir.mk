################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAl/Keypad_driver/KEYPAD.c 

OBJS += \
./HAl/Keypad_driver/KEYPAD.o 

C_DEPS += \
./HAl/Keypad_driver/KEYPAD.d 


# Each subdirectory must supply rules for building sources it contributes
HAl/Keypad_driver/%.o HAl/Keypad_driver/%.su HAl/Keypad_driver/%.cyclo: ../HAl/Keypad_driver/%.c HAl/Keypad_driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/stm32_f103c6_drivers/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAl-2f-Keypad_driver

clean-HAl-2f-Keypad_driver:
	-$(RM) ./HAl/Keypad_driver/KEYPAD.cyclo ./HAl/Keypad_driver/KEYPAD.d ./HAl/Keypad_driver/KEYPAD.o ./HAl/Keypad_driver/KEYPAD.su

.PHONY: clean-HAl-2f-Keypad_driver

