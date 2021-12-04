################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/rcc.c 

OBJS += \
./Peripherals/Src/rcc.o 

C_DEPS += \
./Peripherals/Src/rcc.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/%.o: ../Peripherals/Src/%.c Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"F:/__WORKSPACES/STM32CubeIDE/Udemy_STM32/02_SysTick/Core/Inc" -I"F:/__WORKSPACES/STM32CubeIDE/Udemy_STM32/02_SysTick/CMSIS/Include" -I"F:/__WORKSPACES/STM32CubeIDE/Udemy_STM32/02_SysTick/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Peripherals-2f-Src

clean-Peripherals-2f-Src:
	-$(RM) ./Peripherals/Src/rcc.d ./Peripherals/Src/rcc.o

.PHONY: clean-Peripherals-2f-Src

