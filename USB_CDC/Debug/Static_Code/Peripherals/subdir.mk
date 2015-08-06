################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Static_Code/Peripherals/USB0_Init.c 

OBJS += \
./Static_Code/Peripherals/USB0_Init.o 

C_DEPS += \
./Static_Code/Peripherals/USB0_Init.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/Peripherals/%.o: ../Static_Code/Peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/lguillain/workspace.kds/USB_CDC/Static_Code/System" -I"C:/Users/lguillain/workspace.kds/USB_CDC/Static_Code/PDD" -I"C:/Users/lguillain/workspace.kds/USB_CDC/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/lguillain/workspace.kds/USB_CDC/Sources" -I"C:/Users/lguillain/workspace.kds/USB_CDC/Generated_Code" -I"C:/Users/lguillain/workspace.kds/USB_CDC/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


