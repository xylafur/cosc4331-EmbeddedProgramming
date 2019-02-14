FILES=Lab04_SoftwareDesignmain.c
OUT=Lab04.exe

ARM-CC=arm-none-eabi-gcc

OBJ=Lab04.o
SOLUTION-OBJ=Solution.obj

ARM-OUT=Lab04-arm.exe

QEMU=qemu-arm

#LIBGCC=/usr/lib/gcc/arm-none-eabi/8.2.0/thumb/v8-m.main/nofp/
LIBGCC=/opt/ccstudio/ccsv8/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/lib/gcc/arm-none-eabi/7.2.1/thumb/v8-m.main/fpv5-sp/softfp/

ARM-LD=arm-none-eabi-ld
ARM-LD-FLAGS=-L$(LIBGCC) -lgcc

GDB=arm-none-eabi-gdb
GDB_INSTRUCTIONS=gdb-file

##THIS IS ALL STUFF FROM THE TI MAKE FILE
ARM-LINKER=/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl
LD-FLAGS += -mv7M4 --code_state=16 --float_support=FPv4SPD16
LD-FLAGS += -me --advice:power=all --define=__MSP432P401R__
LD-FLAGS += --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc
LD-FLAGS += --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi
LD-FLAGS += -z -m"Lab04_SoftwareDesign.map" --heap_size=1024 --stack_size=512
LD-FLAGS += -i"/opt/ccstudio/ccsv8/ccs_base/arm/include"
LD-FLAGS += -i"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/lib"
LD-FLAGS += -i"/opt/ccstudio/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include"
LD-FLAGS += --reread_libs --diag_wrap=off --display_error_number --warn_sections
LD-FLAGS += --xml_link_info="Lab04_SoftwareDesign_linkInfo.xml" --rom_model

$(ARM-OUT):
	$(ARM-CC) $(FILES) -g -c -o $(OBJ) -DARM=1
	#$(ARM-LINKER) $(LD-FLAGS) $(OBJ) $(SOLUTION-OBJ) -o $(ARM-OUT)
	$(ARM-LD) $(ARM-LD-FLAGS) $(OBJ) $(SOLUTION-OBJ) -o $(ARM-OUT)

qemu:$(ARM-OUT)
	$(QEMU) -g 1234 $(ARM-OUT)

gdb:
	$(GDB) -x $(GDB_INSTRUCTIONS)

$(OUT):
	$(CC) $(FILES) -o $(OUT)

clean:
	if [ -f $(OUT) ] ; then rm $(OUT) ; fi
	if [ -f $(OBJ) ]; then rm $(OBJ) ; fi
	if [ -f $(ARM-OUT) ]; then rm $(ARM-OUT) ; fi


