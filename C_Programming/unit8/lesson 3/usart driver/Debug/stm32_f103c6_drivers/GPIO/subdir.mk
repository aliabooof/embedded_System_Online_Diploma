################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.c 

OBJS += \
./stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.o 

C_DEPS += \
./stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_drivers/GPIO/%.o stm32_f103c6_drivers/GPIO/%.su stm32_f103c6_drivers/GPIO/%.cyclo: ../stm32_f103c6_drivers/GPIO/%.c stm32_f103c6_drivers/GPIO/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/lesson 3/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/lesson 3/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/lesson 3/usart driver/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/stm32_f103c6_drivers/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-stm32_f103c6_drivers-2f-GPIO

clean-stm32_f103c6_drivers-2f-GPIO:
	-$(RM) ./stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.cyclo ./stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.d ./stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.o ./stm32_f103c6_drivers/GPIO/stm32_f103c6_gpio_drivers.su

.PHONY: clean-stm32_f103c6_drivers-2f-GPIO

