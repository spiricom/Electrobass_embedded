################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-analysis.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-delay.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-distortion.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-dynamics.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-effects.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-electrical.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-envelopes.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-filters.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-instruments.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-math.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-mempool.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-midi.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-oscillators.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-physical.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-reverb.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-sampling.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-tables.c \
/Users/jeffsnyder/dev/LEAF/leaf/Src/leaf.c 

OBJS += \
./leaf/Src/leaf-analysis.o \
./leaf/Src/leaf-delay.o \
./leaf/Src/leaf-distortion.o \
./leaf/Src/leaf-dynamics.o \
./leaf/Src/leaf-effects.o \
./leaf/Src/leaf-electrical.o \
./leaf/Src/leaf-envelopes.o \
./leaf/Src/leaf-filters.o \
./leaf/Src/leaf-instruments.o \
./leaf/Src/leaf-math.o \
./leaf/Src/leaf-mempool.o \
./leaf/Src/leaf-midi.o \
./leaf/Src/leaf-oscillators.o \
./leaf/Src/leaf-physical.o \
./leaf/Src/leaf-reverb.o \
./leaf/Src/leaf-sampling.o \
./leaf/Src/leaf-tables.o \
./leaf/Src/leaf.o 

C_DEPS += \
./leaf/Src/leaf-analysis.d \
./leaf/Src/leaf-delay.d \
./leaf/Src/leaf-distortion.d \
./leaf/Src/leaf-dynamics.d \
./leaf/Src/leaf-effects.d \
./leaf/Src/leaf-electrical.d \
./leaf/Src/leaf-envelopes.d \
./leaf/Src/leaf-filters.d \
./leaf/Src/leaf-instruments.d \
./leaf/Src/leaf-math.d \
./leaf/Src/leaf-mempool.d \
./leaf/Src/leaf-midi.d \
./leaf/Src/leaf-oscillators.d \
./leaf/Src/leaf-physical.d \
./leaf/Src/leaf-reverb.d \
./leaf/Src/leaf-sampling.d \
./leaf/Src/leaf-tables.d \
./leaf/Src/leaf.d 


# Each subdirectory must supply rules for building sources it contributes
leaf/Src/leaf-analysis.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-analysis.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-delay.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-delay.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-distortion.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-distortion.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-dynamics.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-dynamics.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-effects.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-effects.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-electrical.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-electrical.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-envelopes.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-envelopes.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-filters.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-filters.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-instruments.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-instruments.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-math.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-math.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-mempool.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-mempool.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-midi.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-midi.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-oscillators.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-oscillators.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-physical.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-physical.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-reverb.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-reverb.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-sampling.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-sampling.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf-tables.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf-tables.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
leaf/Src/leaf.o: /Users/jeffsnyder/dev/LEAF/leaf/Src/leaf.c leaf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-leaf-2f-Src

clean-leaf-2f-Src:
	-$(RM) ./leaf/Src/leaf-analysis.d ./leaf/Src/leaf-analysis.o ./leaf/Src/leaf-analysis.su ./leaf/Src/leaf-delay.d ./leaf/Src/leaf-delay.o ./leaf/Src/leaf-delay.su ./leaf/Src/leaf-distortion.d ./leaf/Src/leaf-distortion.o ./leaf/Src/leaf-distortion.su ./leaf/Src/leaf-dynamics.d ./leaf/Src/leaf-dynamics.o ./leaf/Src/leaf-dynamics.su ./leaf/Src/leaf-effects.d ./leaf/Src/leaf-effects.o ./leaf/Src/leaf-effects.su ./leaf/Src/leaf-electrical.d ./leaf/Src/leaf-electrical.o ./leaf/Src/leaf-electrical.su ./leaf/Src/leaf-envelopes.d ./leaf/Src/leaf-envelopes.o ./leaf/Src/leaf-envelopes.su ./leaf/Src/leaf-filters.d ./leaf/Src/leaf-filters.o ./leaf/Src/leaf-filters.su ./leaf/Src/leaf-instruments.d ./leaf/Src/leaf-instruments.o ./leaf/Src/leaf-instruments.su ./leaf/Src/leaf-math.d ./leaf/Src/leaf-math.o ./leaf/Src/leaf-math.su ./leaf/Src/leaf-mempool.d ./leaf/Src/leaf-mempool.o ./leaf/Src/leaf-mempool.su ./leaf/Src/leaf-midi.d ./leaf/Src/leaf-midi.o ./leaf/Src/leaf-midi.su ./leaf/Src/leaf-oscillators.d ./leaf/Src/leaf-oscillators.o ./leaf/Src/leaf-oscillators.su ./leaf/Src/leaf-physical.d ./leaf/Src/leaf-physical.o ./leaf/Src/leaf-physical.su ./leaf/Src/leaf-reverb.d ./leaf/Src/leaf-reverb.o ./leaf/Src/leaf-reverb.su ./leaf/Src/leaf-sampling.d ./leaf/Src/leaf-sampling.o ./leaf/Src/leaf-sampling.su ./leaf/Src/leaf-tables.d ./leaf/Src/leaf-tables.o ./leaf/Src/leaf-tables.su ./leaf/Src/leaf.d ./leaf/Src/leaf.o ./leaf/Src/leaf.su

.PHONY: clean-leaf-2f-Src

