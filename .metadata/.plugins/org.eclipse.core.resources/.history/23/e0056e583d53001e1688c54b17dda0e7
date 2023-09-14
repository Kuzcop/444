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
    float x_o = 0.1;   // Initialize guess to 1
    float x_1 = 0.5;
    float f_prime = -1;
    float tolerance = 0.000001;
    float epsilon = 0.1;
    uint32_t iter = 0;
	while(1){
		f_prime = 2*x_o + (*omega) * arm_sin_f32((*omega)*(x_o) + (*phi));
		x_1 = x_o - (x_o*x_o - arm_cos_f32((*omega)*(x_o) + (*phi))) / f_prime;
		if (fabs(x_1 - x_o) <= tolerance || fabs(f_prime) < epsilon){
			(*x) = x_o;
			break;
		}
		x_o = x_1;
		iter++;
	}

}

