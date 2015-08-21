################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/OLED_DC.c \
../Generated_Code/OLED_RESET.c \
../Generated_Code/OLED_SUPPLY.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/SM1.c \
../Generated_Code/SMasterLdd1.c \
../Generated_Code/WAIT1.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/OLED_DC.o \
./Generated_Code/OLED_RESET.o \
./Generated_Code/OLED_SUPPLY.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/SM1.o \
./Generated_Code/SMasterLdd1.o \
./Generated_Code/WAIT1.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/OLED_DC.d \
./Generated_Code/OLED_RESET.d \
./Generated_Code/OLED_SUPPLY.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/SM1.d \
./Generated_Code/SMasterLdd1.d \
./Generated_Code/WAIT1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/lguillain/workspace/OLED_SSD1351/Sources" -I"C:/Users/lguillain/workspace/OLED_SSD1351/Generated_Code" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


