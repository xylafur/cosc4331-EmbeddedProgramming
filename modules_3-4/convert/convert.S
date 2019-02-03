	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"convert.c"
	.global	__aeabi_uidiv
	.text
	.align	2
	.global	convert
	.syntax unified
	.arm
	.fpu softvfp
	.type	convert, %function
convert:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	ldr	r3, [fp, #-16]
	ldr	r2, .L4
	cmp	r3, r2
	bhi	.L2
	mov	r3, #800
	b	.L3
.L2:
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1056
	sub	r3, r3, #2
	str	r3, [fp, #-8]
	ldr	r1, [fp, #-8]
	ldr	r0, .L4+4
	bl	__aeabi_uidiv
	mov	r3, r0
.L3:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L5:
	.align	2
.L4:
	.word	2551
	.word	1195172
	.size	convert, .-convert
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	ldr	r3, .L8
	str	r3, [fp, #-8]
	ldr	r0, [fp, #-8]
	bl	convert
	str	r0, [fp, #-12]
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L9:
	.align	2
.L8:
	.word	2552
	.size	main, .-main
	.ident	"GCC: (Fedora 7.1.0-5.fc27) 7.1.0"
