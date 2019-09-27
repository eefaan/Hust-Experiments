/*
 * mini_crt0.S
 *
 * Set up a basic runtime environment
*/
/*
Copyright (c) 2015, Imagination Technologies LLC and Imagination Technologies
Limited.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions in binary form must be built to execute on machines
   implementing the MIPS32(R), MIPS64 and/or microMIPS instruction set
   architectures.

2. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

3. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

4. Neither the name of Imagination Technologies LLC, Imagination Technologies Limited
   nor the names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL IMAGINATION TECHNOLOGIES LLC OR IMAGINATION
TECHNOLOGIES LIMITED BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <mips/regdef.h>
#include "boot.h"
#include <mips/m32c0.h>


	.set	noreorder           # Don't allow the assembler to reorder instructions.
	.set	noat                # Don't allow the assembler to use r1(at) for synthetic instr.

/**************************************************************************************
**************************************************************************************/
LEAF(__exception_entry)

	move	k1,sp
	addiu	sp, sp, -176
	#sw	at, 16(sp)
	sw	v0, 20(sp)
	sw	v1, 24(sp)
	sw	a0, 28(sp)
	sw	a1, 32(sp)
	sw	a2, 36(sp)
	sw	a3, 40(sp)
	sw	t0, 44(sp)
	sw	t1, 48(sp)
	sw	t2, 52(sp)
	sw	t3, 56(sp)
	sw	t4, 60(sp)
	sw	t5, 64(sp)
	sw	t6, 68(sp)
	sw	t7, 72(sp)
	sw	s0, 76(sp)
	sw	s1, 80(sp)
	sw	s2, 84(sp)
	sw	s3, 88(sp)
	sw	s4, 92(sp)
	sw	s5, 96(sp)
	sw	s6, 100(sp)
	sw	s7, 104(sp)
	sw	t8, 108(sp)
	sw	t9, 112(sp)
	sw	k0, 116(sp)
	sw	gp, 124(sp)
	sw	k1, 128(sp)
	sw	s8, 132(sp)
	sw	ra, 136(sp)
	sw	zero,156(sp)
	mfhi	t1
	mflo	t2
	sw	t1,148(sp)
	sw	t2,152(sp)
	mfc0	ra,C0_EPC
	mfc0	s3,C0_CAUSE
	sw	ra,140(sp)
	mfc0	t1,C0_BADVADDR
	sw	t1,144(sp)
	sw	s3,164(sp)
	move	t3,zero
	move	t4,zero
	mfc0	t1,C0_CONFIG3
	ext	t2,t1,0x1b,0x1
	beqz	t2, 1f
	mfc0	t3,$8,2
1:
	ext	t1,t1,0x1a,0x1
	beqz	t1, 2f
	mfc0	t4,$8,1
2:
	sw	t3,172(sp)
	sw	t4,168(sp)
	move	a0,sp
	mfc0	s5,C0_STATUS
	lui	t1,0x0
	addiu	t1,t1,-3
	and	s5,s5,t1
	mtc0	s5,C0_STATUS
	sw	s5,160(sp)

	la  t9, _mips_handle_irq
	andi	a1,s3,0x7c
	addiu	a0,a0,16
	srl	a1,a1,0x2
	jalr  t9
	nop



	lw	t1,148(sp)
	lw	t2,152(sp)
	mthi	t1
	mtlo	t2
	lw	s5,160(sp)
	mtc0	s5,C0_STATUS
	lw	s6,140(sp)
	mtc0	s6,C0_EPC
	#lw	at,16(sp)
	lw	v0,20(sp)
	lw	v1,24(sp)
	lw	a0,28(sp)
	lw	a1,32(sp)
	lw	a2,36(sp)
	lw	a3,40(sp)
	lw	t0,44(sp)
	lw	t1,48(sp)
	lw	t2,52(sp)
	lw	t3,56(sp)
	lw	t4,60(sp)
	lw	t5,64(sp)
	lw	t6,68(sp)
	lw	t7,72(sp)
	lw	s0,76(sp)
	lw	s1,80(sp)
	lw	s2,84(sp)
	lw	s3,88(sp)
	lw	s4,92(sp)
	lw	s5,96(sp)
	lw	s6,100(sp)
	lw	s7,104(sp)
	lw	t8,108(sp)
	lw	t9,112(sp)
	lw	k0,116(sp)
	lw	k1,120(sp)
	lw	gp,124(sp)
	lw	s8,132(sp)
	lw	ra,136(sp)
	lw	sp,128(sp)
	eret
	nop


END(__exception_entry)
