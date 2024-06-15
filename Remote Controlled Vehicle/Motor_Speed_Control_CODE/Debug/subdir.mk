################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gpio.c \
../input.c \
../main.c \
../motor.c \
../pwm.c \
../sensor.c 

OBJS += \
./gpio.o \
./input.o \
./main.o \
./motor.o \
./pwm.o \
./sensor.o 

C_DEPS += \
./gpio.d \
./input.d \
./main.d \
./motor.d \
./pwm.d \
./sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


