################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/RFModSTM32f4x.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/RFModSTM32f4x.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/RFModSTM32f4x.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Gabriel/Documents/STM32_projetos/exemplo_RFModSTM32f4x_transmissor/Core/Inc" -I"C:/Users/Gabriel/Documents/STM32_projetos/exemplo_RFModSTM32f4x_transmissor/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Gabriel/Documents/STM32_projetos/exemplo_RFModSTM32f4x_transmissor/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Gabriel/Documents/STM32_projetos/exemplo_RFModSTM32f4x_transmissor/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Gabriel/Documents/STM32_projetos/exemplo_RFModSTM32f4x_transmissor/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


