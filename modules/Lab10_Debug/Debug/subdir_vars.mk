################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../msp432p401r.cmd 

INC_DIR = /home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/inc

C_SRCS += \
$(INC_DIR)/Bump.c \
$(INC_DIR)/Clock.c \
$(INC_DIR)/CortexM.c \
$(INC_DIR)/FlashProgram.c \
$(INC_DIR)/FlashDebug.c \
$(INC_DIR)/LaunchPad.c \
$(INC_DIR)/Reflectance.c \
$(INC_DIR)/SysTickInts.c \
../Lab10_Debugmain.c \
../startup_msp432p401r_ccs.c \
../system_msp432p401r.c 

C_DEPS += $(patsubst %.c,%.d,$(notdir $(C_SRCS)))

OBJS += $(patsubst %.d,%.obj,$(C_DEPS))
