################################################################################
# Automatically-generated file. Do not edit!
################################################################################

INC_DIR = /home/yelsek/projects/cosc4331-EmbeddedProgramming/modules/inc

# Each subdirectory must supply rules for building sources it contributes
%.obj: $(INC_DIR)/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -DLineFollowing1 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 -DLineFollowing1 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include" --include_path="/opt/ccstudio/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


