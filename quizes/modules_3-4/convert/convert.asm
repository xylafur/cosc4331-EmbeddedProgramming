;@ The goal of this module is to implement the function: D=1195172 / (n - 1058)
;@ This function takes input from our sensor that has been passed from the ADC
;@ as the variable n and then determines the distace to the wall
;@ The max mesaurement of distance for the sensor is 800mm so if the value given
;@ from the the ADC is less than 2552, return 800


        .data
;@All of my constants
.set    C1,     1195172
.set    C2,     1058
.set    C3,     2552
.set    TEST,   2551
.set    DEFAULT,800

        .text
        .align
_start: .global _start
        .global main
        .global convert
        b main

        .type main, %function
main:
        LDR R0,=TEST
        BL convert
        BX LR

        .type convert, %function
convert:
        ;@ we assume that n was passed in as R0
        LDR R1, =C3                         ;@ 2552
        CMP R0, R1

        BLT invalid                         ;@ bif R0 < R1

        LDR R2, =C2                         ;@ 1058
        SUB R4, R0, R2                      ;@ R4 = n - 1058

        LDR R3, =C1                         ;@ 1195172

        SDIV R0, R3, R4                     ;@ 1195172 / (n - 1058)

        BX LR

invalid:
        LDR R0, =DEFAULT
        BX LR
