	.syntax unified
	.cpu cortex-m4
	.thumb

	.section .text

/* Reset vector. */
	.global Reset_Handler
	.type  Reset_Handler, %function
Reset_Handler:
	/* Copy .data from FLASH to RAM */
	ldr  r0, =_data
	ldr  r1, =_edata
	ldr  r2, =_etext
	cmp  r0, r1
	beq  nodata
	subs r2, r2, #4
dataloop:
	ldr  r3, [r2, #4]!
	str  r3, [r0], #4
	cmp  r1, r0
	bne  dataloop
nodata:
	/* Zero .bss */
	ldr  r0, =_bss_start
	ldr  r1, =_bss_end
	cmp  r0, r1
	beq  nobss
	movs r3, #0
bssloop:
	str  r3, [r0], #4
	cmp  r1, r0
	bne  bssloop
nobss:
	/* Jump to main() */
	bl   main
	/*  If main() returns, endless loop */
loop:
	b    loop
	.size	Reset_Handler, .-Reset_Handler

/* Minimal interrupt vector table. Only the stack pointer and reset handler */
	.section .isr_vector
	.global __Vectors
__Vectors:
	.word  _stack_top
	.word  Reset_Handler
