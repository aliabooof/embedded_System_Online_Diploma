################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.c 

OBJS += \
./STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.o 

C_DEPS += \
./STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_DRIVERS/EXTI/%.o STM32_F103C6_DRIVERS/EXTI/%.su STM32_F103C6_DRIVERS/EXTI/%.cyclo: ../STM32_F103C6_DRIVERS/EXTI/%.c STM32_F103C6_DRIVERS/EXTI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"C:/Users/aliab/OneDrive/Desktop/lesson 5/STM32_F103C6_DRIVERS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32_F103C6_DRIVERS-2f-EXTI

clean-STM32_F103C6_DRIVERS-2f-EXTI:
	-$(RM) ./STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.cyclo ./STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.d ./STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.o ./STM32_F103C6_DRIVERS/EXTI/Stm32_F103C6_EXTI_driver.su

.PHONY: clean-STM32_F103C6_DRIVERS-2f-EXTI

