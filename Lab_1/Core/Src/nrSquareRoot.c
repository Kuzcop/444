/*
 * newtonRaphson.c
 *
 *  Created on: Sep 2, 2023
 *      Author: asidh
 */
#include "main.h"

void square_root(float *x){
    if((*x) == 0.0){
    	return;
    }
    else if ((*x) < 0.0){
    	(*x) = -1;	// TODO
    }
    else{
    	float x_o = 1;   // Initialize guess to 1
    	float x_1 = 1;
    	float f_prime = -1;
    	float tolerance = 0.000001;
    	float epsilon = 0.1;
    	uint32_t iter = 0;
    	while(1){
    		f_prime = (2*x_o);
    		x_1 = x_o - (x_o*x_o - (*x))/f_prime;
    		if (fabs(x_1 - x_o) < tolerance){
    			(*x) = x_o;
    			break;
    		}

    		if(fabs(f_prime) < epsilon){
    			(*x) = tolerance;
    			break;
    		}

    		x_o = x_1;
    		iter++;
    	}
    }
}
