################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FatFs/src/diskio.c \
../Middlewares/Third_Party/FatFs/src/ff.c \
../Middlewares/Third_Party/FatFs/src/ff_gen_drv.c 

OBJS += \
./Middlewares/Third_Party/FatFs/src/diskio.o \
./Middlewares/Third_Party/FatFs/src/ff.o \
./Middlewares/Third_Party/FatFs/src/ff_gen_drv.o 

C_DEPS += \
./Middlewares/Third_Party/FatFs/src/diskio.d \
./Middlewares/Third_Party/FatFs/src/ff.d \
./Middlewares/Third_Party/FatFs/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FatFs/src/%.o: ../Middlewares/Third_Party/FatFs/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/CMSIS/Include" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/STemWinLib/inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/Third_Party/FatFs/src" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Software" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Hardware" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Windows" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


