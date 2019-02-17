# MPLAB IDE generated this makefile for use with GNU make.
# Project: RoqDryPlus.mcp
# Date: Wed Jul 27 17:56:32 2016

AS = pic32-as.exe
CC = pic32-gcc.exe
LD = pic32-ld.exe
AR = pic32-ar.exe
HX = pic32-bin2hex.exe
RM = rm

Output/RoqDryPlus.hex : Output/RoqDryPlus.elf
	$(HX) "Output\RoqDryPlus.elf"

Output/RoqDryPlus.elf : Intermediary/adc.o Intermediary/buzzer.o Intermediary/can.o Intermediary/fram.o Intermediary/glcd.o Intermediary/i2c.o Intermediary/io.o Intermediary/main.o Intermediary/matrixKeyboard.o Intermediary/pwm.o Intermediary/rtc.o Intermediary/spi.o Intermediary/thermocouple.o Intermediary/uart.o Intermediary/usb_descriptors.o Intermediary/FSIO.o Intermediary/SD-SPI.o Intermediary/usb_device.o Intermediary/usb_function_msd.o
	$(CC) -mprocessor=32MX795F512L "Intermediary\adc.o" "Intermediary\buzzer.o" "Intermediary\can.o" "Intermediary\fram.o" "Intermediary\glcd.o" "Intermediary\i2c.o" "Intermediary\io.o" "Intermediary\main.o" "Intermediary\matrixKeyboard.o" "Intermediary\pwm.o" "Intermediary\rtc.o" "Intermediary\spi.o" "Intermediary\thermocouple.o" "Intermediary\uart.o" "Intermediary\usb_descriptors.o" "Intermediary\FSIO.o" "Intermediary\SD-SPI.o" "Intermediary\usb_device.o" "Intermediary\usb_function_msd.o" -o"Output\RoqDryPlus.elf" -Wl,-L"C:\Program Files (x86)\Microchip\MPLAB C32 Suite\lib",-L"C:\Program Files (x86)\Microchip\MPLAB C32 Suite\pic32mx\lib",--script="app_32MX795F512L.ld",--defsym=__MPLAB_BUILD=1,-Map="Output\RoqDryPlus.map"

Intermediary/adc.o : adc.c adc.h hardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h
	$(CC) -mprocessor=32MX795F512L -x c -c "adc.c" -o"Intermediary\adc.o" -MMD -MF"Intermediary\adc.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/buzzer.o : buzzer.c buzzer.h ../Microchip/Include/Compiler.h hardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h
	$(CC) -mprocessor=32MX795F512L -x c -c "buzzer.c" -o"Intermediary\buzzer.o" -MMD -MF"Intermediary\buzzer.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/can.o : can.c can.h ../Microchip/Include/GenericTypeDefs.h
	$(CC) -mprocessor=32MX795F512L -x c -c "can.c" -o"Intermediary\can.o" -MMD -MF"Intermediary\can.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/fram.o : fram.c fram.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h
	$(CC) -mprocessor=32MX795F512L -x c -c "fram.c" -o"Intermediary\fram.o" -MMD -MF"Intermediary\fram.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/glcd.o : glcd.c ../Microchip/Include/Compiler.h glcd.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h LCD_FONTS.h
	$(CC) -mprocessor=32MX795F512L -x c -c "glcd.c" -o"Intermediary\glcd.o" -MMD -MF"Intermediary\glcd.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/i2c.o : i2c.c i2c.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h
	$(CC) -mprocessor=32MX795F512L -x c -c "i2c.c" -o"Intermediary\i2c.o" -MMD -MF"Intermediary\i2c.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/io.o : io.c HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h io.h
	$(CC) -mprocessor=32MX795F512L -x c -c "io.c" -o"Intermediary\io.o" -MMD -MF"Intermediary\io.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/main.o : main.c ../Microchip/Include/USB/usb.h ../Microchip/Include/GenericTypeDefs.h ../Microchip/Include/Compiler.h usb_config.h ../Microchip/Include/USB/usb_common.h ../Microchip/Include/USB/usb_ch9.h ../Microchip/Include/USB/usb_device.h ../Microchip/Include/USB/usb_hal.h ../Microchip/Include/USB/usb_hal_pic32.h ../Microchip/Include/USB/usb_function_msd.h ../Microchip/Include/MDD\ File\ System/FSDefs.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h ../Microchip/Include/MDD\ File\ System/FSIO.h FSconfig.h HardwareProfile.h ../Microchip/Include/MDD\ File\ System/SD-SPI.h adc.h buzzer.h io.h uart.h rtc.h matrixKeyboard.h spi.h fram.h thermocouple.h pwm.h glcd.h LCD_DATA.h can.h
	$(CC) -mprocessor=32MX795F512L -x c -c "main.c" -o"Intermediary\main.o" -MMD -MF"Intermediary\main.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/matrixKeyboard.o : matrixKeyboard.c matrixKeyboard.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h ../Microchip/Include/Compiler.h
	$(CC) -mprocessor=32MX795F512L -x c -c "matrixKeyboard.c" -o"Intermediary\matrixKeyboard.o" -MMD -MF"Intermediary\matrixKeyboard.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/pwm.o : pwm.c HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h pwm.h
	$(CC) -mprocessor=32MX795F512L -x c -c "pwm.c" -o"Intermediary\pwm.o" -MMD -MF"Intermediary\pwm.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/rtc.o : rtc.c HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h rtc.h uart.h
	$(CC) -mprocessor=32MX795F512L -x c -c "rtc.c" -o"Intermediary\rtc.o" -MMD -MF"Intermediary\rtc.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/spi.o : spi.c spi.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h
	$(CC) -mprocessor=32MX795F512L -x c -c "spi.c" -o"Intermediary\spi.o" -MMD -MF"Intermediary\spi.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/thermocouple.o : thermocouple.c HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h spi.h thermocouple.h
	$(CC) -mprocessor=32MX795F512L -x c -c "thermocouple.c" -o"Intermediary\thermocouple.o" -MMD -MF"Intermediary\thermocouple.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/uart.o : uart.c HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h uart.h
	$(CC) -mprocessor=32MX795F512L -x c -c "uart.c" -o"Intermediary\uart.o" -MMD -MF"Intermediary\uart.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/usb_descriptors.o : usb_descriptors.c ../Microchip/Include/USB/usb.h ../Microchip/Include/GenericTypeDefs.h ../Microchip/Include/Compiler.h usb_config.h ../Microchip/Include/USB/usb_common.h ../Microchip/Include/USB/usb_ch9.h ../Microchip/Include/USB/usb_device.h ../Microchip/Include/USB/usb_hal.h ../Microchip/Include/USB/usb_hal_pic32.h ../Microchip/Include/USB/usb_function_msd.h ../Microchip/Include/MDD\ File\ System/FSDefs.h
	$(CC) -mprocessor=32MX795F512L -x c -c "usb_descriptors.c" -o"Intermediary\usb_descriptors.o" -MMD -MF"Intermediary\usb_descriptors.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/FSIO.o : Y:/Técnico/Projectos/SRoque/RoqDry\ Plus_Versão\ 3/Dossier\ de\ projecto/Software/RoqDryPlus\ v3.5\ -\ Cliente/Microchip/MDD\ File\ System/FSIO.c ../Microchip/Include/Compiler.h ../Microchip/Include/MDD\ File\ System/FSIO.h FSconfig.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h ../Microchip/Include/MDD\ File\ System/FSDefs.h ../Microchip/Include/MDD\ File\ System/SD-SPI.h
	$(CC) -mprocessor=32MX795F512L -x c -c "Y:\Técnico\Projectos\SRoque\RoqDry Plus_Versão 3\Dossier de projecto\Software\RoqDryPlus v3.5 - Cliente\Microchip\MDD File System\FSIO.c" -o"Intermediary\FSIO.o" -MMD -MF"Intermediary\FSIO.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/SD-SPI.o : Y:/Técnico/Projectos/SRoque/RoqDry\ Plus_Versão\ 3/Dossier\ de\ projecto/Software/RoqDryPlus\ v3.5\ -\ Cliente/Microchip/MDD\ File\ System/SD-SPI.c ../Microchip/Include/Compiler.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h ../Microchip/Include/MDD\ File\ System/FSIO.h FSconfig.h HardwareProfile.h ../Microchip/Include/MDD\ File\ System/FSDefs.h ../Microchip/Include/MDD\ File\ System/SD-SPI.h
	$(CC) -mprocessor=32MX795F512L -x c -c "Y:\Técnico\Projectos\SRoque\RoqDry Plus_Versão 3\Dossier de projecto\Software\RoqDryPlus v3.5 - Cliente\Microchip\MDD File System\SD-SPI.c" -o"Intermediary\SD-SPI.o" -MMD -MF"Intermediary\SD-SPI.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/usb_device.o : Y:/Técnico/Projectos/SRoque/RoqDry\ Plus_Versão\ 3/Dossier\ de\ projecto/Software/RoqDryPlus\ v3.5\ -\ Cliente/Microchip/USB/usb_device.c ../Microchip/Include/USB/usb.h ../Microchip/Include/GenericTypeDefs.h ../Microchip/Include/Compiler.h usb_config.h ../Microchip/Include/USB/usb_common.h ../Microchip/Include/USB/usb_ch9.h ../Microchip/Include/USB/usb_device.h ../Microchip/Include/USB/usb_hal.h ../Microchip/Include/USB/usb_hal_pic32.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h Y:/Técnico/Projectos/SRoque/RoqDry\ Plus_Versão\ 3/Dossier\ de\ projecto/Software/RoqDryPlus\ v3.5\ -\ Cliente/Microchip/USB/usb_device_local.h ../Microchip/Include/USB/usb_function_msd.h ../Microchip/Include/MDD\ File\ System/FSDefs.h
	$(CC) -mprocessor=32MX795F512L -x c -c "Y:\Técnico\Projectos\SRoque\RoqDry Plus_Versão 3\Dossier de projecto\Software\RoqDryPlus v3.5 - Cliente\Microchip\USB\usb_device.c" -o"Intermediary\usb_device.o" -MMD -MF"Intermediary\usb_device.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

Intermediary/usb_function_msd.o : Y:/Técnico/Projectos/SRoque/RoqDry\ Plus_Versão\ 3/Dossier\ de\ projecto/Software/RoqDryPlus\ v3.5\ -\ Cliente/Microchip/USB/usb_function_msd.c ../Microchip/Include/USB/usb.h ../Microchip/Include/GenericTypeDefs.h ../Microchip/Include/Compiler.h usb_config.h ../Microchip/Include/USB/usb_common.h ../Microchip/Include/USB/usb_ch9.h ../Microchip/Include/USB/usb_device.h ../Microchip/Include/USB/usb_hal.h ../Microchip/Include/USB/usb_hal_pic32.h HardwareProfile.h HardwareProfile\ -\ PIC32MX795F512L.h usb_config.h FSconfig.h HardwareProfile.h ../Microchip/Include/USB/usb_function_msd.h ../Microchip/Include/MDD\ File\ System/FSDefs.h ../Microchip/Include/MDD\ File\ System/SD-SPI.h
	$(CC) -mprocessor=32MX795F512L -x c -c "Y:\Técnico\Projectos\SRoque\RoqDry Plus_Versão 3\Dossier de projecto\Software\RoqDryPlus v3.5 - Cliente\Microchip\USB\usb_function_msd.c" -o"Intermediary\usb_function_msd.o" -MMD -MF"Intermediary\usb_function_msd.d" -I"../Microchip/MDD File System" -I"../Microchip/USB" -I"../Microchip/Include/MDD File System" -I"../Microchip/Include/USB" -I"../Microchip/Include" -I"." -g

clean : 
	$(RM) "Intermediary\adc.o" "Intermediary\buzzer.o" "Intermediary\can.o" "Intermediary\fram.o" "Intermediary\glcd.o" "Intermediary\i2c.o" "Intermediary\io.o" "Intermediary\main.o" "Intermediary\matrixKeyboard.o" "Intermediary\pwm.o" "Intermediary\rtc.o" "Intermediary\spi.o" "Intermediary\thermocouple.o" "Intermediary\uart.o" "Intermediary\usb_descriptors.o" "Intermediary\FSIO.o" "Intermediary\SD-SPI.o" "Intermediary\usb_device.o" "Intermediary\usb_function_msd.o" "Output\RoqDryPlus.elf" "Output\RoqDryPlus.hex"

