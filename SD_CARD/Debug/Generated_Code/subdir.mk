################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/CD1.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/FAT1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c \
../Generated_Code/SD1.c \
../Generated_Code/SM1.c \
../Generated_Code/SS1.c \
../Generated_Code/TI1.c \
../Generated_Code/TMOUT1.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerIntLdd1.c \
../Generated_Code/TmDt1.c \
../Generated_Code/UTIL1.c \
../Generated_Code/WAIT1.c \
../Generated_Code/ff.c 

OBJS += \
./Generated_Code/CD1.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/FAT1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o \
./Generated_Code/SD1.o \
./Generated_Code/SM1.o \
./Generated_Code/SS1.o \
./Generated_Code/TI1.o \
./Generated_Code/TMOUT1.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerIntLdd1.o \
./Generated_Code/TmDt1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/WAIT1.o \
./Generated_Code/ff.o 

C_DEPS += \
./Generated_Code/CD1.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/FAT1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d \
./Generated_Code/SD1.d \
./Generated_Code/SM1.d \
./Generated_Code/SS1.d \
./Generated_Code/TI1.d \
./Generated_Code/TMOUT1.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerIntLdd1.d \
./Generated_Code/TmDt1.d \
./Generated_Code/UTIL1.d \
./Generated_Code/WAIT1.d \
./Generated_Code/ff.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/peripherals" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/system" -I"C:/Users/lguillain/workspace/SD_CARD/Sources" -I"C:/Users/lguillain/workspace/SD_CARD/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


