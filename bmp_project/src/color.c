#include "color.h"

//----------------------------------------------------------------------------------------------------

RGB newColor(){
	RGB newColor;
	newColor.r = 0;
	newColor.g = 0;
	newColor.b = 0;

	return newColor; //initial color is black
}

//----------------------------------------------------------------------------------------------------

RGB getColor(RGB Color, const char* hexValue){
  sscanf(hexValue, "%02x%02x%02x", &Color.r, &Color.g, &Color.b); //getting a color from string
  return Color; 
}

//----------------------------------------------------------------------------------------------------
