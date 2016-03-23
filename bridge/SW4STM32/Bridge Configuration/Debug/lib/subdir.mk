################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/NRF24L01.c 

OBJS += \
./lib/NRF24L01.o 

C_DEPS += \
./lib/NRF24L01.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Jean-Francois/workspace/freestyle_ele400/bridge/SW4STM32/Bridge Configuration/lib"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


