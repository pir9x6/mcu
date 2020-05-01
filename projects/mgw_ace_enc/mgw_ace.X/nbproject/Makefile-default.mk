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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../lm63.c ../tmp75.c ../pwm.c ../timer.c ../i2c_slave.c ../i2c_master.c ../adc.c ../main.c ../pic32mx_cfg.c ../delays.c ../io_control.c ../power_management.c ../temp_management.c ../i2c_registers.c ../interrupt_management.c ../led_power.c D:/SVN/MGW-ACE-ENC/Trunk/pic32/common.c D:/SVN/MGW-ACE-ENC/Trunk/pic32/config_performance.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/lm63.o ${OBJECTDIR}/_ext/1472/tmp75.o ${OBJECTDIR}/_ext/1472/pwm.o ${OBJECTDIR}/_ext/1472/timer.o ${OBJECTDIR}/_ext/1472/i2c_slave.o ${OBJECTDIR}/_ext/1472/i2c_master.o ${OBJECTDIR}/_ext/1472/adc.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o ${OBJECTDIR}/_ext/1472/delays.o ${OBJECTDIR}/_ext/1472/io_control.o ${OBJECTDIR}/_ext/1472/power_management.o ${OBJECTDIR}/_ext/1472/temp_management.o ${OBJECTDIR}/_ext/1472/i2c_registers.o ${OBJECTDIR}/_ext/1472/interrupt_management.o ${OBJECTDIR}/_ext/1472/led_power.o ${OBJECTDIR}/_ext/111011056/common.o ${OBJECTDIR}/_ext/111011056/config_performance.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/lm63.o.d ${OBJECTDIR}/_ext/1472/tmp75.o.d ${OBJECTDIR}/_ext/1472/pwm.o.d ${OBJECTDIR}/_ext/1472/timer.o.d ${OBJECTDIR}/_ext/1472/i2c_slave.o.d ${OBJECTDIR}/_ext/1472/i2c_master.o.d ${OBJECTDIR}/_ext/1472/adc.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d ${OBJECTDIR}/_ext/1472/delays.o.d ${OBJECTDIR}/_ext/1472/io_control.o.d ${OBJECTDIR}/_ext/1472/power_management.o.d ${OBJECTDIR}/_ext/1472/temp_management.o.d ${OBJECTDIR}/_ext/1472/i2c_registers.o.d ${OBJECTDIR}/_ext/1472/interrupt_management.o.d ${OBJECTDIR}/_ext/1472/led_power.o.d ${OBJECTDIR}/_ext/111011056/common.o.d ${OBJECTDIR}/_ext/111011056/config_performance.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/lm63.o ${OBJECTDIR}/_ext/1472/tmp75.o ${OBJECTDIR}/_ext/1472/pwm.o ${OBJECTDIR}/_ext/1472/timer.o ${OBJECTDIR}/_ext/1472/i2c_slave.o ${OBJECTDIR}/_ext/1472/i2c_master.o ${OBJECTDIR}/_ext/1472/adc.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o ${OBJECTDIR}/_ext/1472/delays.o ${OBJECTDIR}/_ext/1472/io_control.o ${OBJECTDIR}/_ext/1472/power_management.o ${OBJECTDIR}/_ext/1472/temp_management.o ${OBJECTDIR}/_ext/1472/i2c_registers.o ${OBJECTDIR}/_ext/1472/interrupt_management.o ${OBJECTDIR}/_ext/1472/led_power.o ${OBJECTDIR}/_ext/111011056/common.o ${OBJECTDIR}/_ext/111011056/config_performance.o

# Source Files
SOURCEFILES=../lm63.c ../tmp75.c ../pwm.c ../timer.c ../i2c_slave.c ../i2c_master.c ../adc.c ../main.c ../pic32mx_cfg.c ../delays.c ../io_control.c ../power_management.c ../temp_management.c ../i2c_registers.c ../interrupt_management.c ../led_power.c D:/SVN/MGW-ACE-ENC/Trunk/pic32/common.c D:/SVN/MGW-ACE-ENC/Trunk/pic32/config_performance.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX775F256L
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/_ext/1472/lm63.o: ../lm63.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/lm63.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/lm63.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/lm63.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/lm63.o.d" -o ${OBJECTDIR}/_ext/1472/lm63.o ../lm63.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/tmp75.o: ../tmp75.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/tmp75.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/tmp75.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/tmp75.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/tmp75.o.d" -o ${OBJECTDIR}/_ext/1472/tmp75.o ../tmp75.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/pwm.o: ../pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/pwm.o.d" -o ${OBJECTDIR}/_ext/1472/pwm.o ../pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/timer.o: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/timer.o.d" -o ${OBJECTDIR}/_ext/1472/timer.o ../timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c_slave.o: ../i2c_slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_slave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_slave.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_slave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_slave.o.d" -o ${OBJECTDIR}/_ext/1472/i2c_slave.o ../i2c_slave.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c_master.o: ../i2c_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_master.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_master.o.d" -o ${OBJECTDIR}/_ext/1472/i2c_master.o ../i2c_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/adc.o: ../adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/adc.o.d" -o ${OBJECTDIR}/_ext/1472/adc.o ../adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/pic32mx_cfg.o: ../pic32mx_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d" -o ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o ../pic32mx_cfg.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/delays.o: ../delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delays.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/delays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/delays.o.d" -o ${OBJECTDIR}/_ext/1472/delays.o ../delays.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/io_control.o: ../io_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/io_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/io_control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/io_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/io_control.o.d" -o ${OBJECTDIR}/_ext/1472/io_control.o ../io_control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/power_management.o: ../power_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/power_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/power_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/power_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/power_management.o.d" -o ${OBJECTDIR}/_ext/1472/power_management.o ../power_management.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/temp_management.o: ../temp_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/temp_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/temp_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/temp_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/temp_management.o.d" -o ${OBJECTDIR}/_ext/1472/temp_management.o ../temp_management.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c_registers.o: ../i2c_registers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_registers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_registers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_registers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_registers.o.d" -o ${OBJECTDIR}/_ext/1472/i2c_registers.o ../i2c_registers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/interrupt_management.o: ../interrupt_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupt_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/interrupt_management.o.d" -o ${OBJECTDIR}/_ext/1472/interrupt_management.o ../interrupt_management.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/led_power.o: ../led_power.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/led_power.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/led_power.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/led_power.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/led_power.o.d" -o ${OBJECTDIR}/_ext/1472/led_power.o ../led_power.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/111011056/common.o: D:/SVN/MGW-ACE-ENC/Trunk/pic32/common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/111011056" 
	@${RM} ${OBJECTDIR}/_ext/111011056/common.o.d 
	@${RM} ${OBJECTDIR}/_ext/111011056/common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/111011056/common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/111011056/common.o.d" -o ${OBJECTDIR}/_ext/111011056/common.o D:/SVN/MGW-ACE-ENC/Trunk/pic32/common.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/111011056/config_performance.o: D:/SVN/MGW-ACE-ENC/Trunk/pic32/config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/111011056" 
	@${RM} ${OBJECTDIR}/_ext/111011056/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/111011056/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/111011056/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/111011056/config_performance.o.d" -o ${OBJECTDIR}/_ext/111011056/config_performance.o D:/SVN/MGW-ACE-ENC/Trunk/pic32/config_performance.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1472/lm63.o: ../lm63.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/lm63.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/lm63.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/lm63.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/lm63.o.d" -o ${OBJECTDIR}/_ext/1472/lm63.o ../lm63.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/tmp75.o: ../tmp75.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/tmp75.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/tmp75.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/tmp75.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/tmp75.o.d" -o ${OBJECTDIR}/_ext/1472/tmp75.o ../tmp75.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/pwm.o: ../pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/pwm.o.d" -o ${OBJECTDIR}/_ext/1472/pwm.o ../pwm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/timer.o: ../timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/timer.o.d" -o ${OBJECTDIR}/_ext/1472/timer.o ../timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c_slave.o: ../i2c_slave.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_slave.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_slave.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_slave.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_slave.o.d" -o ${OBJECTDIR}/_ext/1472/i2c_slave.o ../i2c_slave.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c_master.o: ../i2c_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_master.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_master.o.d" -o ${OBJECTDIR}/_ext/1472/i2c_master.o ../i2c_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/adc.o: ../adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/adc.o.d" -o ${OBJECTDIR}/_ext/1472/adc.o ../adc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/pic32mx_cfg.o: ../pic32mx_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/pic32mx_cfg.o.d" -o ${OBJECTDIR}/_ext/1472/pic32mx_cfg.o ../pic32mx_cfg.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/delays.o: ../delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delays.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/delays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/delays.o.d" -o ${OBJECTDIR}/_ext/1472/delays.o ../delays.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/io_control.o: ../io_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/io_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/io_control.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/io_control.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/io_control.o.d" -o ${OBJECTDIR}/_ext/1472/io_control.o ../io_control.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/power_management.o: ../power_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/power_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/power_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/power_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/power_management.o.d" -o ${OBJECTDIR}/_ext/1472/power_management.o ../power_management.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/temp_management.o: ../temp_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/temp_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/temp_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/temp_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/temp_management.o.d" -o ${OBJECTDIR}/_ext/1472/temp_management.o ../temp_management.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/i2c_registers.o: ../i2c_registers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_registers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/i2c_registers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/i2c_registers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/i2c_registers.o.d" -o ${OBJECTDIR}/_ext/1472/i2c_registers.o ../i2c_registers.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/interrupt_management.o: ../interrupt_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_management.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_management.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupt_management.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/interrupt_management.o.d" -o ${OBJECTDIR}/_ext/1472/interrupt_management.o ../interrupt_management.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1472/led_power.o: ../led_power.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/led_power.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/led_power.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/led_power.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/1472/led_power.o.d" -o ${OBJECTDIR}/_ext/1472/led_power.o ../led_power.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/111011056/common.o: D:/SVN/MGW-ACE-ENC/Trunk/pic32/common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/111011056" 
	@${RM} ${OBJECTDIR}/_ext/111011056/common.o.d 
	@${RM} ${OBJECTDIR}/_ext/111011056/common.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/111011056/common.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/111011056/common.o.d" -o ${OBJECTDIR}/_ext/111011056/common.o D:/SVN/MGW-ACE-ENC/Trunk/pic32/common.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/111011056/config_performance.o: D:/SVN/MGW-ACE-ENC/Trunk/pic32/config_performance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/111011056" 
	@${RM} ${OBJECTDIR}/_ext/111011056/config_performance.o.d 
	@${RM} ${OBJECTDIR}/_ext/111011056/config_performance.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/111011056/config_performance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -D_SUPPRESS_PLIB_WARNING -D_DISABLE_OPENADC10_CONFIGPORT_WARNING -D_PLIB_DISABLE_LEGACY -I"../../../../../Projects/ACE-ENC/MGW-ACE/Trunk/pic32" -I"C:/Microchip/xc32/v1.40/pic32mx/include/peripheral" -I"C:/Microchip/xc32/v1.40/pic32mx/lib" -I"C:/Microchip/xc32/v1.40/pic32mx/include" -I".." -I"." -MMD -MF "${OBJECTDIR}/_ext/111011056/config_performance.o.d" -o ${OBJECTDIR}/_ext/111011056/config_performance.o D:/SVN/MGW-ACE-ENC/Trunk/pic32/config_performance.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-L"..",-L".",-Map="${DISTDIR}/mgw_ace.X.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-L"..",-L".",-Map="${DISTDIR}/mgw_ace.X.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/mgw_ace.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
