#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#ifndef PPM_H
#define PPM_H
#include "ppm.h"
#endif

#ifndef FB_WIDTH
#define FB_WIDTH 320
#endif

#ifndef FB_HEIGHT
#define FB_HEIGHT 240
#endif

#define FB_BYTES_PER_PIXEL 2

//#define FONT_TABLE fontdata_6x11
#define FONT_WIDTH 6
#define FONT_HEIGHT 11

#define ROWS ((FB_HEIGHT-FONT_HEIGHT+1)/FONT_HEIGHT)
#define COLS ((FB_WIDTH-FONT_WIDTH+1)/FONT_WIDTH)

#define PIXELS_PER_ROW (FONT_HEIGHT*FB_WIDTH)

void CHFB_RGB888toRGB565(unsigned char *destimg, unsigned char *srcimg);
void CHFB_convertImage888to565(unsigned char *dest, struct PPM *ppm);
	
unsigned char* CHFB_getFB();
void CHFB_printImage(unsigned char *base, struct PPM *ppm, int x, int y);
