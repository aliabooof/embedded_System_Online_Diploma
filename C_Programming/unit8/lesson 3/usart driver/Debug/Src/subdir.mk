################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/lesson 3/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/HAl/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/lesson 3/usart driver/stm32_f103c6_drivers/inc" -I"D:/courses/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit8/lesson 3/usart driver/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/HAl/inc" -I"D:/EmbadedSystemDiploma/C_Programming/embedded_System_Online_Diploma/C_Programming/unit7/lec3_section/stm32_f103c6_drivers/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

