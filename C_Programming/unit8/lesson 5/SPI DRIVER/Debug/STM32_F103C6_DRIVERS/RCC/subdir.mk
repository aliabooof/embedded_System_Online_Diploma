################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.c 

OBJS += \
./STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.o 

C_DEPS += \
./STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_DRIVERS/RCC/%.o STM32_F103C6_DRIVERS/RCC/%.su STM32_F103C6_DRIVERS/RCC/%.cyclo: ../STM32_F103C6_DRIVERS/RCC/%.c STM32_F103C6_DRIVERS/RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"C:/Users/aliab/OneDrive/Desktop/lesson 5/STM32_F103C6_DRIVERS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32_F103C6_DRIVERS-2f-RCC

clean-STM32_F103C6_DRIVERS-2f-RCC:
	-$(RM) ./STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.cyclo ./STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.d ./STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.o ./STM32_F103C6_DRIVERS/RCC/stm32_f103c6_RCC_driver.su

.PHONY: clean-STM32_F103C6_DRIVERS-2f-RCC

