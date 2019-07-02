################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Windows/img/accel.c \
../Src/Windows/img/backward.c \
../Src/Windows/img/bmKnob_150x150.c \
../Src/Windows/img/buzzer.c \
../Src/Windows/img/close.c \
../Src/Windows/img/files.c \
../Src/Windows/img/forward.c \
../Src/Windows/img/info.c \
../Src/Windows/img/led.c \
../Src/Windows/img/light.c \
../Src/Windows/img/mikroe.c \
../Src/Windows/img/mp3.c \
../Src/Windows/img/music.c \
../Src/Windows/img/pause.c \
../Src/Windows/img/play.c \
../Src/Windows/img/slideshow.c \
../Src/Windows/img/stm32.c \
../Src/Windows/img/stop.c \
../Src/Windows/img/temp.c \
../Src/Windows/img/time.c \
../Src/Windows/img/touch.c \
../Src/Windows/img/usb.c \
../Src/Windows/img/wallpaper.c 

OBJS += \
./Src/Windows/img/accel.o \
./Src/Windows/img/backward.o \
./Src/Windows/img/bmKnob_150x150.o \
./Src/Windows/img/buzzer.o \
./Src/Windows/img/close.o \
./Src/Windows/img/files.o \
./Src/Windows/img/forward.o \
./Src/Windows/img/info.o \
./Src/Windows/img/led.o \
./Src/Windows/img/light.o \
./Src/Windows/img/mikroe.o \
./Src/Windows/img/mp3.o \
./Src/Windows/img/music.o \
./Src/Windows/img/pause.o \
./Src/Windows/img/play.o \
./Src/Windows/img/slideshow.o \
./Src/Windows/img/stm32.o \
./Src/Windows/img/stop.o \
./Src/Windows/img/temp.o \
./Src/Windows/img/time.o \
./Src/Windows/img/touch.o \
./Src/Windows/img/usb.o \
./Src/Windows/img/wallpaper.o 

C_DEPS += \
./Src/Windows/img/accel.d \
./Src/Windows/img/backward.d \
./Src/Windows/img/bmKnob_150x150.d \
./Src/Windows/img/buzzer.d \
./Src/Windows/img/close.d \
./Src/Windows/img/files.d \
./Src/Windows/img/forward.d \
./Src/Windows/img/info.d \
./Src/Windows/img/led.d \
./Src/Windows/img/light.d \
./Src/Windows/img/mikroe.d \
./Src/Windows/img/mp3.d \
./Src/Windows/img/music.d \
./Src/Windows/img/pause.d \
./Src/Windows/img/play.d \
./Src/Windows/img/slideshow.d \
./Src/Windows/img/stm32.d \
./Src/Windows/img/stop.d \
./Src/Windows/img/temp.d \
./Src/Windows/img/time.d \
./Src/Windows/img/touch.d \
./Src/Windows/img/usb.d \
./Src/Windows/img/wallpaper.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Windows/img/%.o: ../Src/Windows/img/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/CMSIS/Include" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/STemWinLib/inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/Third_Party/FatFs/src" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Software" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Hardware" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Windows" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


