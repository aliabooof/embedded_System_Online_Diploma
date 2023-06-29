################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAl/lcd_driver/LCD.c 

OBJS += \
./HAl/lcd_driver/LCD.o 

C_DEPS += \
./HAl/lcd_driver/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HAl/lcd_driver/%.o HAl/lcd_driver/%.su HAl/lcd_driver/%.cyclo: ../HAl/lcd_driver/%.c HAl/lcd_driver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/stm32_f103c6_drivers/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAl-2f-lcd_driver

clean-HAl-2f-lcd_driver:
	-$(RM) ./HAl/lcd_driver/LCD.cyclo ./HAl/lcd_driver/LCD.d ./HAl/lcd_driver/LCD.o ./HAl/lcd_driver/LCD.su

.PHONY: clean-HAl-2f-lcd_driver

