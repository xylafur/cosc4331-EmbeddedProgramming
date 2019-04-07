################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Bump.obj: ../../inc/Bump.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.obj: ../../inc/Clock.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

CortexM.obj: ../../inc/CortexM.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FlashProgram.obj: ../../inc/FlashProgram.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FlashDebug.obj: ../../inc/FlashDebug.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '



%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.obj: ../../inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Reflectance.obj: ../../inc/Reflectance.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

SysTickInts.obj: ../../inc/SysTickInts.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/Lab10_Debug" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


