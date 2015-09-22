################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/EInt1.c \
../Generated_Code/ExtIntLdd1.c \
../Generated_Code/NEXT_RESET.c \
../Generated_Code/NEXT_SPI.c \
../Generated_Code/OLED_DC.c \
../Generated_Code/OLED_RESET.c \
../Generated_Code/OLED_SUPPLY.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SM1.c \
../Generated_Code/SM3.c \
../Generated_Code/SMasterLdd1.c \
../Generated_Code/SMasterLdd3.c \
../Generated_Code/SS.c \
../Generated_Code/TI1.c \
../Generated_Code/TU1.c \
../Generated_Code/WAIT1.c 

OBJS += \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/EInt1.o \
./Generated_Code/ExtIntLdd1.o \
./Generated_Code/NEXT_RESET.o \
./Generated_Code/NEXT_SPI.o \
./Generated_Code/OLED_DC.o \
./Generated_Code/OLED_RESET.o \
./Generated_Code/OLED_SUPPLY.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SM1.o \
./Generated_Code/SM3.o \
./Generated_Code/SMasterLdd1.o \
./Generated_Code/SMasterLdd3.o \
./Generated_Code/SS.o \
./Generated_Code/TI1.o \
./Generated_Code/TU1.o \
./Generated_Code/WAIT1.o 

C_DEPS += \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/EInt1.d \
./Generated_Code/ExtIntLdd1.d \
./Generated_Code/NEXT_RESET.d \
./Generated_Code/NEXT_SPI.d \
./Generated_Code/OLED_DC.d \
./Generated_Code/OLED_RESET.d \
./Generated_Code/OLED_SUPPLY.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SM1.d \
./Generated_Code/SM3.d \
./Generated_Code/SMasterLdd1.d \
./Generated_Code/SMasterLdd3.d \
./Generated_Code/SS.d \
./Generated_Code/TI1.d \
./Generated_Code/TU1.d \
./Generated_Code/WAIT1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Users\lguillain\workspace.kds\FRFXLL\include" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lguillain/workspace.kds/SESAMETOUCH_FINALv2/Sources" -I"C:/Users/lguillain/workspace.kds/SESAMETOUCH_FINALv2/Generated_Code" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


