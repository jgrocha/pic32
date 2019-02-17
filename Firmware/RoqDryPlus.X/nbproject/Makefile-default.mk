#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../../Microchip/MDD File System/FSIO.c" "../../Microchip/MDD File System/SD-SPI.c" ../../Microchip/USB/usb_device.c ../../Microchip/USB/usb_function_msd.c ../adc.c ../buzzer.c ../can.c ../fram.c ../glcd.c ../i2c.c ../io.c ../main.c ../matrixKeyboard.c ../pwm.c ../rtc.c ../spi.c ../thermocouple.c ../uart.c ../usb_descriptors.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/65885567/FSIO.o ${OBJECTDIR}/_ext/65885567/SD-SPI.o ${OBJECTDIR}/_ext/713068069/usb_device.o ${OBJECTDIR}/_ext/713068069/usb_function_msd.o ${OBJECTDIR}/_ext/1472/adc.o ${OBJECTDIR}/_ext/1472/buzzer.o ${OBJECTDIR}/_ext/1472/can.o ${OBJECTDIR}/_ext/1472/fram.o ${OBJECTDIR}/_ext/1472/glcd.o ${OBJECTDIR}/_ext/1472/i2c.o ${OBJECTDIR}/_ext/1472/io.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/matrixKeyboard.o ${OBJECTDIR}/_ext/1472/pwm.o ${OBJECTDIR}/_ext/1472/rtc.o ${OBJECTDIR}/_ext/1472/spi.o ${OBJECTDIR}/_ext/1472/thermocouple.o ${OBJECTDIR}/_ext/1472/uart.o ${OBJECTDIR}/_ext/1472/usb_descriptors.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/65885567/FSIO.o.d ${OBJECTDIR}/_ext/65885567/SD-SPI.o.d ${OBJECTDIR}/_ext/713068069/usb_device.o.d ${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d ${OBJECTDIR}/_ext/1472/adc.o.d ${OBJECTDIR}/_ext/1472/buzzer.o.d ${OBJECTDIR}/_ext/1472/can.o.d ${OBJECTDIR}/_ext/1472/fram.o.d ${OBJECTDIR}/_ext/1472/glcd.o.d ${OBJECTDIR}/_ext/1472/i2c.o.d ${OBJECTDIR}/_ext/1472/io.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d ${OBJECTDIR}/_ext/1472/pwm.o.d ${OBJECTDIR}/_ext/1472/rtc.o.d ${OBJECTDIR}/_ext/1472/spi.o.d ${OBJECTDIR}/_ext/1472/thermocouple.o.d ${OBJECTDIR}/_ext/1472/uart.o.d ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/65885567/FSIO.o ${OBJECTDIR}/_ext/65885567/SD-SPI.o ${OBJECTDIR}/_ext/713068069/usb_device.o ${OBJECTDIR}/_ext/713068069/usb_function_msd.o ${OBJECTDIR}/_ext/1472/adc.o ${OBJECTDIR}/_ext/1472/buzzer.o ${OBJECTDIR}/_ext/1472/can.o ${OBJECTDIR}/_ext/1472/fram.o ${OBJECTDIR}/_ext/1472/glcd.o ${OBJECTDIR}/_ext/1472/i2c.o ${OBJECTDIR}/_ext/1472/io.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/matrixKeyboard.o ${OBJECTDIR}/_ext/1472/pwm.o ${OBJECTDIR}/_ext/1472/rtc.o ${OBJECTDIR}/_ext/1472/spi.o ${OBJECTDIR}/_ext/1472/thermocouple.o ${OBJECTDIR}/_ext/1472/uart.o ${OBJECTDIR}/_ext/1472/usb_descriptors.o

# Source Files
SOURCEFILES=../../Microchip/MDD File System/FSIO.c ../../Microchip/MDD File System/SD-SPI.c ../../Microchip/USB/usb_device.c ../../Microchip/USB/usb_function_msd.c ../adc.c ../buzzer.c ../can.c ../fram.c ../glcd.c ../i2c.c ../io.c ../main.c ../matrixKeyboard.c ../pwm.c ../rtc.c ../spi.c ../thermocouple.c ../uart.c ../usb_descriptors.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="../app_32MX795F512L.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/65885567/FSIO.o: ../../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/65885567" 
	@${RM} ${OBJECTDIR}/_ext/65885567/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/65885567/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65885567/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/65885567/FSIO.o.d" -o ${OBJECTDIR}/_ext/65885567/FSIO.o "../../Microchip/MDD File System/FSIO.c"    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/65885567/SD-SPI.o: ../../Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/65885567" 
	@${RM} ${OBJECTDIR}/_ext/65885567/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/65885567/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65885567/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/65885567/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/65885567/SD-SPI.o "../../Microchip/MDD File System/SD-SPI.c"    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/713068069/usb_device.o: ../../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/713068069" 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/713068069/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/713068069/usb_device.o.d" -o ${OBJECTDIR}/_ext/713068069/usb_device.o ../../Microchip/USB/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/713068069/usb_function_msd.o: ../../Microchip/USB/usb_function_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/713068069" 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_function_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d" -o ${OBJECTDIR}/_ext/713068069/usb_function_msd.o ../../Microchip/USB/usb_function_msd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/adc.o: ../adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/adc.o.d" -o ${OBJECTDIR}/_ext/1472/adc.o ../adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/buzzer.o: ../buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/buzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/buzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/buzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/buzzer.o.d" -o ${OBJECTDIR}/_ext/1472/buzzer.o ../buzzer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/can.o: ../can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/can.o.d" -o ${OBJECTDIR}/_ext/1472/can.o ../can.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/fram.o: ../fram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fram.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fram.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/fram.o.d" -o ${OBJECTDIR}/_ext/1472/fram.o ../fram.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/glcd.o: ../glcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/glcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/glcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/glcd.o.d" -o ${OBJECTDIR}/_ext/1472/glcd.o ../glcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/io.o: ../io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/io.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/io.o.d" -o ${OBJECTDIR}/_ext/1472/io.o ../io.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/matrixKeyboard.o: ../matrixKeyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/matrixKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d" -o ${OBJECTDIR}/_ext/1472/matrixKeyboard.o ../matrixKeyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/pwm.o: ../pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/pwm.o.d" -o ${OBJECTDIR}/_ext/1472/pwm.o ../pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/rtc.o: ../rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/rtc.o.d" -o ${OBJECTDIR}/_ext/1472/rtc.o ../rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/spi.o: ../spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/spi.o.d" -o ${OBJECTDIR}/_ext/1472/spi.o ../spi.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/thermocouple.o: ../thermocouple.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/thermocouple.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/thermocouple.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/thermocouple.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/thermocouple.o.d" -o ${OBJECTDIR}/_ext/1472/thermocouple.o ../thermocouple.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/uart.o.d" -o ${OBJECTDIR}/_ext/1472/uart.o ../uart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/usb_descriptors.o: ../usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1472/usb_descriptors.o ../usb_descriptors.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/65885567/FSIO.o: ../../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/65885567" 
	@${RM} ${OBJECTDIR}/_ext/65885567/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/65885567/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65885567/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/65885567/FSIO.o.d" -o ${OBJECTDIR}/_ext/65885567/FSIO.o "../../Microchip/MDD File System/FSIO.c"    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/65885567/SD-SPI.o: ../../Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/65885567" 
	@${RM} ${OBJECTDIR}/_ext/65885567/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/65885567/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65885567/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/65885567/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/65885567/SD-SPI.o "../../Microchip/MDD File System/SD-SPI.c"    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/713068069/usb_device.o: ../../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/713068069" 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/713068069/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/713068069/usb_device.o.d" -o ${OBJECTDIR}/_ext/713068069/usb_device.o ../../Microchip/USB/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/713068069/usb_function_msd.o: ../../Microchip/USB/usb_function_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/713068069" 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_function_msd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/713068069/usb_function_msd.o.d" -o ${OBJECTDIR}/_ext/713068069/usb_function_msd.o ../../Microchip/USB/usb_function_msd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/adc.o: ../adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/adc.o.d" -o ${OBJECTDIR}/_ext/1472/adc.o ../adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/buzzer.o: ../buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/buzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/buzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/buzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/buzzer.o.d" -o ${OBJECTDIR}/_ext/1472/buzzer.o ../buzzer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/can.o: ../can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/can.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/can.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/can.o.d" -o ${OBJECTDIR}/_ext/1472/can.o ../can.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/fram.o: ../fram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/fram.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/fram.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/fram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/fram.o.d" -o ${OBJECTDIR}/_ext/1472/fram.o ../fram.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/glcd.o: ../glcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/glcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/glcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/glcd.o.d" -o ${OBJECTDIR}/_ext/1472/glcd.o ../glcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c.o: ../i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/i2c.o.d" -o ${OBJECTDIR}/_ext/1472/i2c.o ../i2c.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/io.o: ../io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/io.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/io.o.d" -o ${OBJECTDIR}/_ext/1472/io.o ../io.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/matrixKeyboard.o: ../matrixKeyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/matrixKeyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/matrixKeyboard.o.d" -o ${OBJECTDIR}/_ext/1472/matrixKeyboard.o ../matrixKeyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/pwm.o: ../pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/pwm.o.d" -o ${OBJECTDIR}/_ext/1472/pwm.o ../pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/rtc.o: ../rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/rtc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/rtc.o.d" -o ${OBJECTDIR}/_ext/1472/rtc.o ../rtc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/spi.o: ../spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/spi.o.d" -o ${OBJECTDIR}/_ext/1472/spi.o ../spi.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/thermocouple.o: ../thermocouple.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/thermocouple.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/thermocouple.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/thermocouple.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/thermocouple.o.d" -o ${OBJECTDIR}/_ext/1472/thermocouple.o ../thermocouple.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/uart.o.d" -o ${OBJECTDIR}/_ext/1472/uart.o ../uart.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/usb_descriptors.o: ../usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../../Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -I"../../Microchip/MDD File System" -I"../../Microchip/USB" -I"." -I"/opt/microchip/xc32/v2.10/pic32-libs/include" -MMD -MF "${OBJECTDIR}/_ext/1472/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1472/usb_descriptors.o ../usb_descriptors.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--defsym=_min_heap_size=4096,--no-code-in-dinit,--no-dinit-in-serial-mem,-L"/opt/microchip/xc32/v2.10/lib",-L"/opt/microchip/xc32/v2.10/pic32mx/lib",-L".",-L"/opt/microchip/xc32/v1.40/pic32mx/lib",-L"..",-Map="${DISTDIR}/RoqDryPlus.X.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--no-code-in-dinit,--no-dinit-in-serial-mem,-L"/opt/microchip/xc32/v2.10/lib",-L"/opt/microchip/xc32/v2.10/pic32mx/lib",-L".",-L"/opt/microchip/xc32/v1.40/pic32mx/lib",-L"..",-Map="${DISTDIR}/RoqDryPlus.X.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/RoqDryPlus.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
