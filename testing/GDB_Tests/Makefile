FILE=test.S
OBJ=test.o
EXE=test

AS=arm-none-eabi-as
LD=arm-none-eabi-ld
QEMU=qemu-arm

$(EXE): $(OBJ)
	$(LD) $(OBJ) -o $(EXE)

$(OBJ):
	$(AS) $(FILE) -g -o $(OBJ)

qemu: $(EXE)
	$(QEMU) -singlestep -g 1234 $(EXE)


clean:
	rm $(OBJ) $(EXE)
