################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/SSD1351.cpp \
../Sources/main.cpp 

C_SRCS += \
../Sources/Events.c \
../Sources/spi_next.c 

OBJS += \
./Sources/Events.o \
./Sources/SSD1351.o \
./Sources/main.o \
./Sources/spi_next.o 

C_DEPS += \
./Sources/Events.d \
./Sources/spi_next.d 

CPP_DEPS += \
./Sources/SSD1351.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Users\lguillain\workspace.kds\FRFXLL\include" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lguillain/workspace.kds/SESAMETOUCH_FINALv2/Sources" -I"C:/Users/lguillain/workspace.kds/SESAMETOUCH_FINALv2/Generated_Code" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:\Users\lguillain\workspace.kds\FRFXLL\include" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/iofiles" -I"C:/Users/lguillain/workspace.kds/SESAMETOUCH_FINALv2/Sources" -I"C:/Users/lguillain/workspace.kds/SESAMETOUCH_FINALv2/Generated_Code" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -std=gnu++11 -fabi-version=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


