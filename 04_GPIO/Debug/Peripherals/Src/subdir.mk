################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/gpio.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/uart.c 

OBJS += \
./Peripherals/Src/gpio.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/uart.o 

C_DEPS += \
./Peripherals/Src/gpio.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/%.o: ../Peripherals/Src/%.c Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103xB -c -I"/home/dananjaya/Projects/udemy-stm32-getting-started-level-1/04_GPIO/Core/Inc" -I"/home/dananjaya/Projects/udemy-stm32-getting-started-level-1/04_GPIO/CMSIS/Include" -I"/home/dananjaya/Projects/udemy-stm32-getting-started-level-1/04_GPIO/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Peripherals-2f-Src

clean-Peripherals-2f-Src:
	-$(RM) ./Peripherals/Src/gpio.d ./Peripherals/Src/gpio.o ./Peripherals/Src/rcc.d ./Peripherals/Src/rcc.o ./Peripherals/Src/uart.d ./Peripherals/Src/uart.o

.PHONY: clean-Peripherals-2f-Src

