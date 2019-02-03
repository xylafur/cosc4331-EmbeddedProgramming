;@ The goal of this module is to implement the function: D=1195172 / (n - 1058)
;@ This function takes input from our sensor that has been passed from the ADC
;@ as the variable n and then determines the distace to the wall
;@ The max mesaurement of distance for the sensor is 800mm so if the value given
;@ from the the ADC is less than 2552, return 800

.text
.global main

;@ I am assuming that the number from the ADC is unsigned!  Probably this is
;@ correct because we won't have a 'negative' distance
main:   .asmfunc
        MOV R0,#2551
        BL  convert
        .endasmfunc

convert:.asmfunc
        ;@ we assume that n was passed in as R0
        CMP R0, #2552
        ;@ since this is unsigned
        BCS invalid
        SUB R2, R0, #1058
invalid:
        MOV R0,#800
        BX LR
        .endasmfunc
