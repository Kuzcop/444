################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Components/cs42l51/cs42l51.c 

OBJS += \
./Core/Inc/Components/cs42l51/cs42l51.o 

C_DEPS += \
./Core/Inc/Components/cs42l51/cs42l51.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Components/cs42l51/%.o Core/Inc/Components/cs42l51/%.su Core/Inc/Components/cs42l51/%.cyclo: ../Core/Inc/Components/cs42l51/%.c Core/Inc/Components/cs42l51/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L4S5xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-Components-2f-cs42l51

clean-Core-2f-Inc-2f-Components-2f-cs42l51:
	-$(RM) ./Core/Inc/Components/cs42l51/cs42l51.cyclo ./Core/Inc/Components/cs42l51/cs42l51.d ./Core/Inc/Components/cs42l51/cs42l51.o ./Core/Inc/Components/cs42l51/cs42l51.su

.PHONY: clean-Core-2f-Inc-2f-Components-2f-cs42l51
