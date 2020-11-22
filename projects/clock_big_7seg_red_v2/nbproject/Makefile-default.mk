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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=main.c ../../libraries/lib_pic/i2c.c ../../libraries/lib_misc/delays.c ../../libraries/lib_misc/misc.c ../../libraries/lib_pic/timer.c ../../libraries/lib_pic/pwm.c ../../libraries/lib_misc/bcd.c ../../libraries/lib_comp/ds1307.c ../../libraries/lib_comp/pcf8574.c ../../libraries/lib_misc/date_time.c ../../libraries/lib_pic/uart.c ../../libraries/lib_misc/console.c ../../libraries/lib_misc/i2c_tools.c ../../libraries/lib_misc/log.c interrupts_management.c ../../libraries/lib_pic/interrupts.c pin_manager.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/113394246/i2c.p1 ${OBJECTDIR}/_ext/779656892/delays.p1 ${OBJECTDIR}/_ext/779656892/misc.p1 ${OBJECTDIR}/_ext/113394246/timer.p1 ${OBJECTDIR}/_ext/113394246/pwm.p1 ${OBJECTDIR}/_ext/779656892/bcd.p1 ${OBJECTDIR}/_ext/779364575/ds1307.p1 ${OBJECTDIR}/_ext/779364575/pcf8574.p1 ${OBJECTDIR}/_ext/779656892/date_time.p1 ${OBJECTDIR}/_ext/113394246/uart.p1 ${OBJECTDIR}/_ext/779656892/console.p1 ${OBJECTDIR}/_ext/779656892/i2c_tools.p1 ${OBJECTDIR}/_ext/779656892/log.p1 ${OBJECTDIR}/interrupts_management.p1 ${OBJECTDIR}/_ext/113394246/interrupts.p1 ${OBJECTDIR}/pin_manager.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/main.p1.d ${OBJECTDIR}/_ext/113394246/i2c.p1.d ${OBJECTDIR}/_ext/779656892/delays.p1.d ${OBJECTDIR}/_ext/779656892/misc.p1.d ${OBJECTDIR}/_ext/113394246/timer.p1.d ${OBJECTDIR}/_ext/113394246/pwm.p1.d ${OBJECTDIR}/_ext/779656892/bcd.p1.d ${OBJECTDIR}/_ext/779364575/ds1307.p1.d ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d ${OBJECTDIR}/_ext/779656892/date_time.p1.d ${OBJECTDIR}/_ext/113394246/uart.p1.d ${OBJECTDIR}/_ext/779656892/console.p1.d ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d ${OBJECTDIR}/_ext/779656892/log.p1.d ${OBJECTDIR}/interrupts_management.p1.d ${OBJECTDIR}/_ext/113394246/interrupts.p1.d ${OBJECTDIR}/pin_manager.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.p1 ${OBJECTDIR}/_ext/113394246/i2c.p1 ${OBJECTDIR}/_ext/779656892/delays.p1 ${OBJECTDIR}/_ext/779656892/misc.p1 ${OBJECTDIR}/_ext/113394246/timer.p1 ${OBJECTDIR}/_ext/113394246/pwm.p1 ${OBJECTDIR}/_ext/779656892/bcd.p1 ${OBJECTDIR}/_ext/779364575/ds1307.p1 ${OBJECTDIR}/_ext/779364575/pcf8574.p1 ${OBJECTDIR}/_ext/779656892/date_time.p1 ${OBJECTDIR}/_ext/113394246/uart.p1 ${OBJECTDIR}/_ext/779656892/console.p1 ${OBJECTDIR}/_ext/779656892/i2c_tools.p1 ${OBJECTDIR}/_ext/779656892/log.p1 ${OBJECTDIR}/interrupts_management.p1 ${OBJECTDIR}/_ext/113394246/interrupts.p1 ${OBJECTDIR}/pin_manager.p1

# Source Files
SOURCEFILES=main.c ../../libraries/lib_pic/i2c.c ../../libraries/lib_misc/delays.c ../../libraries/lib_misc/misc.c ../../libraries/lib_pic/timer.c ../../libraries/lib_pic/pwm.c ../../libraries/lib_misc/bcd.c ../../libraries/lib_comp/ds1307.c ../../libraries/lib_comp/pcf8574.c ../../libraries/lib_misc/date_time.c ../../libraries/lib_pic/uart.c ../../libraries/lib_misc/console.c ../../libraries/lib_misc/i2c_tools.c ../../libraries/lib_misc/log.c interrupts_management.c ../../libraries/lib_pic/interrupts.c pin_manager.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F57K42
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/i2c.p1: ../../libraries/lib_pic/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/i2c.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/i2c.p1 ../../libraries/lib_pic/i2c.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/i2c.d ${OBJECTDIR}/_ext/113394246/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/delays.p1: ../../libraries/lib_misc/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/delays.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/delays.p1 ../../libraries/lib_misc/delays.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/delays.d ${OBJECTDIR}/_ext/779656892/delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/misc.p1: ../../libraries/lib_misc/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/misc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/misc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/misc.p1 ../../libraries/lib_misc/misc.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/misc.d ${OBJECTDIR}/_ext/779656892/misc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/misc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/timer.p1: ../../libraries/lib_pic/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/timer.p1 ../../libraries/lib_pic/timer.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/timer.d ${OBJECTDIR}/_ext/113394246/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/pwm.p1: ../../libraries/lib_pic/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/pwm.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/pwm.p1 ../../libraries/lib_pic/pwm.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/pwm.d ${OBJECTDIR}/_ext/113394246/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/bcd.p1: ../../libraries/lib_misc/bcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/bcd.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/bcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/bcd.p1 ../../libraries/lib_misc/bcd.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/bcd.d ${OBJECTDIR}/_ext/779656892/bcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/bcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779364575/ds1307.p1: ../../libraries/lib_comp/ds1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779364575" 
	@${RM} ${OBJECTDIR}/_ext/779364575/ds1307.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779364575/ds1307.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779364575/ds1307.p1 ../../libraries/lib_comp/ds1307.c 
	@-${MV} ${OBJECTDIR}/_ext/779364575/ds1307.d ${OBJECTDIR}/_ext/779364575/ds1307.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779364575/ds1307.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779364575/pcf8574.p1: ../../libraries/lib_comp/pcf8574.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779364575" 
	@${RM} ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779364575/pcf8574.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779364575/pcf8574.p1 ../../libraries/lib_comp/pcf8574.c 
	@-${MV} ${OBJECTDIR}/_ext/779364575/pcf8574.d ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/date_time.p1: ../../libraries/lib_misc/date_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/date_time.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/date_time.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/date_time.p1 ../../libraries/lib_misc/date_time.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/date_time.d ${OBJECTDIR}/_ext/779656892/date_time.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/date_time.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/uart.p1: ../../libraries/lib_pic/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/uart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/uart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/uart.p1 ../../libraries/lib_pic/uart.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/uart.d ${OBJECTDIR}/_ext/113394246/uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/console.p1: ../../libraries/lib_misc/console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/console.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/console.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/console.p1 ../../libraries/lib_misc/console.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/console.d ${OBJECTDIR}/_ext/779656892/console.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/console.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/i2c_tools.p1: ../../libraries/lib_misc/i2c_tools.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/i2c_tools.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/i2c_tools.p1 ../../libraries/lib_misc/i2c_tools.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/i2c_tools.d ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/log.p1: ../../libraries/lib_misc/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/log.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/log.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/log.p1 ../../libraries/lib_misc/log.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/log.d ${OBJECTDIR}/_ext/779656892/log.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/log.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts_management.p1: interrupts_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts_management.p1.d 
	@${RM} ${OBJECTDIR}/interrupts_management.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/interrupts_management.p1 interrupts_management.c 
	@-${MV} ${OBJECTDIR}/interrupts_management.d ${OBJECTDIR}/interrupts_management.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts_management.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/interrupts.p1: ../../libraries/lib_pic/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/interrupts.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/interrupts.p1 ../../libraries/lib_pic/interrupts.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/interrupts.d ${OBJECTDIR}/_ext/113394246/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pin_manager.p1: pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/pin_manager.p1 pin_manager.c 
	@-${MV} ${OBJECTDIR}/pin_manager.d ${OBJECTDIR}/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/i2c.p1: ../../libraries/lib_pic/i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/i2c.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/i2c.p1 ../../libraries/lib_pic/i2c.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/i2c.d ${OBJECTDIR}/_ext/113394246/i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/delays.p1: ../../libraries/lib_misc/delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/delays.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/delays.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/delays.p1 ../../libraries/lib_misc/delays.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/delays.d ${OBJECTDIR}/_ext/779656892/delays.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/delays.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/misc.p1: ../../libraries/lib_misc/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/misc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/misc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/misc.p1 ../../libraries/lib_misc/misc.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/misc.d ${OBJECTDIR}/_ext/779656892/misc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/misc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/timer.p1: ../../libraries/lib_pic/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/timer.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/timer.p1 ../../libraries/lib_pic/timer.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/timer.d ${OBJECTDIR}/_ext/113394246/timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/pwm.p1: ../../libraries/lib_pic/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/pwm.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/pwm.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/pwm.p1 ../../libraries/lib_pic/pwm.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/pwm.d ${OBJECTDIR}/_ext/113394246/pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/bcd.p1: ../../libraries/lib_misc/bcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/bcd.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/bcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/bcd.p1 ../../libraries/lib_misc/bcd.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/bcd.d ${OBJECTDIR}/_ext/779656892/bcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/bcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779364575/ds1307.p1: ../../libraries/lib_comp/ds1307.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779364575" 
	@${RM} ${OBJECTDIR}/_ext/779364575/ds1307.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779364575/ds1307.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779364575/ds1307.p1 ../../libraries/lib_comp/ds1307.c 
	@-${MV} ${OBJECTDIR}/_ext/779364575/ds1307.d ${OBJECTDIR}/_ext/779364575/ds1307.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779364575/ds1307.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779364575/pcf8574.p1: ../../libraries/lib_comp/pcf8574.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779364575" 
	@${RM} ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779364575/pcf8574.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779364575/pcf8574.p1 ../../libraries/lib_comp/pcf8574.c 
	@-${MV} ${OBJECTDIR}/_ext/779364575/pcf8574.d ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779364575/pcf8574.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/date_time.p1: ../../libraries/lib_misc/date_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/date_time.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/date_time.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/date_time.p1 ../../libraries/lib_misc/date_time.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/date_time.d ${OBJECTDIR}/_ext/779656892/date_time.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/date_time.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/uart.p1: ../../libraries/lib_pic/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/uart.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/uart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/uart.p1 ../../libraries/lib_pic/uart.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/uart.d ${OBJECTDIR}/_ext/113394246/uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/console.p1: ../../libraries/lib_misc/console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/console.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/console.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/console.p1 ../../libraries/lib_misc/console.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/console.d ${OBJECTDIR}/_ext/779656892/console.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/console.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/i2c_tools.p1: ../../libraries/lib_misc/i2c_tools.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/i2c_tools.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/i2c_tools.p1 ../../libraries/lib_misc/i2c_tools.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/i2c_tools.d ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/i2c_tools.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/779656892/log.p1: ../../libraries/lib_misc/log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/779656892" 
	@${RM} ${OBJECTDIR}/_ext/779656892/log.p1.d 
	@${RM} ${OBJECTDIR}/_ext/779656892/log.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/779656892/log.p1 ../../libraries/lib_misc/log.c 
	@-${MV} ${OBJECTDIR}/_ext/779656892/log.d ${OBJECTDIR}/_ext/779656892/log.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/779656892/log.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts_management.p1: interrupts_management.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts_management.p1.d 
	@${RM} ${OBJECTDIR}/interrupts_management.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/interrupts_management.p1 interrupts_management.c 
	@-${MV} ${OBJECTDIR}/interrupts_management.d ${OBJECTDIR}/interrupts_management.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts_management.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/113394246/interrupts.p1: ../../libraries/lib_pic/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/113394246" 
	@${RM} ${OBJECTDIR}/_ext/113394246/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/_ext/113394246/interrupts.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/_ext/113394246/interrupts.p1 ../../libraries/lib_pic/interrupts.c 
	@-${MV} ${OBJECTDIR}/_ext/113394246/interrupts.d ${OBJECTDIR}/_ext/113394246/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/113394246/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/pin_manager.p1: pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/pin_manager.p1 pin_manager.c 
	@-${MV} ${OBJECTDIR}/pin_manager.d ${OBJECTDIR}/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
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
dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"../../libraries/lib_pic" -I"../../libraries/lib_comp" -I"../../libraries/lib_misc" -I"." -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/clock_big_7seg_red_v2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
