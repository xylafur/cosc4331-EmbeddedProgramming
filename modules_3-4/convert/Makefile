ASMFILE=convert.asm
OBJ=convert.o
EXE=convert

CFILE=convert.c
CASM_OUT=convert.S

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
QEMU=qemu-arm

#For the TI provided tools.. 
TI-CC=../../TI-Tools/TI-arm-cc
TI-AS=../../TI-Tools/TI-arm-cc --asm_file
TI-ASM=convert.non_gnu.asm
TI-OUT=



$(EXE): $(OBJ)
	$(LD) $(OBJ) -o $(EXE)

c:
	$(CC) $(CFILE) -S -o $(CASM_OUT)

$(OBJ):
	$(AS) $(ASMFILE) -g -o $(OBJ)

ti-out:
	$(TI-CC) --asm_file $(TI-ASM)

qemu: $(EXE)
	$(QEMU) -singlestep -g 1234 $(EXE)

clean:
	rm $(OBJ)
	rm $(EXE)
	rm $(CASM_OUT)
