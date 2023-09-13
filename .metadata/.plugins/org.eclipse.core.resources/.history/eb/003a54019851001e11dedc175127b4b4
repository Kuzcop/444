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
    	uint32_t len = 10;
        for(uint32_t i = 0; i < len; i++){
            x_o = x_o - (x_o*x_o - (*x))/(2*x_o);
        }
        (*x) = x_o;
    }
}
