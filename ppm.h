#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 200
#define PPM_BYTES_PER_PIXEL 3

struct PPM {
	char *type;
	int width;
	int height;
	int sd;
	unsigned char *img;
};

void PPM_getType(char *type, FILE* fp);
void PPM_getWidth(int *width, FILE* fp);
void PPM_getHeight(int *height, FILE* fp);
void PPM_getSD(int *sd, FILE* fp);
void PPM_getHeaders(struct PPM *ppm, FILE *infile);
void PPM_getImg(struct PPM *ppm, FILE *fp);
void PPM_createPPM(struct PPM *ppm, FILE *fp);
void PPM_trashPPM(struct PPM *ppm);
