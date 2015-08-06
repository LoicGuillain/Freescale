################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/ILI9163C.c \
../Sources/font5x8.c \
../Sources/image1.c \
../Sources/main.c 

OBJS += \
./Sources/Events.o \
./Sources/ILI9163C.o \
./Sources/font5x8.o \
./Sources/image1.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/ILI9163C.d \
./Sources/font5x8.d \
./Sources/image1.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/peripherals" -I"C:\Users\lguillain\Downloads\eclipse-cpp-kepler-SR2-win32-x86_64\eclipse\ProcessorExpert/lib/Kinetis/pdd2/MK64FN1M0LQ12/system" -I"C:/Users/lguillain/workspace/LCD_GPIO/Sources" -I"C:/Users/lguillain/workspace/LCD_GPIO/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


