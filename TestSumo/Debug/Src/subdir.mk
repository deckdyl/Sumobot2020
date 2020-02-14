################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SRF02.c \
../Src/WS2812.c \
../Src/adc.c \
../Src/dma.c \
../Src/fdcan.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/runtime.c \
../Src/stm32g4xx_hal_msp.c \
../Src/stm32g4xx_it.c \
../Src/sys.c \
../Src/syscalls.c \
../Src/system_stm32g4xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/SRF02.o \
./Src/WS2812.o \
./Src/adc.o \
./Src/dma.o \
./Src/fdcan.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/runtime.o \
./Src/stm32g4xx_hal_msp.o \
./Src/stm32g4xx_it.o \
./Src/sys.o \
./Src/syscalls.o \
./Src/system_stm32g4xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/SRF02.d \
./Src/WS2812.d \
./Src/adc.d \
./Src/dma.d \
./Src/fdcan.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/runtime.d \
./Src/stm32g4xx_hal_msp.d \
./Src/stm32g4xx_it.d \
./Src/sys.d \
./Src/syscalls.d \
./Src/system_stm32g4xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32G474xx -I"D:/Dylan/STM32/TestSumo/Inc" -I"D:/Dylan/STM32/TestSumo/Drivers/STM32G4xx_HAL_Driver/Inc" -I"D:/Dylan/STM32/TestSumo/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"D:/Dylan/STM32/TestSumo/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/Dylan/STM32/TestSumo/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


