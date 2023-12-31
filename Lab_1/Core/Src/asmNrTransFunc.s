/*
 * asmNrTransFunc.s
 *
 *  Created on: Sep 3, 2023
 *      Author: asidh
 */

// unified indicates that we're using a mix of different ARM instructions,
// e.g., 16-bit Thumb and 32-bit ARM instructions may be present (and are)
.syntax unified

// .global exports the label asmMax, which is expected by lab1math.h
.global asmTransFunc

// .section marks a new section in assembly. .text identifies it as source code;
// .rodata marks it as read-only, setting it to go in FLASH, not SRAM
.section .text.rodata

/**
 * void asmTransFunc(float *x, float *omega, float *phi);
 *
 * R0 = pointer to result
 * R1 = pointer to omega parameter
 * R2 = pointer to phi parameter
 */
 asmTransFunc:
	VMOV.f32 S1, #0.5	// S1 is the initial guess
	VLDR.f32 S2, [R1]	// S2 is omega
	VLDR.f32 S3, [R2]	// S3 is phi
	MOV R1, #10			// R1 is the counter

Loop:
	CMP R1, #0
  	BEQ		done

  	VMOV.f32 S4, S3		//Copy phi into S4
  	VMLA.f32 S4, S1, S2 //S2*S1 + S4 -> S4, holds theta angle for both cos and sine

  	VMOV.f32 S0, S4	//Setup function call for cosine
  	PUSH {R0-R2, LR}
  	BL arm_cos_f32
  	POP {R0-R2, LR}
  	VMOV.f32 S5, S0 // S5 holds result of cos

  	VMOV.f32 S0, S4	//Setup function call for sine
 	PUSH {R0-R2, LR}
  	BL arm_sin_f32
 	POP {R0-R2, LR}
  	VMOV.f32 S6, S0	// S6 holds results of sin

	VNMLS.f32 S5, S1, S1 // S1*S1-S5, S5 holds the numerator

	VADD.f32 S4, S1, S1	//S4 holds 2*x_o
	VMLA.f32 S4, S2, S6 //S2*S6+S4, S4 holds the denominator

	VDIV.f32 S4, S5, S4 //Numerator/Denominator

	VSUB.f32 S1, S1, S4

	SUBS	R1, R1, #1	// Decrement counter

  	B Loop

done:
	VSTR.f32 S1, [R0]
	BX LR

