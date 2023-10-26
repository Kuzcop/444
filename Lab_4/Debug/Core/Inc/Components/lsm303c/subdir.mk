################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Components/lsm303c/lsm303c.c 

OBJS += \
./Core/Inc/Components/lsm303c/lsm303c.o 

C_DEPS += \
./Core/Inc/Components/lsm303c/lsm303c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Components/lsm303c/%.o Core/Inc/Components/lsm303c/%.su Core/Inc/Components/lsm303c/%.cyclo: ../Core/Inc/Components/lsm303c/%.c Core/Inc/Components/lsm303c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Components-2f-lsm303c

clean-Core-2f-Inc-2f-Components-2f-lsm303c:
	-$(RM) ./Core/Inc/Components/lsm303c/lsm303c.cyclo ./Core/Inc/Components/lsm303c/lsm303c.d ./Core/Inc/Components/lsm303c/lsm303c.o ./Core/Inc/Components/lsm303c/lsm303c.su

.PHONY: clean-Core-2f-Inc-2f-Components-2f-lsm303c

