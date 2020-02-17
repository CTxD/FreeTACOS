/*
 * taskswitch.S
 *
 * Circle - A C++ bare metal environment for Raspberry Pi
 * Copyright (C) 2015-2018  R. Stange <rsta2@o2online.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

	.text

	.globl	StoreContext
StoreContext:				/* x0: pOldRegs */
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

	ret

	.globl  LoadContext
LoadContext:	
    ldr	x0, [x0], #8			/* parameter for CTask::TaskEntry() */
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

/* End */
