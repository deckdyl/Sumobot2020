################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/system_stm32g4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32g4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32g4xx.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/system_stm32g4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/system_stm32g4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

