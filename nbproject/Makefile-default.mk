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
FINAL_IMAGE=${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=main.c source/oled.c source/i2c.c source/si5351.c source/rotary.c source/controller.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/source/oled.o ${OBJECTDIR}/source/i2c.o ${OBJECTDIR}/source/si5351.o ${OBJECTDIR}/source/rotary.o ${OBJECTDIR}/source/controller.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/source/oled.o.d ${OBJECTDIR}/source/i2c.o.d ${OBJECTDIR}/source/si5351.o.d ${OBJECTDIR}/source/rotary.o.d ${OBJECTDIR}/source/controller.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/source/oled.o ${OBJECTDIR}/source/i2c.o ${OBJECTDIR}/source/si5351.o ${OBJECTDIR}/source/rotary.o ${OBJECTDIR}/source/controller.o

# Source Files
SOURCEFILES=main.c source/oled.c source/i2c.c source/si5351.c source/rotary.c source/controller.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F3012
MP_LINKER_FILE_OPTION=,--script=p30F3012.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/786c4e3c2a611079693d72609c03f15964c1c1e4 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/oled.o: source/oled.c  .generated_files/flags/default/d7b0cd39209cf4a0052db6e347ad891bcfe634e9 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/oled.o.d 
	@${RM} ${OBJECTDIR}/source/oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/oled.c  -o ${OBJECTDIR}/source/oled.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/oled.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/i2c.o: source/i2c.c  .generated_files/flags/default/2e327735eaddba318c9134093818fcf923dc012a .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/i2c.o.d 
	@${RM} ${OBJECTDIR}/source/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/i2c.c  -o ${OBJECTDIR}/source/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/i2c.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/si5351.o: source/si5351.c  .generated_files/flags/default/53466dbb0335698a4c3288801160d117e23ed276 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/si5351.o.d 
	@${RM} ${OBJECTDIR}/source/si5351.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/si5351.c  -o ${OBJECTDIR}/source/si5351.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/si5351.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/rotary.o: source/rotary.c  .generated_files/flags/default/2849544cdef092acf4a4d5c25f6fa5507ede34d2 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/rotary.o.d 
	@${RM} ${OBJECTDIR}/source/rotary.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/rotary.c  -o ${OBJECTDIR}/source/rotary.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/rotary.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/controller.o: source/controller.c  .generated_files/flags/default/a4dbfe203a4c3a7dbb19a5130ef08648a2f6e7af .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/controller.o.d 
	@${RM} ${OBJECTDIR}/source/controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/controller.c  -o ${OBJECTDIR}/source/controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/controller.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/cb620c2bc4db4d7256e8facdf9a3a3c82edbfca0 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/oled.o: source/oled.c  .generated_files/flags/default/61640d24440ed9dee53ff40c2bfb499b47c5e888 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/oled.o.d 
	@${RM} ${OBJECTDIR}/source/oled.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/oled.c  -o ${OBJECTDIR}/source/oled.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/oled.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/i2c.o: source/i2c.c  .generated_files/flags/default/787a153ec323dcd27f588a75bec0f4ca8661f507 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/i2c.o.d 
	@${RM} ${OBJECTDIR}/source/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/i2c.c  -o ${OBJECTDIR}/source/i2c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/i2c.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/si5351.o: source/si5351.c  .generated_files/flags/default/752ecf45e646870362922572c8403596af61d40e .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/si5351.o.d 
	@${RM} ${OBJECTDIR}/source/si5351.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/si5351.c  -o ${OBJECTDIR}/source/si5351.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/si5351.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/rotary.o: source/rotary.c  .generated_files/flags/default/31e7557e4cdded47c3a9483468b4378657029fd3 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/rotary.o.d 
	@${RM} ${OBJECTDIR}/source/rotary.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/rotary.c  -o ${OBJECTDIR}/source/rotary.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/rotary.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/source/controller.o: source/controller.c  .generated_files/flags/default/9cf1fbdd6698e4438e86aba40da0f730ebb5108 .generated_files/flags/default/bcecbc814c247f3d72fc54f9d0d34aa9c791f402
	@${MKDIR} "${OBJECTDIR}/source" 
	@${RM} ${OBJECTDIR}/source/controller.o.d 
	@${RM} ${OBJECTDIR}/source/controller.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  source/controller.c  -o ${OBJECTDIR}/source/controller.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/source/controller.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off   
	
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
${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	
else
${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/FT8_DsPic_Transceiver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
