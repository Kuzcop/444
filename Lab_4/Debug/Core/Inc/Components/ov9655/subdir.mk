################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Components/ov9655/ov9655.c 

OBJS += \
./Core/Inc/Components/ov9655/ov9655.o 

C_DEPS += \
./Core/Inc/Components/ov9655/ov9655.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Components/ov9655/%.o Core/Inc/Components/ov9655/%.su Core/Inc/Components/ov9655/%.cyclo: ../Core/Inc/Components/ov9655/%.c Core/Inc/Components/ov9655/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Components-2f-ov9655

clean-Core-2f-Inc-2f-Components-2f-ov9655:
	-$(RM) ./Core/Inc/Components/ov9655/ov9655.cyclo ./Core/Inc/Components/ov9655/ov9655.d ./Core/Inc/Components/ov9655/ov9655.o ./Core/Inc/Components/ov9655/ov9655.su

.PHONY: clean-Core-2f-Inc-2f-Components-2f-ov9655
