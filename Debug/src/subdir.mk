################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fv_i2c.c \
../src/led_matrix.c \
../src/main.c \
../src/mcp23017.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/test.c \
../src/timer.c \
../src/uart.c 

OBJS += \
./src/fv_i2c.o \
./src/led_matrix.o \
./src/main.o \
./src/mcp23017.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/test.o \
./src/timer.o \
./src/uart.o 

C_DEPS += \
./src/fv_i2c.d \
./src/led_matrix.d \
./src/main.d \
./src/mcp23017.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/test.d \
./src/timer.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/nucleo-f401re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f401re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f401re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f401re_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/work/workspace_stm/nucleo_i2c/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


