################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.c 

OBJS += \
./STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.o 

C_DEPS += \
./STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_F103C6_DRIVERS/GPIO/%.o STM32_F103C6_DRIVERS/GPIO/%.su STM32_F103C6_DRIVERS/GPIO/%.cyclo: ../STM32_F103C6_DRIVERS/GPIO/%.c STM32_F103C6_DRIVERS/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"C:/Users/aliab/OneDrive/Desktop/lesson 5/STM32_F103C6_DRIVERS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32_F103C6_DRIVERS-2f-GPIO

clean-STM32_F103C6_DRIVERS-2f-GPIO:
	-$(RM) ./STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.cyclo ./STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.d ./STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.o ./STM32_F103C6_DRIVERS/GPIO/stm32_f103c6_gpio_drivers.su

.PHONY: clean-STM32_F103C6_DRIVERS-2f-GPIO

