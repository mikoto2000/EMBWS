#ifndef PPM_H
#define PPM_H
#include "ppm.h"
#endif

#define CHPOOL_POOLSIZE 20

struct PPM* CHPool_createPool(){
	FILE *infile;
	int i = 0;

	struct PPM *newPool = malloc(CHPOOL_POOLSIZE * sizeof(struct PPM));

	//PPMファイルを開いてメモリに展開する
	//アイコン
	infile = fopen("/psp/programming/c/img/LED.ppm", "rb");
	struct PPM LED;
	PPM_createPPM(&LED, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/startButton1.ppm", "rb");
	struct PPM startButton1;
	PPM_createPPM(&startButton1, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/startButton2.ppm", "rb");
	struct PPM startButton2;
	PPM_createPPM(&startButton2, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/menu.ppm", "rb");
	struct PPM menu;
	PPM_createPPM(&menu, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/plus1.ppm", "rb");
	struct PPM plus1;
	PPM_createPPM(&plus1, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/plus2.ppm", "rb");
	struct PPM plus2;
	PPM_createPPM(&plus2, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/minus1.ppm", "rb");
	struct PPM minus1;
	PPM_createPPM(&minus1, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/minus2.ppm", "rb");
	struct PPM minus2;
	PPM_createPPM(&minus2, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/setupping.ppm", "rb");
	struct PPM setupping;
	PPM_createPPM(&setupping, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/moter.ppm", "rb");
	struct PPM moter;
	PPM_createPPM(&moter, infile);
	fclose(infile);

	infile = fopen("/psp/programming/c/img/bar.ppm", "rb");
	struct PPM bar;
	PPM_createPPM(&bar, infile);
	fclose(infile);

	//アイコンプールの作成
	newPool[0] = setupping;
	newPool[1] = startButton1;
	newPool[2] = startButton2;
	newPool[3] = LED;
	newPool[4] = plus1;
	newPool[5] = plus2;
	newPool[6] = minus1;
	newPool[7] = minus2;
	newPool[8] = menu;
	newPool[9] = moter;
	newPool[10] = bar;

	return newPool;
}

void CHPool_trashPool(struct PPM *pool){
	free(pool);
}

