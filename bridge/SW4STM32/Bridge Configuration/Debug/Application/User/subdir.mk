################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/gpio.c \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/main.c \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/spi.c \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/stm32f4xx_hal_msp.c \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/stm32f4xx_it.c \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/tim.c \
G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/usart.c 

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
Application/User/gpio.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spi.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/spi.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/stm32f4xx_hal_msp.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/stm32f4xx_it.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/tim.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/tim.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usart.o: G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"G:/SVN_Christian/ETS/ELE400/Freestyle/git/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


