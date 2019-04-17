################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
CMD_SRCS += \
../msp432p401r.cmd

INC_DIR = /home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/inc

C_SRCS += \
$(INC_DIR)/Clock.c \
$(INC_DIR)/SysTick.c \
$(INC_DIR)/LaunchPad.c \
$(INC_DIR)/Reflectance.c \
$(INC_DIR)/CortexM.c \
$(INC_DIR)/LineInt.c \
$(INC_DIR)/TimerA2.c \
$(INC_DIR)/TimerA0.c \
$(INC_DIR)/FSM.c \
$(INC_DIR)/Motor.c \
$(INC_DIR)/TExaS.c \
../LineFollowing2.c \
../startup_msp432p401r_ccs.c \
../system_msp432p401r.c

C_DEPS += $(patsubst %.c,%.d,$(notdir $(C_SRCS)))

OBJS += $(patsubst %.d,%.obj,$(C_DEPS))
