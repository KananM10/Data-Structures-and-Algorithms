#include "image.h"

//-----------------------------------------------------------
/*
 * this function prints the image
 */
void I_print (color img[], int nb_pixels){
	for(int i=0; i<nb_pixels; i++){
		C_print(img[i]);
	}
}

//-----------------------------------------------------------
/*
 * this function uses C_multiply from color.c in each pixel of image
 */
void I_coef (color img[], int nb_pixels, float coef){
	for(int i=0; i<nb_pixels; i++){
		img[i] = C_multiply(img[i], coef);
	}
}

//-----------------------------------------------------------
/*
 * this function uses C_negative from color.c in each pixel of image
 */
void I_negative (color img[], int nb_pixels){
	for(int i=0; i<nb_pixels; i++){
		img[i] = C_negative(img[i]);
	}
}

//-----------------------------------------------------------
/*
 * this function uses C_permute from color.c in each pixel of image
 */
void I_permute (color img[], int nb_pixels){
	for(int i=0; i<nb_pixels; i++){
		img[i] = C_permute(img[i]);
	}
}

//-----------------------------------------------------------
/*
 * this function uses C_grayScale from color.c in each pixel of image
 */
void I_grayScale(color img[], int nb_pixels){
	for(int i=0; i<nb_pixels; i++){
		img[i] = C_grayScale(img[i]);
	}
}

//-----------------------------------------------------------
/*
 * this function uses C_threshold from color.c in each pixel of image
 * and if returned value is 255, it assignes white color to this pixel, else black color
 */
void I_threshold(color img[], int nb_pixels, int th){
	color white = C_new(255,255,255);
  	color black = C_new(0,0,0);
	for(int i=0; i<nb_pixels; i++){
		img[i] = C_threshold(img[i], th) == 255 ? white : black;
	}
}

//-----------------------------------------------------------
/*
 * this function assigns the color from img2 to img1 if the pixel in img1 is equal w/ the target
 */
void I_compose(color img1[], color img2[], int nb_pixels, color target){
	for(int i=0; i<nb_pixels; i++){
		if(C_areEqual(img1[i], target)){
			img1[i].red = img2[i].red;
			img1[i].green = img2[i].green;
			img1[i].blue = img2[i].blue;
		}
	}
}

//-----------------------------------------------------------
/*
 * this function adds the color to each pixel of the image
 */
void I_addColor(color img[], int nb_pixels, color c){
	for(int i=0; i<nb_pixels; i++){
		img[i].red += c.red;		
		img[i].green += c.green;		
		img[i].blue += c.blue;		
	}
}

//-----------------------------------------------------------
/*
 * this function create gradient image 
 */
void I_gradient(color img_in[], color img_out[], int nb_pixels){
	 color gray = C_new(127,127,127);
	 for(int i=0; i<nb_pixels; i++){
		if(i == 0){
			continue;
		}else{
			img_out[i].red = img_in[i].red - img_in[i-1].red; 
			img_out[i].green = img_in[i].green - img_in[i-1].green; 
			img_out[i].blue = img_in[i].blue - img_in[i-1].blue; 
		}
	}
	I_addColor(img_out, nb_pixels, gray);
}

//-----------------------------------------------------------
/*
 * this function creates an average color taking some pixels average from image
 */
color I_average(color img[], int nb_pixels, int fromhere, int nb_pixels_average){
	color cnew = C_new(0,0,0);
	int c=0;
	int a = fromhere + nb_pixels_average;
	if(a > nb_pixels)
		return cnew;
	for(int i=fromhere; i <= a; i++){
		cnew.red += img[i].red;
		cnew.green += img[i].green;
		cnew.blue += img[i].blue;
		c++;
	}

	cnew.red /= c;
	cnew.green /= c;
	cnew.blue /= c;
	return cnew;
}

//-----------------------------------------------------------
/*
 *this function creates motionBlur image by using I_average on each pixel of the image
 */
void I_motionBlur(color img[], color img_out[], int nb_pixels, int strength){
	 for(int i=0; i<nb_pixels; i++){
		img_out[i] = I_average(img,nb_pixels,i,strength);

		if(i >= nb_pixels - strength){
			img_out[i] = I_average(img,nb_pixels,i,nb_pixels-i);	
		}
	}
}

//-----------------------------------------------------------
