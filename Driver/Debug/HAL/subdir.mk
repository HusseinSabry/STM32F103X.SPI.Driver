################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/keypad.c \
../HAL/lcd.c 

OBJS += \
./HAL/keypad.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/keypad.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/keypad.o: ../HAL/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/10/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_f103_c6_Drivers/Include" -I"C:/Users/10/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/10/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_f103_c6_Drivers/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/lcd.o: ../HAL/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/10/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_f103_c6_Drivers/Include" -I"C:/Users/10/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/10/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_f103_c6_Drivers/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

