################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f042x6.s 

OBJS += \
./startup/startup_stm32f042x6.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -I"C:/Users/andre/Documents/trixlog/canreader/inc" -I"C:/Users/andre/Documents/trixlog/canreader/CMSIS/core" -I"C:/Users/andre/Documents/trixlog/canreader/CMSIS/device" -I"C:/Users/andre/Documents/trixlog/canreader/HAL_Driver/Inc/Legacy" -I"C:/Users/andre/Documents/trixlog/canreader/HAL_Driver/Inc" -I"C:/Users/andre/Documents/trixlog/canreader/Utilities/STM32F0xx_Nucleo_32" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


