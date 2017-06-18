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
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F0 -DNUCLEO_F042K6 -DSTM32F042K6Tx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -I"C:/Users/andre/Documents/trixlog/canreader/inc" -I"C:/Users/andre/Documents/trixlog/canreader/CMSIS/core" -I"C:/Users/andre/Documents/trixlog/canreader/CMSIS/device" -I"C:/Users/andre/Documents/trixlog/canreader/HAL_Driver/Inc/Legacy" -I"C:/Users/andre/Documents/trixlog/canreader/HAL_Driver/Inc" -I"C:/Users/andre/Documents/trixlog/canreader/Utilities/STM32F0xx_Nucleo_32" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


