;@ The goal of this module is to implement the function: D=1195172 / (n - 1058)
;@ This function takes input from our sensor that has been passed from the ADC
;@ as the variable n and then determines the distace to the wall
;@ The max mesaurement of distance for the sensor is 800mm so if the value given
;@ from the the ADC is less than 2552, return 800

        .thumb
        .data
        .text
        .align  2

        .global main

main:   .asmfunc
        LDR R0,TEST
        BL convert
        BX LR
        .endasmfunc

convert:.asmfunc
        ;@ we assume that n was passed in as R0
        LDR R1,Cc
        ; 2552
        CMP R0,R1

        BLT invalid
        ; bif R0 < R1

        LDR R2,Cb
        ; 1058
        SUBS R4,R0,R2
        ; R4 = n - 1058

        LDR R3,Ca
        ; 1195172

        SDIV R0,R3,R4
        ; 1195172 / (n - 1058)

        BX LR
invalid
        LDR R0,DEFAULT
        BX LR

        .endasmfunc
;@All of my constants
Ca      .field  1195172,32
Cb      .field  1058,   32
Cc      .field  2552,   32
TEST    .field  2551,   32
DEFAULT .field  800,    32

        .end
