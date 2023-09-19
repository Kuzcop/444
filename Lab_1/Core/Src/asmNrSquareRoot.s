/*
 * newtonRaphson.s
 *
 *  Created on: Sep 3, 2023
 *      Author: asidh
 */

// unified indicates that we're using a mix of different ARM instructions,
// e.g., 16-bit Thumb and 32-bit ARM instructions may be present (and are)
.syntax unified

// .global exports the label asmMax, which is expected by lab1math.h
.global asmSquareRoot

// .section marks a new section in assembly. .text identifies it as source code;
// .rodata marks it as read-only, setting it to go in FLASH, not SRAM
.section .text.rodata

/**
 * void asmSquareRoot(float *x);
 *
 * R0 = pointer to square
 */

 asmSquareRoot:
 	VLDR.f32 S0, [R0]
 	VCMP.f32 S0, #0.0
 	VMRS APSR_nzvc, FPSCR
 	ITE GT
 	VSQRTGT.f32 S0, S0
 	VMOVLE.f32 S0, #-1
 	VSTR.f32 S0, [R0]
 	BX LR

