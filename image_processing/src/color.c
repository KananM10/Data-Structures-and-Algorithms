#include "color.h"

//-----------------------------------------------------------
/*
 * this function returns 0 if input is less than 0 and 255 if input is more than 255, else returns the input
 */
static int clamp(int n){
  if (n < 0) return 0;
  if (n > MAX)  return 255;
  return n;
}

//-----------------------------------------------------------
/*
 * this function prints the colors attributes
 */
void C_print(color c){
  printf("(%d,%d,%d) \n",c.red,c.green,c.blue);
}

//-----------------------------------------------------------
/*
 * this function serves to create new color
 */
color C_new(int r, int g, int b){
  color cnew;
  cnew.red = clamp(r) ;
  cnew.green = clamp(g);
  cnew.blue = clamp(b);
  return cnew;
}

//-----------------------------------------------------------
/*
 * this function multiplies each attribute of color by some coefficient, without overpassing 255
 */
color C_multiply(color c, float coef){
    if(coef <= 0)
      return c;
    c.red = clamp(c.red * coef);
    c.green = clamp(c.green * coef);
    c.blue = clamp(c.blue * coef);
    return c;
}

//-----------------------------------------------------------
/*
 * this function serves to create negative color
 */
color C_negative(color c){
  c.red = MAX - c.red;
  c.blue = MAX - c.blue;
  c.green = MAX - c.green;
  return c;
}

//-----------------------------------------------------------
/*
 * this function creates permute color, by swapping the attributes
 */
color C_permute(color c){
  int reverse;
  reverse = c.red;
  c.red = c.green;
  c.green = c.blue;
  c.blue = reverse;
  return c;
}

//-----------------------------------------------------------
/*
 * this function returns the intensity of the color
 */
int C_intensity(color c){
  return (c.red + c.green + c.blue) / 3;
}

//-----------------------------------------------------------
/*
 *function that creates grayScale color, by assigning to each attribute the intensity of this color
 */
color C_grayScale(color c){
  int b = C_intensity(c);
  c.red = b;
  c.green = b;
  c.blue = b;
  return c;
}

//-----------------------------------------------------------
/*
 * this function returns 255 if color's intensity is higher than input, else 0
 */
int C_threshold(color c, int th){
  return (C_intensity(c) > th) ? 255 : 0;
}

//-----------------------------------------------------------
/*
 * this function checks if 2 colors are equal
 */
int C_areEqual(color c1, color c2){
  return (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue) ? 1 : 0;
}

//-----------------------------------------------------------
/*
 * this function creates new color, by summing first inputted color with second color multiplied by coeffiecient
 */
color C_addCoef(color c1, color c2, float coef){
  color cnew;
  cnew.red = c1.red + c2.red * coef;
  cnew.green = c1.green + c2.green * coef;
  cnew.blue = c1.blue + c2.blue * coef;
  return cnew;
}

//-----------------------------------------------------------
