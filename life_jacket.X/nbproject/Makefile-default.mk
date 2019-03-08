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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/acc/accelerometer.c src/acc/lis2hh12_io.c src/audio/ext_flash.c src/audio/pcm1770.c src/audio/audio.c src/audio/dma.c src/gps/jf2_uart.c src/gps/nmea.c src/gps/nmea_queue.c src/gps/jf2_io.c src/gps/gps.c src/hal/clock.c src/hal/flash.c src/hal/gpio.c src/hal/spi_hal.c src/hal/uart.c src/hal/configuration_bits.c src/lora/rfm95w.c src/lora/rfm95w_io.c src/lora/lora_tx_queue.c src/lora/p2pc_protocol.c src/main/main.c src/uart/terminal.c src/uart/terminal_help.c src/uart/debug_log.c src/status.c src/lora/p2ps_protocol.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/acc/accelerometer.o ${OBJECTDIR}/src/acc/lis2hh12_io.o ${OBJECTDIR}/src/audio/ext_flash.o ${OBJECTDIR}/src/audio/pcm1770.o ${OBJECTDIR}/src/audio/audio.o ${OBJECTDIR}/src/audio/dma.o ${OBJECTDIR}/src/gps/jf2_uart.o ${OBJECTDIR}/src/gps/nmea.o ${OBJECTDIR}/src/gps/nmea_queue.o ${OBJECTDIR}/src/gps/jf2_io.o ${OBJECTDIR}/src/gps/gps.o ${OBJECTDIR}/src/hal/clock.o ${OBJECTDIR}/src/hal/flash.o ${OBJECTDIR}/src/hal/gpio.o ${OBJECTDIR}/src/hal/spi_hal.o ${OBJECTDIR}/src/hal/uart.o ${OBJECTDIR}/src/hal/configuration_bits.o ${OBJECTDIR}/src/lora/rfm95w.o ${OBJECTDIR}/src/lora/rfm95w_io.o ${OBJECTDIR}/src/lora/lora_tx_queue.o ${OBJECTDIR}/src/lora/p2pc_protocol.o ${OBJECTDIR}/src/main/main.o ${OBJECTDIR}/src/uart/terminal.o ${OBJECTDIR}/src/uart/terminal_help.o ${OBJECTDIR}/src/uart/debug_log.o ${OBJECTDIR}/src/status.o ${OBJECTDIR}/src/lora/p2ps_protocol.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/acc/accelerometer.o.d ${OBJECTDIR}/src/acc/lis2hh12_io.o.d ${OBJECTDIR}/src/audio/ext_flash.o.d ${OBJECTDIR}/src/audio/pcm1770.o.d ${OBJECTDIR}/src/audio/audio.o.d ${OBJECTDIR}/src/audio/dma.o.d ${OBJECTDIR}/src/gps/jf2_uart.o.d ${OBJECTDIR}/src/gps/nmea.o.d ${OBJECTDIR}/src/gps/nmea_queue.o.d ${OBJECTDIR}/src/gps/jf2_io.o.d ${OBJECTDIR}/src/gps/gps.o.d ${OBJECTDIR}/src/hal/clock.o.d ${OBJECTDIR}/src/hal/flash.o.d ${OBJECTDIR}/src/hal/gpio.o.d ${OBJECTDIR}/src/hal/spi_hal.o.d ${OBJECTDIR}/src/hal/uart.o.d ${OBJECTDIR}/src/hal/configuration_bits.o.d ${OBJECTDIR}/src/lora/rfm95w.o.d ${OBJECTDIR}/src/lora/rfm95w_io.o.d ${OBJECTDIR}/src/lora/lora_tx_queue.o.d ${OBJECTDIR}/src/lora/p2pc_protocol.o.d ${OBJECTDIR}/src/main/main.o.d ${OBJECTDIR}/src/uart/terminal.o.d ${OBJECTDIR}/src/uart/terminal_help.o.d ${OBJECTDIR}/src/uart/debug_log.o.d ${OBJECTDIR}/src/status.o.d ${OBJECTDIR}/src/lora/p2ps_protocol.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/acc/accelerometer.o ${OBJECTDIR}/src/acc/lis2hh12_io.o ${OBJECTDIR}/src/audio/ext_flash.o ${OBJECTDIR}/src/audio/pcm1770.o ${OBJECTDIR}/src/audio/audio.o ${OBJECTDIR}/src/audio/dma.o ${OBJECTDIR}/src/gps/jf2_uart.o ${OBJECTDIR}/src/gps/nmea.o ${OBJECTDIR}/src/gps/nmea_queue.o ${OBJECTDIR}/src/gps/jf2_io.o ${OBJECTDIR}/src/gps/gps.o ${OBJECTDIR}/src/hal/clock.o ${OBJECTDIR}/src/hal/flash.o ${OBJECTDIR}/src/hal/gpio.o ${OBJECTDIR}/src/hal/spi_hal.o ${OBJECTDIR}/src/hal/uart.o ${OBJECTDIR}/src/hal/configuration_bits.o ${OBJECTDIR}/src/lora/rfm95w.o ${OBJECTDIR}/src/lora/rfm95w_io.o ${OBJECTDIR}/src/lora/lora_tx_queue.o ${OBJECTDIR}/src/lora/p2pc_protocol.o ${OBJECTDIR}/src/main/main.o ${OBJECTDIR}/src/uart/terminal.o ${OBJECTDIR}/src/uart/terminal_help.o ${OBJECTDIR}/src/uart/debug_log.o ${OBJECTDIR}/src/status.o ${OBJECTDIR}/src/lora/p2ps_protocol.o

# Source Files
SOURCEFILES=src/acc/accelerometer.c src/acc/lis2hh12_io.c src/audio/ext_flash.c src/audio/pcm1770.c src/audio/audio.c src/audio/dma.c src/gps/jf2_uart.c src/gps/nmea.c src/gps/nmea_queue.c src/gps/jf2_io.c src/gps/gps.c src/hal/clock.c src/hal/flash.c src/hal/gpio.c src/hal/spi_hal.c src/hal/uart.c src/hal/configuration_bits.c src/lora/rfm95w.c src/lora/rfm95w_io.c src/lora/lora_tx_queue.c src/lora/p2pc_protocol.c src/main/main.c src/uart/terminal.c src/uart/terminal_help.c src/uart/debug_log.c src/status.c src/lora/p2ps_protocol.c


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

# The following macros may be used in the pre and post step lines
Device=PIC24FJ128GA204
ProjectDir="C:\Users\Erik\Dropbox\exjobb\sw\working_dir\lifeJacket\life_jacket.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [python -E increment_build_number.py]"
	@python -E increment_build_number.py
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=24FJ128GA204
MP_LINKER_FILE_OPTION=,--script=p24FJ128GA204.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/acc/accelerometer.o: src/acc/accelerometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/acc" 
	@${RM} ${OBJECTDIR}/src/acc/accelerometer.o.d 
	@${RM} ${OBJECTDIR}/src/acc/accelerometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/acc/accelerometer.c  -o ${OBJECTDIR}/src/acc/accelerometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/acc/accelerometer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/acc/accelerometer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/acc/lis2hh12_io.o: src/acc/lis2hh12_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/acc" 
	@${RM} ${OBJECTDIR}/src/acc/lis2hh12_io.o.d 
	@${RM} ${OBJECTDIR}/src/acc/lis2hh12_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/acc/lis2hh12_io.c  -o ${OBJECTDIR}/src/acc/lis2hh12_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/acc/lis2hh12_io.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/acc/lis2hh12_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/ext_flash.o: src/audio/ext_flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/ext_flash.o.d 
	@${RM} ${OBJECTDIR}/src/audio/ext_flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/ext_flash.c  -o ${OBJECTDIR}/src/audio/ext_flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/ext_flash.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/ext_flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/pcm1770.o: src/audio/pcm1770.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/pcm1770.o.d 
	@${RM} ${OBJECTDIR}/src/audio/pcm1770.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/pcm1770.c  -o ${OBJECTDIR}/src/audio/pcm1770.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/pcm1770.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/pcm1770.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/audio.o: src/audio/audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/audio.o.d 
	@${RM} ${OBJECTDIR}/src/audio/audio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/audio.c  -o ${OBJECTDIR}/src/audio/audio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/audio.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/audio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/dma.o: src/audio/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/dma.o.d 
	@${RM} ${OBJECTDIR}/src/audio/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/dma.c  -o ${OBJECTDIR}/src/audio/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/jf2_uart.o: src/gps/jf2_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/jf2_uart.o.d 
	@${RM} ${OBJECTDIR}/src/gps/jf2_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/jf2_uart.c  -o ${OBJECTDIR}/src/gps/jf2_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/jf2_uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/jf2_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/nmea.o: src/gps/nmea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/nmea.o.d 
	@${RM} ${OBJECTDIR}/src/gps/nmea.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/nmea.c  -o ${OBJECTDIR}/src/gps/nmea.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/nmea.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/nmea.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/nmea_queue.o: src/gps/nmea_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/nmea_queue.o.d 
	@${RM} ${OBJECTDIR}/src/gps/nmea_queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/nmea_queue.c  -o ${OBJECTDIR}/src/gps/nmea_queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/nmea_queue.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/nmea_queue.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/jf2_io.o: src/gps/jf2_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/jf2_io.o.d 
	@${RM} ${OBJECTDIR}/src/gps/jf2_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/jf2_io.c  -o ${OBJECTDIR}/src/gps/jf2_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/jf2_io.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/jf2_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/gps.o: src/gps/gps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/gps.o.d 
	@${RM} ${OBJECTDIR}/src/gps/gps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/gps.c  -o ${OBJECTDIR}/src/gps/gps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/gps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/gps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/clock.o: src/hal/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/clock.o.d 
	@${RM} ${OBJECTDIR}/src/hal/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/clock.c  -o ${OBJECTDIR}/src/hal/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/flash.o: src/hal/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/flash.o.d 
	@${RM} ${OBJECTDIR}/src/hal/flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/flash.c  -o ${OBJECTDIR}/src/hal/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/flash.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/gpio.o: src/hal/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/hal/gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/gpio.c  -o ${OBJECTDIR}/src/hal/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/gpio.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/spi_hal.o: src/hal/spi_hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/spi_hal.o.d 
	@${RM} ${OBJECTDIR}/src/hal/spi_hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/spi_hal.c  -o ${OBJECTDIR}/src/hal/spi_hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/spi_hal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/spi_hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/uart.o: src/hal/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/uart.c  -o ${OBJECTDIR}/src/hal/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/configuration_bits.o: src/hal/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/src/hal/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/configuration_bits.c  -o ${OBJECTDIR}/src/hal/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/configuration_bits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/rfm95w.o: src/lora/rfm95w.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w.o.d 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/rfm95w.c  -o ${OBJECTDIR}/src/lora/rfm95w.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/rfm95w.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/rfm95w.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/rfm95w_io.o: src/lora/rfm95w_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w_io.o.d 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/rfm95w_io.c  -o ${OBJECTDIR}/src/lora/rfm95w_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/rfm95w_io.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/rfm95w_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/lora_tx_queue.o: src/lora/lora_tx_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/lora_tx_queue.o.d 
	@${RM} ${OBJECTDIR}/src/lora/lora_tx_queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/lora_tx_queue.c  -o ${OBJECTDIR}/src/lora/lora_tx_queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/lora_tx_queue.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/lora_tx_queue.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/p2pc_protocol.o: src/lora/p2pc_protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/p2pc_protocol.o.d 
	@${RM} ${OBJECTDIR}/src/lora/p2pc_protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/p2pc_protocol.c  -o ${OBJECTDIR}/src/lora/p2pc_protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/p2pc_protocol.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/p2pc_protocol.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main/main.o: src/main/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/main" 
	@${RM} ${OBJECTDIR}/src/main/main.o.d 
	@${RM} ${OBJECTDIR}/src/main/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main/main.c  -o ${OBJECTDIR}/src/main/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart/terminal.o: src/uart/terminal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/uart" 
	@${RM} ${OBJECTDIR}/src/uart/terminal.o.d 
	@${RM} ${OBJECTDIR}/src/uart/terminal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart/terminal.c  -o ${OBJECTDIR}/src/uart/terminal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart/terminal.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/uart/terminal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart/terminal_help.o: src/uart/terminal_help.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/uart" 
	@${RM} ${OBJECTDIR}/src/uart/terminal_help.o.d 
	@${RM} ${OBJECTDIR}/src/uart/terminal_help.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart/terminal_help.c  -o ${OBJECTDIR}/src/uart/terminal_help.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart/terminal_help.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/uart/terminal_help.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart/debug_log.o: src/uart/debug_log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/uart" 
	@${RM} ${OBJECTDIR}/src/uart/debug_log.o.d 
	@${RM} ${OBJECTDIR}/src/uart/debug_log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart/debug_log.c  -o ${OBJECTDIR}/src/uart/debug_log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart/debug_log.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/uart/debug_log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/status.o: src/status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/status.o.d 
	@${RM} ${OBJECTDIR}/src/status.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/status.c  -o ${OBJECTDIR}/src/status.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/status.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/status.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/p2ps_protocol.o: src/lora/p2ps_protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/p2ps_protocol.o.d 
	@${RM} ${OBJECTDIR}/src/lora/p2ps_protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/p2ps_protocol.c  -o ${OBJECTDIR}/src/lora/p2ps_protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/p2ps_protocol.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/p2ps_protocol.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/acc/accelerometer.o: src/acc/accelerometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/acc" 
	@${RM} ${OBJECTDIR}/src/acc/accelerometer.o.d 
	@${RM} ${OBJECTDIR}/src/acc/accelerometer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/acc/accelerometer.c  -o ${OBJECTDIR}/src/acc/accelerometer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/acc/accelerometer.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/acc/accelerometer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/acc/lis2hh12_io.o: src/acc/lis2hh12_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/acc" 
	@${RM} ${OBJECTDIR}/src/acc/lis2hh12_io.o.d 
	@${RM} ${OBJECTDIR}/src/acc/lis2hh12_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/acc/lis2hh12_io.c  -o ${OBJECTDIR}/src/acc/lis2hh12_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/acc/lis2hh12_io.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/acc/lis2hh12_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/ext_flash.o: src/audio/ext_flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/ext_flash.o.d 
	@${RM} ${OBJECTDIR}/src/audio/ext_flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/ext_flash.c  -o ${OBJECTDIR}/src/audio/ext_flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/ext_flash.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/ext_flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/pcm1770.o: src/audio/pcm1770.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/pcm1770.o.d 
	@${RM} ${OBJECTDIR}/src/audio/pcm1770.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/pcm1770.c  -o ${OBJECTDIR}/src/audio/pcm1770.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/pcm1770.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/pcm1770.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/audio.o: src/audio/audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/audio.o.d 
	@${RM} ${OBJECTDIR}/src/audio/audio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/audio.c  -o ${OBJECTDIR}/src/audio/audio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/audio.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/audio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/audio/dma.o: src/audio/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/audio" 
	@${RM} ${OBJECTDIR}/src/audio/dma.o.d 
	@${RM} ${OBJECTDIR}/src/audio/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/audio/dma.c  -o ${OBJECTDIR}/src/audio/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/audio/dma.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/audio/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/jf2_uart.o: src/gps/jf2_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/jf2_uart.o.d 
	@${RM} ${OBJECTDIR}/src/gps/jf2_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/jf2_uart.c  -o ${OBJECTDIR}/src/gps/jf2_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/jf2_uart.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/jf2_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/nmea.o: src/gps/nmea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/nmea.o.d 
	@${RM} ${OBJECTDIR}/src/gps/nmea.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/nmea.c  -o ${OBJECTDIR}/src/gps/nmea.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/nmea.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/nmea.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/nmea_queue.o: src/gps/nmea_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/nmea_queue.o.d 
	@${RM} ${OBJECTDIR}/src/gps/nmea_queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/nmea_queue.c  -o ${OBJECTDIR}/src/gps/nmea_queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/nmea_queue.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/nmea_queue.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/jf2_io.o: src/gps/jf2_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/jf2_io.o.d 
	@${RM} ${OBJECTDIR}/src/gps/jf2_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/jf2_io.c  -o ${OBJECTDIR}/src/gps/jf2_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/jf2_io.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/jf2_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/gps/gps.o: src/gps/gps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/gps" 
	@${RM} ${OBJECTDIR}/src/gps/gps.o.d 
	@${RM} ${OBJECTDIR}/src/gps/gps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/gps/gps.c  -o ${OBJECTDIR}/src/gps/gps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/gps/gps.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/gps/gps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/clock.o: src/hal/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/clock.o.d 
	@${RM} ${OBJECTDIR}/src/hal/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/clock.c  -o ${OBJECTDIR}/src/hal/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/clock.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/flash.o: src/hal/flash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/flash.o.d 
	@${RM} ${OBJECTDIR}/src/hal/flash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/flash.c  -o ${OBJECTDIR}/src/hal/flash.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/flash.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/flash.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/gpio.o: src/hal/gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/gpio.o.d 
	@${RM} ${OBJECTDIR}/src/hal/gpio.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/gpio.c  -o ${OBJECTDIR}/src/hal/gpio.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/gpio.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/gpio.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/spi_hal.o: src/hal/spi_hal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/spi_hal.o.d 
	@${RM} ${OBJECTDIR}/src/hal/spi_hal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/spi_hal.c  -o ${OBJECTDIR}/src/hal/spi_hal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/spi_hal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/spi_hal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/uart.o: src/hal/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/uart.o.d 
	@${RM} ${OBJECTDIR}/src/hal/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/uart.c  -o ${OBJECTDIR}/src/hal/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/uart.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/hal/configuration_bits.o: src/hal/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/src/hal/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/hal/configuration_bits.c  -o ${OBJECTDIR}/src/hal/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/hal/configuration_bits.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/hal/configuration_bits.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/rfm95w.o: src/lora/rfm95w.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w.o.d 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/rfm95w.c  -o ${OBJECTDIR}/src/lora/rfm95w.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/rfm95w.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/rfm95w.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/rfm95w_io.o: src/lora/rfm95w_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w_io.o.d 
	@${RM} ${OBJECTDIR}/src/lora/rfm95w_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/rfm95w_io.c  -o ${OBJECTDIR}/src/lora/rfm95w_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/rfm95w_io.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/rfm95w_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/lora_tx_queue.o: src/lora/lora_tx_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/lora_tx_queue.o.d 
	@${RM} ${OBJECTDIR}/src/lora/lora_tx_queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/lora_tx_queue.c  -o ${OBJECTDIR}/src/lora/lora_tx_queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/lora_tx_queue.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/lora_tx_queue.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/p2pc_protocol.o: src/lora/p2pc_protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/p2pc_protocol.o.d 
	@${RM} ${OBJECTDIR}/src/lora/p2pc_protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/p2pc_protocol.c  -o ${OBJECTDIR}/src/lora/p2pc_protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/p2pc_protocol.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/p2pc_protocol.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main/main.o: src/main/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/main" 
	@${RM} ${OBJECTDIR}/src/main/main.o.d 
	@${RM} ${OBJECTDIR}/src/main/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main/main.c  -o ${OBJECTDIR}/src/main/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main/main.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart/terminal.o: src/uart/terminal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/uart" 
	@${RM} ${OBJECTDIR}/src/uart/terminal.o.d 
	@${RM} ${OBJECTDIR}/src/uart/terminal.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart/terminal.c  -o ${OBJECTDIR}/src/uart/terminal.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart/terminal.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/uart/terminal.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart/terminal_help.o: src/uart/terminal_help.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/uart" 
	@${RM} ${OBJECTDIR}/src/uart/terminal_help.o.d 
	@${RM} ${OBJECTDIR}/src/uart/terminal_help.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart/terminal_help.c  -o ${OBJECTDIR}/src/uart/terminal_help.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart/terminal_help.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/uart/terminal_help.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/uart/debug_log.o: src/uart/debug_log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/uart" 
	@${RM} ${OBJECTDIR}/src/uart/debug_log.o.d 
	@${RM} ${OBJECTDIR}/src/uart/debug_log.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/uart/debug_log.c  -o ${OBJECTDIR}/src/uart/debug_log.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/uart/debug_log.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/uart/debug_log.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/status.o: src/status.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/status.o.d 
	@${RM} ${OBJECTDIR}/src/status.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/status.c  -o ${OBJECTDIR}/src/status.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/status.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/status.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/lora/p2ps_protocol.o: src/lora/p2ps_protocol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/lora" 
	@${RM} ${OBJECTDIR}/src/lora/p2ps_protocol.o.d 
	@${RM} ${OBJECTDIR}/src/lora/p2ps_protocol.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/lora/p2ps_protocol.c  -o ${OBJECTDIR}/src/lora/p2ps_protocol.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/lora/p2ps_protocol.o.d"      -mno-eds-warn  -g -omf=elf -O0 -I"inc" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/lora/p2ps_protocol.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=0,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/life_jacket.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python -E terminal_doc_gen.py]"
	@python -E terminal_doc_gen.py
	@echo "--------------------------------------"

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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
