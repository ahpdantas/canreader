################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F0xx_Nucleo_32/stm32f0xx_nucleo_32.c 

OBJS += \
./Utilities/STM32F0xx_Nucleo_32/stm32f0xx_nucleo_32.o 

C_DEPS += \
./Utilities/STM32F0xx_Nucleo_32/stm32f0xx_nucleo_32.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F0xx_Nucleo_32/%.o: ../Utilities/STM32F0xx_Nucleo_32/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -std=c11 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F042x6 -I"C:/Users/andre/Documents/trixlog/canreader/Inc" -I"C:/Users/andre/Documents/trixlog/canreader/Utilities/STM32F0xx_Nucleo_32" -I"C:/Users/andre/Documents/trixlog/canreader/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/andre/Documents/trixlog/canreader/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/andre/Documents/trixlog/canreader/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"C:/Users/andre/Documents/trixlog/canreader/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


