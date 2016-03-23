################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/gpio.c \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/main.c \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/spi.c \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/stm32f4xx_hal_msp.c \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/stm32f4xx_it.c \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/tim.c \
C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/usart.c 

OBJS += \
./Application/User/gpio.o \
./Application/User/main.o \
./Application/User/spi.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_it.o \
./Application/User/tim.o \
./Application/User/usart.o 

C_DEPS += \
./Application/User/gpio.d \
./Application/User/main.d \
./Application/User/spi.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_it.d \
./Application/User/tim.d \
./Application/User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/gpio.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spi.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/spi.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/stm32f4xx_hal_msp.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/stm32f4xx_it.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/tim.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/tim.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usart.o: C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


