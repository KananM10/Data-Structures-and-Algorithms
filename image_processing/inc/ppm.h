#ifndef __PPM_H__
#define __PPM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"

#define PGM_MAX 300

typedef struct ppm{
	FILE *ppmfile;
	int width, height, nbpixels;
	color *pixels;
}ppm;

void PPM_check(ppm p, char *message);
ppm PPM_new(char *ppmfilepath);
int  PPM_nbPixels(ppm p);
color* PPM_pixels(ppm p);
void PPM_save(ppm p, color *image, char *outputfile);

#endif