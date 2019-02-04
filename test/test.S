        .data
val:    .word   25565
        .text
        .global _start
_start:
        ldr r0,=val
        b _start

