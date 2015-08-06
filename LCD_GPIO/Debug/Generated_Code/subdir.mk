################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/LCD_CS.c \
../Generated_Code/LCD_LED.c \
../Generated_Code/LCD_RS.c \
../Generated_Code/LCD_RST.c \
../Generated_Code/LCD_SCL.c \
../Generated_Code/LCD_SDA.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Pins1.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/LCD_CS.o \
./Generated_Code/LCD_LED.o \
./Generated_Code/LCD_RS.o \
./Generated_Code/LCD_RST.o \
./Generated_Code/LCD_SCL.o \
./Generated_Code/LCD_SDA.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Pins1.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/LCD_CS.d \
./Generated_Code/LCD_LED.d \
./Generated_Code/LCD_RS.d \
./Generated_Code/LCD_RST.d \
./Generated_Code/LCD_SCL.d \
./Generated_Code/LCD_SDA.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Pins1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/peripherals" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/system" -I"C:/Users/lguillain/workspace/LCD_GPIO/Sources" -I"C:/Users/lguillain/workspace/LCD_GPIO/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


