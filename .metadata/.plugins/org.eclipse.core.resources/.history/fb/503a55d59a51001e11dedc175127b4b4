/*
 * nrTransFunc.c
 *
 *  Created on: Sep 3, 2023
 *      Author: asidh
 */

#define ARM_MATH_CM4
#include "arm_math.h"
#include "main.h"

void trans_func(float *x, float *omega, float *phi){
    float x_o = 0.5;   // Initialize guess to 1
	uint32_t len = 10;
	for(uint32_t i = 0; i < len; i++){
		x_o = x_o - (x_o*x_o - arm_cos_f32((*omega)*(x_o) + (*phi))) / (2*x_o + (*omega) * arm_sin_f32((*omega)*(x_o) + (*phi)));
	}
	(*x) = x_o;
}

