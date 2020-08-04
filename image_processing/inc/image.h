#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include "color.h"
#include <string.h>


void I_print (struct color img[], int nb_pixels);
void I_coef (struct color img[], int nb_pixels, float coef);
void I_negative (struct color img[], int nb_pixels);
void I_permute (struct color img[], int nb_pixels);
void I_grayScale(struct color img[], int nb_pixels);
void I_threshold(struct color img[], int nb_pixels, int th);
void I_compose(color img1[], color img2[], int nb_pixels, color target);
void I_addColor(color img[], int nb_pixels, color c);
void I_gradient(color img_in[], color img_out[], int nb_pixels);
color I_average(color img[], int nb_pixels, int fromhere, int nb_pixels_average);
void I_motionBlur(color img[], color img_out[], int nb_pixels, int strength);


#endif