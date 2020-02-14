################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/customESC.c \
../Application/User/customMC.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/dac_ui.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/main.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_api.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_config.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_interface.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_math.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_parameters.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_tasks.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/motor_control_protocol.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/motorcontrol.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/regular_conversion_manager.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/stm32g4xx_hal_msp.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/stm32g4xx_it.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/stm32g4xx_mc_it.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/ui_task.c \
C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/user_interface.c 

OBJS += \
./Application/User/customESC.o \
./Application/User/customMC.o \
./Application/User/dac_ui.o \
./Application/User/main.o \
./Application/User/mc_api.o \
./Application/User/mc_config.o \
./Application/User/mc_interface.o \
./Application/User/mc_math.o \
./Application/User/mc_parameters.o \
./Application/User/mc_tasks.o \
./Application/User/motor_control_protocol.o \
./Application/User/motorcontrol.o \
./Application/User/regular_conversion_manager.o \
./Application/User/stm32g4xx_hal_msp.o \
./Application/User/stm32g4xx_it.o \
./Application/User/stm32g4xx_mc_it.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o \
./Application/User/ui_task.o \
./Application/User/user_interface.o 

C_DEPS += \
./Application/User/customESC.d \
./Application/User/customMC.d \
./Application/User/dac_ui.d \
./Application/User/main.d \
./Application/User/mc_api.d \
./Application/User/mc_config.d \
./Application/User/mc_interface.d \
./Application/User/mc_math.d \
./Application/User/mc_parameters.d \
./Application/User/mc_tasks.d \
./Application/User/motor_control_protocol.d \
./Application/User/motorcontrol.d \
./Application/User/regular_conversion_manager.d \
./Application/User/stm32g4xx_hal_msp.d \
./Application/User/stm32g4xx_it.d \
./Application/User/stm32g4xx_mc_it.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d \
./Application/User/ui_task.d \
./Application/User/user_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/customESC.o: ../Application/User/customESC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/customESC.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/customMC.o: ../Application/User/customMC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/customMC.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/dac_ui.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/dac_ui.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/dac_ui.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/main.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/mc_api.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_api.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/mc_api.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/mc_config.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/mc_config.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/mc_interface.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_interface.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/mc_interface.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/mc_math.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_math.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/mc_math.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/mc_parameters.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_parameters.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/mc_parameters.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/mc_tasks.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/mc_tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/mc_tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/motor_control_protocol.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/motor_control_protocol.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/motor_control_protocol.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/motorcontrol.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/motorcontrol.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/motorcontrol.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/regular_conversion_manager.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/regular_conversion_manager.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/regular_conversion_manager.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32g4xx_hal_msp.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/stm32g4xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32g4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32g4xx_it.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/stm32g4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32g4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32g4xx_mc_it.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/stm32g4xx_mc_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32g4xx_mc_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/syscalls.o: ../Application/User/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/sysmem.o: ../Application/User/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/ui_task.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/ui_task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/ui_task.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/user_interface.o: C:/Users/mining.110.1/Desktop/ESC/DylanDrive/Src/user_interface.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32G431xx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -c -I../../Drivers/CMSIS/Include -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/G4xx/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/MCLib/Any/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/UILibrary/Inc -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I../../MCSDK_v5.4.3/MotorControl/MCSDK/SystemDriveParams -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/user_interface.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

