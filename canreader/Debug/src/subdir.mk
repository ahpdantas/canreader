################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f0xx_hal_msp.c \
../src/stm32f0xx_it.c \
../src/syscalls.c \
../src/system_stm32f0xx.c 

OBJS += \
./src/main.o \
./src/stm32f0xx_hal_msp.o \
./src/stm32f0xx_it.o \
./src/syscalls.o \
./src/system_stm32f0xx.o 

C_DEPS += \
./src/main.d \
./src/stm32f0xx_hal_msp.d \
./src/stm32f0xx_it.d \
./src/syscalls.d \
./src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F0 -DNUCLEO_F042K6 -DSTM32F042K6Tx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -I"C:/Users/andre/Documents/trixlog/canreader/inc" -I"C:/Users/andre/Documents/trixlog/canreader/CMSIS/core" -I"C:/Users/andre/Documents/trixlog/canreader/CMSIS/device" -I"C:/Users/andre/Documents/trixlog/canreader/HAL_Driver/Inc/Legacy" -I"C:/Users/andre/Documents/trixlog/canreader/HAL_Driver/Inc" -I"C:/Users/andre/Documents/trixlog/canreader/Utilities/STM32F0xx_Nucleo_32" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


