################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32_f103c6_drivers/GPIO/stm32_f103c6_Driver.c 

OBJS += \
./stm32_f103c6_drivers/GPIO/stm32_f103c6_Driver.o 

C_DEPS += \
./stm32_f103c6_drivers/GPIO/stm32_f103c6_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
stm32_f103c6_drivers/GPIO/stm32_f103c6_Driver.o: ../stm32_f103c6_drivers/GPIO/stm32_f103c6_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec2/lab2/stm32_f103c6_drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32_f103c6_drivers/GPIO/stm32_f103c6_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

