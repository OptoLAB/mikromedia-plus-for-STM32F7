################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Windows/ACCELDLG.c \
../Src/Windows/BUZZERDLG.c \
../Src/Windows/FILESDLG.c \
../Src/Windows/INFODLG.c \
../Src/Windows/LEDDLG.c \
../Src/Windows/LIGHTDLG.c \
../Src/Windows/MENUDLG.c \
../Src/Windows/MP3DLG.c \
../Src/Windows/QWERTYDLG.c \
../Src/Windows/SETDATEDLG.c \
../Src/Windows/SETTIMEDLG.c \
../Src/Windows/TEMPDLG.c \
../Src/Windows/TIMEDLG.c \
../Src/Windows/USBDLG.c 

OBJS += \
./Src/Windows/ACCELDLG.o \
./Src/Windows/BUZZERDLG.o \
./Src/Windows/FILESDLG.o \
./Src/Windows/INFODLG.o \
./Src/Windows/LEDDLG.o \
./Src/Windows/LIGHTDLG.o \
./Src/Windows/MENUDLG.o \
./Src/Windows/MP3DLG.o \
./Src/Windows/QWERTYDLG.o \
./Src/Windows/SETDATEDLG.o \
./Src/Windows/SETTIMEDLG.o \
./Src/Windows/TEMPDLG.o \
./Src/Windows/TIMEDLG.o \
./Src/Windows/USBDLG.o 

C_DEPS += \
./Src/Windows/ACCELDLG.d \
./Src/Windows/BUZZERDLG.d \
./Src/Windows/FILESDLG.d \
./Src/Windows/INFODLG.d \
./Src/Windows/LEDDLG.d \
./Src/Windows/LIGHTDLG.d \
./Src/Windows/MENUDLG.d \
./Src/Windows/MP3DLG.d \
./Src/Windows/QWERTYDLG.d \
./Src/Windows/SETDATEDLG.d \
./Src/Windows/SETTIMEDLG.d \
./Src/Windows/TEMPDLG.d \
./Src/Windows/TIMEDLG.d \
./Src/Windows/USBDLG.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Windows/%.o: ../Src/Windows/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F746xx -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Drivers/CMSIS/Include" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/STemWinLib/inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/Third_Party/FatFs/src" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Software" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Hardware" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Inc/Windows" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Jovan/Desktop/MP3/MP3 - STemWin/Display STemWin/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


