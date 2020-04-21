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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=main.c ../../lib_pic/adc.c ../../lib_pic/i2c.c ../../lib_misc/delays.c ../../lib_misc/clock.c ../../lib_misc/misc.c ../../lib_pic/timer.c ../../lib_pic/pwm.c ../../lib_misc/bcd.c ../../lib_comp/ds1307.c ../../lib_comp/pcf8574.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/958983984/adc.p1 ${OBJECTDIR}/_ext/958983984/i2c.p1 ${OBJECTDIR}/_ext/336356346/delays.p1 ${OBJECTDIR}/_ext/336356346/clock.p1 ${OBJECTDIR}/_ext/336356346/misc.p1 ${OBJECTDIR}/_ext/958983984/timer.p1 ${OBJECTDIR}/_ext/958983984/pwm.p1 ${OBJECTDIR}/_ext/336356346/bcd.p1 ${OBJECTDIR}/_ext/336648663/ds1307.p1 ${OBJECTDIR}/_ext/336648663/pcf8574.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/main.p1.d ${OBJECTDIR}/_ext/958983984/adc.p1.d ${OBJECTDIR}/_ext/958983984/i2c.p1.d ${OBJECTDIR}/_ext/336356346/delays.p1.d ${OBJECTDIR}/_ext/336356346/clock.p1.d ${OBJECTDIR}/_ext/336356346/misc.p1.d ${OBJECTDIR}/_ext/958983984/timer.p1.d ${OBJECTDIR}/_ext/958983984/pwm.p1.d ${OBJECTDIR}/_ext/336356346/bcd.p1.d ${OBJECTDIR}/_ext/336648663/ds1307.p1.d ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/958983984/adc.p1 ${OBJECTDIR}/_ext/958983984/i2c.p1 ${OBJECTDIR}/_ext/336356346/delays.p1 ${OBJECTDIR}/_ext/336356346/clock.p1 ${OBJECTDIR}/_ext/336356346/misc.p1 ${OBJECTDIR}/_ext/958983984/timer.p1 ${OBJECTDIR}/_ext/958983984/pwm.p1 ${OBJECTDIR}/_ext/336356346/bcd.p1 ${OBJECTDIR}/_ext/336648663/ds1307.p1 ${OBJECTDIR}/_ext/336648663/pcf8574.p1

# Source Files
SOURCEFILES=main.c ../../lib_pic/adc.c ../../lib_pic/i2c.c ../../lib_misc/delays.c ../../lib_misc/clock.c ../../lib_misc/misc.c ../../lib_pic/timer.c ../../lib_pic/pwm.c ../../lib_misc/bcd.c ../../lib_comp/ds1307.c ../../lib_comp/pcf8574.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F252
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/adc.p1: ../../lib_pic/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/adc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/adc.p1 ../../lib_pic/adc.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/adc.d ${OBJECTDIR}/_ext/958983984/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/i2c.p1: ../../lib_pic/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/i2c.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/i2c.p1 ../../lib_pic/i2c.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/i2c.d ${OBJECTDIR}/_ext/958983984/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/delays.p1: ../../lib_misc/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/delays.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/delays.p1 ../../lib_misc/delays.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/delays.d ${OBJECTDIR}/_ext/336356346/delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/clock.p1: ../../lib_misc/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/clock.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/clock.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/clock.p1 ../../lib_misc/clock.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/clock.d ${OBJECTDIR}/_ext/336356346/clock.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/clock.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/misc.p1: ../../lib_misc/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/misc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/misc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/misc.p1 ../../lib_misc/misc.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/misc.d ${OBJECTDIR}/_ext/336356346/misc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/misc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/timer.p1: ../../lib_pic/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/timer.p1 ../../lib_pic/timer.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/timer.d ${OBJECTDIR}/_ext/958983984/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/pwm.p1: ../../lib_pic/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/pwm.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/pwm.p1 ../../lib_pic/pwm.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/pwm.d ${OBJECTDIR}/_ext/958983984/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/bcd.p1: ../../lib_misc/bcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/bcd.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/bcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/bcd.p1 ../../lib_misc/bcd.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/bcd.d ${OBJECTDIR}/_ext/336356346/bcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/bcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336648663/ds1307.p1: ../../lib_comp/ds1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336648663" 
	@${RM} ${OBJECTDIR}/_ext/336648663/ds1307.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336648663/ds1307.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336648663/ds1307.p1 ../../lib_comp/ds1307.c 
	@-${MV} ${OBJECTDIR}/_ext/336648663/ds1307.d ${OBJECTDIR}/_ext/336648663/ds1307.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336648663/ds1307.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336648663/pcf8574.p1: ../../lib_comp/pcf8574.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336648663" 
	@${RM} ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336648663/pcf8574.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336648663/pcf8574.p1 ../../lib_comp/pcf8574.c 
	@-${MV} ${OBJECTDIR}/_ext/336648663/pcf8574.d ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/adc.p1: ../../lib_pic/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/adc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/adc.p1 ../../lib_pic/adc.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/adc.d ${OBJECTDIR}/_ext/958983984/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/i2c.p1: ../../lib_pic/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/i2c.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/i2c.p1 ../../lib_pic/i2c.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/i2c.d ${OBJECTDIR}/_ext/958983984/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/delays.p1: ../../lib_misc/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/delays.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/delays.p1 ../../lib_misc/delays.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/delays.d ${OBJECTDIR}/_ext/336356346/delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/clock.p1: ../../lib_misc/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/clock.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/clock.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/clock.p1 ../../lib_misc/clock.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/clock.d ${OBJECTDIR}/_ext/336356346/clock.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/clock.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/misc.p1: ../../lib_misc/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/misc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/misc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/misc.p1 ../../lib_misc/misc.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/misc.d ${OBJECTDIR}/_ext/336356346/misc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/misc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/timer.p1: ../../lib_pic/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/timer.p1 ../../lib_pic/timer.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/timer.d ${OBJECTDIR}/_ext/958983984/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/958983984/pwm.p1: ../../lib_pic/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/958983984" 
	@${RM} ${OBJECTDIR}/_ext/958983984/pwm.p1.d 
	@${RM} ${OBJECTDIR}/_ext/958983984/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/958983984/pwm.p1 ../../lib_pic/pwm.c 
	@-${MV} ${OBJECTDIR}/_ext/958983984/pwm.d ${OBJECTDIR}/_ext/958983984/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/958983984/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336356346/bcd.p1: ../../lib_misc/bcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336356346" 
	@${RM} ${OBJECTDIR}/_ext/336356346/bcd.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336356346/bcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336356346/bcd.p1 ../../lib_misc/bcd.c 
	@-${MV} ${OBJECTDIR}/_ext/336356346/bcd.d ${OBJECTDIR}/_ext/336356346/bcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336356346/bcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336648663/ds1307.p1: ../../lib_comp/ds1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336648663" 
	@${RM} ${OBJECTDIR}/_ext/336648663/ds1307.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336648663/ds1307.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336648663/ds1307.p1 ../../lib_comp/ds1307.c 
	@-${MV} ${OBJECTDIR}/_ext/336648663/ds1307.d ${OBJECTDIR}/_ext/336648663/ds1307.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336648663/ds1307.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/336648663/pcf8574.p1: ../../lib_comp/pcf8574.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/336648663" 
	@${RM} ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d 
	@${RM} ${OBJECTDIR}/_ext/336648663/pcf8574.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/336648663/pcf8574.p1 ../../lib_comp/pcf8574.c 
	@-${MV} ${OBJECTDIR}/_ext/336648663/pcf8574.d ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/336648663/pcf8574.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -mrom=default,-7dc0-7fff -mram=default,-5f4-5ff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff  $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../lib_pic" -I"../../lib_comp" -I"../../lib_misc" -I"." -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v1.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
