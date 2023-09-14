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
	VMOV.f32 S7, #0.5 	// S7 holds the intermediate solution
	VMOV.f32 S8, #10.0
	VMOV.f32 S9, #1.0	// will hold the tolerance value
	VLDR.f32 S2, [R1]	// S2 is omega
	VLDR.f32 S3, [R2]	// S3 is phi
	MOV R3, #6

Mult_iter:				// loop through dividing 1 by 10 six times
	CMP R3, #0
	BEQ Loop
	VDIV.f32 S9, S9, S8
	CMP R3, #5
	BLE Cont //check if on first pass of loop
	VMOV.f32 S10, S9	//save epsilon as 0.1
Cont:
	SUB R3, R3, #1
	B Mult_iter

Loop:

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

	VMOV.f32 S8, S4 // holds fprime
	VDIV.f32 S4, S5, S4 //Numerator/Denominator

	VSUB.f32 S7, S1, S4 //x1 = x0 - f/fprime
	VSUB.f32 S5, S7, S1 // x1 - x0
	VCMP.f32 S5, #0.0
	VMRS APSR_nzvc, FPSCR	// load the FP PSR to branch using FP conditions
	BGT tol

	VNEG.f32 S5, S5 //negate if difference is negative

tol:

	VCMP.f32 S5, S9 //compare difference to tolerance
	VMRS APSR_nzvc, FPSCR
	BLE done// if difference less than tolerance break


	VCMP.f32 S8, #0.0
	VMRS APSR_nzvc, FPSCR
	BGT eps
	VNEG.f32 S8, S8

eps:
	VCMP.f32 S8, S10
	VMRS APSR_nzvc, FPSCR
	BLE error //fpriome less than epsilon

	VMOV.f32 S1, S7
	B Loop

done:
	VSTR.f32 S1, [R0]
	BX LR

error:
	VSTR.f32 S9, [R0]
	BX LR
