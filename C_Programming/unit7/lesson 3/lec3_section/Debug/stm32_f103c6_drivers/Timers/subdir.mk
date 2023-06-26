################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_drivers/Timers/TIM.c 

OBJS += \
./stm32_f103c6_drivers/Timers/TIM.o 

C_DEPS += \
./stm32_f103c6_drivers/Timers/TIM.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_drivers/Timers/TIM.o: ../stm32_f103c6_drivers/Timers/TIM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/stm32_f103c6_drivers/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_drivers/Timers/TIM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

