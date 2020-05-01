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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../interrupts_management.c ../main.c ../../../../Libraries/lib_pic/pic_config.c ../../../../Libraries/lib_misc/delays.c ../../../../Libraries/lib_misc/i2c_tools.c ../../../../Libraries/lib_misc/misc.c ../../../../Libraries/lib_chips/pcf8574.c ../../../../Libraries/lib_chips/ds1621.c ../../../../Libraries/lib_chips/ds1337.c ../../../../Libraries/lib_lcd/lcd_2x16.c ../../../../Libraries/lib_lcd/glcd_320x240.c ../../../../Libraries/lib_pic/uart.c ../../../../Libraries/lib_pic/timer.c ../../../../Libraries/lib_pic/oscillator.c ../../../../Libraries/lib_pic/i2c.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/interrupts_management.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1976726522/pic_config.o ${OBJECTDIR}/_ext/1148891260/delays.o ${OBJECTDIR}/_ext/1148891260/i2c_tools.o ${OBJECTDIR}/_ext/1148891260/misc.o ${OBJECTDIR}/_ext/1246616599/pcf8574.o ${OBJECTDIR}/_ext/1246616599/ds1621.o ${OBJECTDIR}/_ext/1246616599/ds1337.o ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o ${OBJECTDIR}/_ext/1976726522/uart.o ${OBJECTDIR}/_ext/1976726522/timer.o ${OBJECTDIR}/_ext/1976726522/oscillator.o ${OBJECTDIR}/_ext/1976726522/i2c.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/interrupts_management.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1976726522/pic_config.o.d ${OBJECTDIR}/_ext/1148891260/delays.o.d ${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d ${OBJECTDIR}/_ext/1148891260/misc.o.d ${OBJECTDIR}/_ext/1246616599/pcf8574.o.d ${OBJECTDIR}/_ext/1246616599/ds1621.o.d ${OBJECTDIR}/_ext/1246616599/ds1337.o.d ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d ${OBJECTDIR}/_ext/1976726522/uart.o.d ${OBJECTDIR}/_ext/1976726522/timer.o.d ${OBJECTDIR}/_ext/1976726522/oscillator.o.d ${OBJECTDIR}/_ext/1976726522/i2c.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/interrupts_management.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1976726522/pic_config.o ${OBJECTDIR}/_ext/1148891260/delays.o ${OBJECTDIR}/_ext/1148891260/i2c_tools.o ${OBJECTDIR}/_ext/1148891260/misc.o ${OBJECTDIR}/_ext/1246616599/pcf8574.o ${OBJECTDIR}/_ext/1246616599/ds1621.o ${OBJECTDIR}/_ext/1246616599/ds1337.o ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o ${OBJECTDIR}/_ext/1976726522/uart.o ${OBJECTDIR}/_ext/1976726522/timer.o ${OBJECTDIR}/_ext/1976726522/oscillator.o ${OBJECTDIR}/_ext/1976726522/i2c.o

# Source Files
SOURCEFILES=../interrupts_management.c ../main.c ../../../../Libraries/lib_pic/pic_config.c ../../../../Libraries/lib_misc/delays.c ../../../../Libraries/lib_misc/i2c_tools.c ../../../../Libraries/lib_misc/misc.c ../../../../Libraries/lib_chips/pcf8574.c ../../../../Libraries/lib_chips/ds1621.c ../../../../Libraries/lib_chips/ds1337.c ../../../../Libraries/lib_lcd/lcd_2x16.c ../../../../Libraries/lib_lcd/glcd_320x240.c ../../../../Libraries/lib_pic/uart.c ../../../../Libraries/lib_pic/timer.c ../../../../Libraries/lib_pic/oscillator.c ../../../../Libraries/lib_pic/i2c.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ256MC710
MP_LINKER_FILE_OPTION=,--script=p33FJ256MC710.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/interrupts_management.o: ../interrupts_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../interrupts_management.c  -o ${OBJECTDIR}/_ext/1472/interrupts_management.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/interrupts_management.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupts_management.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/pic_config.o: ../../../../Libraries/lib_pic/pic_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/pic_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/pic_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/pic_config.c  -o ${OBJECTDIR}/_ext/1976726522/pic_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/pic_config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/pic_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1148891260/delays.o: ../../../../Libraries/lib_misc/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1148891260" 
	@${RM} ${OBJECTDIR}/_ext/1148891260/delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1148891260/delays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_misc/delays.c  -o ${OBJECTDIR}/_ext/1148891260/delays.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1148891260/delays.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1148891260/delays.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1148891260/i2c_tools.o: ../../../../Libraries/lib_misc/i2c_tools.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1148891260" 
	@${RM} ${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d 
	@${RM} ${OBJECTDIR}/_ext/1148891260/i2c_tools.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_misc/i2c_tools.c  -o ${OBJECTDIR}/_ext/1148891260/i2c_tools.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1148891260/misc.o: ../../../../Libraries/lib_misc/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1148891260" 
	@${RM} ${OBJECTDIR}/_ext/1148891260/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1148891260/misc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_misc/misc.c  -o ${OBJECTDIR}/_ext/1148891260/misc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1148891260/misc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1148891260/misc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1246616599/pcf8574.o: ../../../../Libraries/lib_chips/pcf8574.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246616599" 
	@${RM} ${OBJECTDIR}/_ext/1246616599/pcf8574.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246616599/pcf8574.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_chips/pcf8574.c  -o ${OBJECTDIR}/_ext/1246616599/pcf8574.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246616599/pcf8574.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246616599/pcf8574.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1246616599/ds1621.o: ../../../../Libraries/lib_chips/ds1621.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246616599" 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1621.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1621.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_chips/ds1621.c  -o ${OBJECTDIR}/_ext/1246616599/ds1621.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246616599/ds1621.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246616599/ds1621.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1246616599/ds1337.o: ../../../../Libraries/lib_chips/ds1337.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246616599" 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1337.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1337.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_chips/ds1337.c  -o ${OBJECTDIR}/_ext/1246616599/ds1337.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246616599/ds1337.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246616599/ds1337.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976722493/lcd_2x16.o: ../../../../Libraries/lib_lcd/lcd_2x16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976722493" 
	@${RM} ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_lcd/lcd_2x16.c  -o ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976722493/glcd_320x240.o: ../../../../Libraries/lib_lcd/glcd_320x240.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976722493" 
	@${RM} ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_lcd/glcd_320x240.c  -o ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/uart.o: ../../../../Libraries/lib_pic/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/uart.c  -o ${OBJECTDIR}/_ext/1976726522/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/timer.o: ../../../../Libraries/lib_pic/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/timer.c  -o ${OBJECTDIR}/_ext/1976726522/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/oscillator.o: ../../../../Libraries/lib_pic/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/oscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/oscillator.c  -o ${OBJECTDIR}/_ext/1976726522/oscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/oscillator.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/oscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/i2c.o: ../../../../Libraries/lib_pic/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/i2c.c  -o ${OBJECTDIR}/_ext/1976726522/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/i2c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1472/interrupts_management.o: ../interrupts_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupts_management.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../interrupts_management.c  -o ${OBJECTDIR}/_ext/1472/interrupts_management.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/interrupts_management.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupts_management.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/pic_config.o: ../../../../Libraries/lib_pic/pic_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/pic_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/pic_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/pic_config.c  -o ${OBJECTDIR}/_ext/1976726522/pic_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/pic_config.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/pic_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1148891260/delays.o: ../../../../Libraries/lib_misc/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1148891260" 
	@${RM} ${OBJECTDIR}/_ext/1148891260/delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1148891260/delays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_misc/delays.c  -o ${OBJECTDIR}/_ext/1148891260/delays.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1148891260/delays.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1148891260/delays.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1148891260/i2c_tools.o: ../../../../Libraries/lib_misc/i2c_tools.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1148891260" 
	@${RM} ${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d 
	@${RM} ${OBJECTDIR}/_ext/1148891260/i2c_tools.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_misc/i2c_tools.c  -o ${OBJECTDIR}/_ext/1148891260/i2c_tools.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1148891260/i2c_tools.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1148891260/misc.o: ../../../../Libraries/lib_misc/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1148891260" 
	@${RM} ${OBJECTDIR}/_ext/1148891260/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1148891260/misc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_misc/misc.c  -o ${OBJECTDIR}/_ext/1148891260/misc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1148891260/misc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1148891260/misc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1246616599/pcf8574.o: ../../../../Libraries/lib_chips/pcf8574.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246616599" 
	@${RM} ${OBJECTDIR}/_ext/1246616599/pcf8574.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246616599/pcf8574.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_chips/pcf8574.c  -o ${OBJECTDIR}/_ext/1246616599/pcf8574.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246616599/pcf8574.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246616599/pcf8574.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1246616599/ds1621.o: ../../../../Libraries/lib_chips/ds1621.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246616599" 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1621.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1621.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_chips/ds1621.c  -o ${OBJECTDIR}/_ext/1246616599/ds1621.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246616599/ds1621.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246616599/ds1621.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1246616599/ds1337.o: ../../../../Libraries/lib_chips/ds1337.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246616599" 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1337.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246616599/ds1337.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_chips/ds1337.c  -o ${OBJECTDIR}/_ext/1246616599/ds1337.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246616599/ds1337.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246616599/ds1337.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976722493/lcd_2x16.o: ../../../../Libraries/lib_lcd/lcd_2x16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976722493" 
	@${RM} ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_lcd/lcd_2x16.c  -o ${OBJECTDIR}/_ext/1976722493/lcd_2x16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976722493/lcd_2x16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976722493/glcd_320x240.o: ../../../../Libraries/lib_lcd/glcd_320x240.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976722493" 
	@${RM} ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_lcd/glcd_320x240.c  -o ${OBJECTDIR}/_ext/1976722493/glcd_320x240.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976722493/glcd_320x240.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/uart.o: ../../../../Libraries/lib_pic/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/uart.c  -o ${OBJECTDIR}/_ext/1976726522/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/timer.o: ../../../../Libraries/lib_pic/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/timer.c  -o ${OBJECTDIR}/_ext/1976726522/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/timer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/oscillator.o: ../../../../Libraries/lib_pic/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/oscillator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/oscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/oscillator.c  -o ${OBJECTDIR}/_ext/1976726522/oscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/oscillator.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/oscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1976726522/i2c.o: ../../../../Libraries/lib_pic/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1976726522" 
	@${RM} ${OBJECTDIR}/_ext/1976726522/i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1976726522/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Libraries/lib_pic/i2c.c  -o ${OBJECTDIR}/_ext/1976726522/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1976726522/i2c.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -O0 -I".." -I"../../../../Libraries" -I"../../../../Libraries/lib_pic" -I"../../../headers" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1976726522/i2c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -I"../../../../Libraries/lib_chips" -I"../../../../Libraries/lib_pic" -I"../../../../Libraries/lib_misc" -I"../../../../Libraries/lib_lcd" -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pitechoid_ref.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
