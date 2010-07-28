#ifndef PPM_H
#define PPM_H
#include "ppm.h"
#endif


void PPM_getType(char *type, FILE* fp){
	char buf;

	int i = 0;
	while((buf = fgetc(fp)) != '\n'){
		type[i] = buf;
		i++;
	}
	type[i] = '\0';

}
void PPM_getWidth(int *width, FILE* fp){
	char buf;
	char str[10];

	int i = 0;
	while((buf = fgetc(fp)) != ' '){
		str[i] = buf;
		i++;
	}
	str[i] = '\0';

	*width = atoi(str);
}

void PPM_getHeight(int *height, FILE* fp){
	char buf;
	char str[10];

	int i = 0;
	while((buf = fgetc(fp)) != '\n'){
		str[i] = buf;
		i++;
	}
	str[i] = '\0';

	*height = atoi(str);
}

void PPM_getSD(int *sd, FILE* fp){
	char buf;
	char str[10];

	int i = 0;
	while((buf = fgetc(fp)) != '\n'){
		str[i] = buf;
		i++;
	}
	str[i] = '\0';

	*sd = atoi(str);
}

void PPM_getHeaders(struct PPM *ppm, FILE *infile){
	char type[3];
	int width, height, sd;

	PPM_getType(type, infile);
	PPM_getWidth(&width, infile);
	PPM_getHeight(&height, infile);
	PPM_getSD(&sd, infile);
	
	ppm->type = type;
	ppm->width = width;
	ppm->height = height;
	ppm->sd = sd;

/*
	printf("type: %s\n", ppm->type);
	printf("width: %d\n", ppm->width);
	printf("height: %d\n", ppm->height);
	printf("sd: %d\n", ppm->sd);
*/
}

void PPM_getImg(struct PPM *ppm, FILE *fp){
	ppm->img = (unsigned char*)malloc(sizeof(unsigned char) * ppm->height * ppm->width * PPM_BYTES_PER_PIXEL);	

	unsigned char buf;
	
	int i = 0;
	
	for(i = 0; i < ppm->width * ppm->height * PPM_BYTES_PER_PIXEL; i++){
		buf = fgetc(fp);
		ppm->img[i] = buf;
	}
}

void PPM_createPPM(struct PPM *ppm, FILE *fp){
	PPM_getHeaders(ppm, fp);
	PPM_getImg(ppm, fp);
}

void PPM_trashPPM(struct PPM *ppm){
	free(ppm->img);
}


