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

#define s1_all_ones     s1   /* at Will hold 0xffffffff to simplify bit insertion of 1's. */
#define t1_temp_addr    t1   /* from address */
#define t3_temp_mark    t3   /* ending address */


	.set	noreorder           # Don't allow the assembler to reorder instructions.
	.set	noat                # Don't allow the assembler to use r1(at) for synthetic instr.

/**************************************************************************************
**************************************************************************************/
LEAF(_start)

    # Set the global pointer register address to _gp - value set in linker .ld file
    la      gp, _gp             # All share globals.

    # Set up the stack pointer register to STACK_BASE_ADDR defined in boot.h
    li      sp, STACK_BASE_ADDR # Set up stack base.

    # Make a stack frame; must be a multiple of 8-bytes
    addiu   sp, sp, -8

    # Preserve return address over the call to main
    sw      ra, 0(sp)

    li      s1_all_ones, 0xffffffff

zero_bss:
    la      t1_temp_addr, _fbss
    ins     t1_temp_addr, s1_all_ones, 29, 1
    la      t3_temp_mark, _end
    ins     t3_temp_mark, s1_all_ones, 29, 1
    beq     t1_temp_addr, t3_temp_mark, invoke_main
    nop
next_bss_word:
    sw      zero, 0(t1_temp_addr)
    addiu   t1_temp_addr, 4
    bne     t1_temp_addr, t3_temp_mark, next_bss_word
    nop

	
invoke_main:
	# Create interrupt control
	#
	lui		v0, 0xbfc0
	mtc0	v0, C0_EBASE		# set the interrupt base address at 0xbfc0_0000
	ehb
	
	mfc0	v0, C0_CAUSE
	la		v1, 0xff7fffff
	and		v0, v0, v1
	mtc0	v0, C0_CAUSE		# CauseIV = 0, interrupt offset at 0x180
	ehb
	
	mfc0	v0, C0_STATUS
	#la		v1, 0xffbffff9
	#and		v0, v0, v1			# StatusBEV = 0, StatusEXL = 0, StatusERL = 0
	la		v1, 0x1
	or		v0, v0, v1			# StatusIE = 1
	mtc0	v0, C0_STATUS		# set the Status register to enable interrupt
	ehb							
	
	mfc0	v0,C0_STATUS		# M_StatusEXL = 0
	lui		v1,0x0
	addiu	v1,v1,-3
	and		v0,v0,v1
	mtc0	v0,C0_STATUS
	ehb							
	

    la      t0, main
    # Create space for the o32 argument stack
    addiu   sp, sp, -16
    # Call main
    jalr    t0
    nop

    lw      ra, 0(sp)
    addiu   sp, sp, 8
    jr      ra
    nop
END(_start)

