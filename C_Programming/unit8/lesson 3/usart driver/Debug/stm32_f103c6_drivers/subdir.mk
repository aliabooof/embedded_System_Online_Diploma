################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_drivers/STM32_F103C6_USART_Driver.c \
../stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.c 

OBJS += \
./stm32_f103c6_drivers/STM32_F103C6_USART_Driver.o \
./stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.o 

C_DEPS += \
./stm32_f103c6_drivers/STM32_F103C6_USART_Driver.d \
./stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_drivers/%.o stm32_f103c6_drivers/%.su stm32_f103c6_drivers/%.cyclo: ../stm32_f103c6_drivers/%.c stm32_f103c6_drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/stm32_f103c6_drivers/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-stm32_f103c6_drivers

clean-stm32_f103c6_drivers:
	-$(RM) ./stm32_f103c6_drivers/STM32_F103C6_USART_Driver.cyclo ./stm32_f103c6_drivers/STM32_F103C6_USART_Driver.d ./stm32_f103c6_drivers/STM32_F103C6_USART_Driver.o ./stm32_f103c6_drivers/STM32_F103C6_USART_Driver.su ./stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.cyclo ./stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.d ./stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.o ./stm32_f103c6_drivers/stm32_f103c6_drivers_EXTI.su

.PHONY: clean-stm32_f103c6_drivers

