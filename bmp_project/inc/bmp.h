#ifndef __BMP_H__
#define __BMP_H__

//----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morse.h"
#include <stdint.h>
#include "color.h"

//----------------------------------------------------------------------------------------------------

typedef struct BMP {
    int w; //width
    int h; //height
    unsigned char *data; // pixels
    char *header; // header
    int size_of_header;
    int bytes_per_pixel; 
} BMP;

//----------------------------------------------------------------------------------------------------

BMP readBMP(char *fileName); //reads a file and returns BMP image
void writeBMP(BMP img, char *fileName); //just takes an image and writes it into file and if there is no file, it writes image into terminal
void changePixel(int x, int y, BMP* img, RGB color); //change the color of a pixel on a given coordinates


//----------------------------------------------------------------------------------------------------

#endif