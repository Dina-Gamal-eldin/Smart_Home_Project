################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_Prog.c \
../DIO_Project.c \
../EEPROM_program.c \
../Global_Interrupt_program.c \
../KPD_Prog.c \
../LCD_proj.c \
../MTWI_program.c \
../TIM1.c \
../UART_program.c \
../main.c 

OBJS += \
./ADC_Prog.o \
./DIO_Project.o \
./EEPROM_program.o \
./Global_Interrupt_program.o \
./KPD_Prog.o \
./LCD_proj.o \
./MTWI_program.o \
./TIM1.o \
./UART_program.o \
./main.o 

C_DEPS += \
./ADC_Prog.d \
./DIO_Project.d \
./EEPROM_program.d \
./Global_Interrupt_program.d \
./KPD_Prog.d \
./LCD_proj.d \
./MTWI_program.d \
./TIM1.d \
./UART_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


