	.text
	.extern pCurrentPCBStack
	.extern nextProcess
	.globl StoreContext
	.globl LoadContext
	.globl SaveRegs
	.globl SaveReg
	.globl SContext
	.globl Switch



.macro SAVE_CONTEXT

	/* Switch to use the EL0 stack pointer. */
	MSR 	SPSEL, #0

	/* Save the entire context. */ /* save x0-x28 onto stack */
	STP 	X0, X1, [SP, #-0x10]!
	STP 	X2, X3, [SP, #-0x10]!
	STP 	X4, X5, [SP, #-0x10]!
	STP 	X6, X7, [SP, #-0x10]!
	STP 	X8, X9, [SP, #-0x10]!
	STP 	X10, X11, [SP, #-0x10]!
	STP 	X12, X13, [SP, #-0x10]!
	STP 	X14, X15, [SP, #-0x10]!
	STP 	X16, X17, [SP, #-0x10]!
	STP 	X18, X19, [SP, #-0x10]!
	STP 	X20, X21, [SP, #-0x10]!
	STP 	X22, X23, [SP, #-0x10]!
	STP 	X24, X25, [SP, #-0x10]!
	STP 	X26, X27, [SP, #-0x10]!
	str 	X28, [SP, #-0x10]!

	BL nextProcess

	LDR 	X28, [SP], #0x10  /* restore x0-x28 from stack */
	LDP 	X26, X27, [SP], #0x10
	LDP 	X24, X25, [SP], #0x10
	LDP 	X22, X23, [SP], #0x10
	LDP 	X20, X21, [SP], #0x10
	LDP 	X18, X19, [SP], #0x10
	LDP 	X16, X17, [SP], #0x10
	LDP 	X14, X15, [SP], #0x10
	LDP 	X12, X13, [SP], #0x10
	LDP 	X10, X11, [SP], #0x10
	LDP 	X8, X9, [SP], #0x10
	LDP 	X6, X7, [SP], #0x10
	LDP 	X4, X5, [SP], #0x10
	LDP 	X2, X3, [SP], #0x10
	LDP 	X0, X1, [SP], #0x10


	/* Switch to use the ELx stack pointer. */
	MSR 	SPSEL, #1

	.endm


.macro RESTORE_CONTEXT

	/* Switch to use the EL0 stack pointer. */
	MSR 	SPSEL, #1

	/* Set the SP to point to the stack of the task being restored. */
	LDR		X0, pCurrentPCBStack
	MOV		SP, X0

	LDR 	X28, [SP], #0x10  /* restore x0-x28 from stack */
	LDP 	X26, X27, [SP], #0x10
	LDP 	X24, X25, [SP], #0x10
	LDP 	X22, X23, [SP], #0x10
	LDP 	X20, X21, [SP], #0x10
	LDP 	X18, X19, [SP], #0x10
	LDP 	X16, X17, [SP], #0x10
	LDP 	X14, X15, [SP], #0x10
	LDP 	X12, X13, [SP], #0x10
	LDP 	X10, X11, [SP], #0x10
	LDP 	X8, X9, [SP], #0x10
	LDP 	X6, X7, [SP], #0x10
	LDP 	X4, X5, [SP], #0x10
	LDP 	X2, X3, [SP], #0x10
	LDP 	X0, X1, [SP], #0x10

	LDP	x29, x30, [sp], #16		/* restore elr_el1, spsr_el1 from stack */
	MSR	spsr_el1, x29
	MSR	elr_el1, x30

    LDP	x29, x30, [sp], #16		/* restore x29, x30 from stack */

	RET

	.endm


.type Switch, %function
Switch:
	RESTORE_CONTEXT
	ret

SaveRegs:
	mrs	x8, esr_el1
	mrs	x1, spsr_el1
	STP x8, x1, [x0], #16
	
	mov	x2, x30				/* lr */
	mrs	x3, elr_el1

	STP x2, x3, [x0], #16
	mrs	x4, sp_el0
	mov	x5, sp

	STP x4, x5, [x0], #16
	mrs	x6, far_el1
	str x6, [x0], #16
	ret

SaveReg:
	
	mrs	x1, spsr_el1
	STR x1, [x0], #16

	ret
	
StoreContext:				/* x0: pOldRegs */
	add	x0, x0, #8			
	stp	x16, x17, [x0], #16
	STP X18, X19, [x0], #16
	stp	x20, x21, [x0], #16
	stp	x22, x23, [x0], #16
	stp	x24, x25, [x0], #16
	stp	x26, x27, [x0], #16
	stp	x28, x29, [x0], #16
	mov	x2, sp
	stp	x30, x2, [x0], #16

	stp	d8, d9, [x0], #16
	stp	d10, d11, [x0], #16
	stp	d12, d13, [x0], #16
	stp	d14, d15, [x0], #16
	mrs	x2, fpcr
	mrs	x3, fpsr
	stp	x2, x3, [x0], #16

	ret

	
LoadContext:	
    ldr	x0, [x0], #8		/* parameter for CTask::TaskEntry() */
	ldp	x16, x17, [x0], #16
	ldp	x18, x19, [x0], #16
	ldp	x20, x21, [x0], #16
	ldp	x22, x23, [x0], #16
	ldp	x24, x25, [x0], #16
	ldp	x26, x27, [x0], #16
	ldp	x28, x29, [x0], #16
	ldp	x30, x2, [x0], #16
	mov	sp, x2

	ldp	d8, d9, [x0], #16
	ldp	d10, d11, [x0], #16
	ldp	d12, d13, [x0], #16
	ldp	d14, d15, [x0], #16
	ldp	x2, x3, [x0], #16
	msr	fpcr, x2
	msr	fpsr, x3

	ret

	
SContext:

	MSR 	SPSEL, #0

	add	x0, x0, #8			/* x0 is not saved */
	stp	x16, x17, [x0], #16
	stp	x18, x19, [x0], #16
	stp	x20, x21, [x0], #16
	stp	x22, x23, [x0], #16
	stp	x24, x25, [x0], #16
	stp	x26, x27, [x0], #16
	stp	x28, x29, [x0], #16
	mov	x2, sp
	stp	x30, x2, [x0], #16

	stp	d8, d9, [x0], #16
	stp	d10, d11, [x0], #16
	stp	d12, d13, [x0], #16
	stp	d14, d15, [x0], #16
	mrs	x2, fpcr
	mrs	x3, fpsr
	stp	x2, x3, [x0], #16

	MSR 	SPSEL, #1
	MSR 	SPSEL, #0

	ldr	x0, [x1], #8			/* parameter for CTask::TaskEntry() */
	ldp	x16, x17, [x1], #16
	ldp	x18, x19, [x1], #16
	ldp	x20, x21, [x1], #16
	ldp	x22, x23, [x1], #16
	ldp	x24, x25, [x1], #16
	ldp	x26, x27, [x1], #16
	ldp	x28, x29, [x1], #16
	ldp	x30, x2, [x1], #16
	mov	sp, x2

	ldp	d8, d9, [x1], #16
	ldp	d10, d11, [x1], #16
	ldp	d12, d13, [x1], #16
	ldp	d14, d15, [x1], #16
	ldp	x2, x3, [x1], #16
	msr	fpcr, x2
	msr	fpsr, x3

	MSR 	SPSEL, #1
	ERET

/* End */
