FILES=Lab04_SoftwareDesignmain.c
OUT=Lab04.exe

ARM-CC=arm-none-eabi-gcc
ARM-LINKER=arm-none-eabi-ld
OBJ=Lab04.o
SOLUTION-OBJ=Solution.obj

ARM-OUT=Lab04-arm.exe

QEMU=qemu-arm

#LIBGCC=/usr/lib/gcc/arm-none-eabi/8.2.0/thumb/v8-m.main/nofp/
LIBGCC=/opt/ccstudio/ccsv8/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/lib/gcc/arm-none-eabi/7.2.1/thumb/v8-m.main/fpv5-sp/softfp/
LD-FLAGS=-L$(LIBGCC) -lgcc

$(ARM-OUT):
	$(ARM-CC) $(FILES) -g -c -o $(OBJ) -DARM=1
	$(ARM-LINKER) $(LD-FLAGS) $(OBJ) $(SOLUTION-OBJ) -o $(ARM-OUT)

qemu:$(ARM-OUT)
	$(QEMU) -g 1234 $(ARM-OUT)

$(OUT):
	$(CC) $(FILES) -o $(OUT)

clean:
	if [ -f $(OUT) ] ; then rm $(OUT) ; fi
	if [ -f $(OBJ) ]; then rm $(OBJ) ; fi
	if [ -f $(ARM-OUT) ]; then rm $(ARM-OUT) ; fi
