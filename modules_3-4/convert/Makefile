ASMFILE=convert.asm
OBJ=convert.o
EXE=convert

CFILE=convert.c
CASM_OUT=convert.S

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
QEMU=qemu-arm

$(EXE): $(OBJ)
	$(LD) $(OBJ) -o $(EXE)

c:
	$(CC) $(CFILE) -S -o $(CASM_OUT)

$(OBJ):
	$(AS) $(ASMFILE) -mccs -g -o $(OBJ)

qemu: $(EXE)
	$(QEMU) -singlestep -g 1234 $(EXE)

clean:
	rm $(OBJ) $(EXE)
	rm $(CASM_OUT)
