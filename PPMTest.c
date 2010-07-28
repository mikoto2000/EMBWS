#ifndef PPMTEST_H
#define PPMTEST_H
#include "PPMTest.h"
#endif

#ifndef DESKTOP_PATH
#define DESKTOP_PATH "/psp/desktop/"
#endif

void mainLoop(struct CHWS *chws, unsigned char *bg){
	//ダブルバッファリング用バッファ
	unsigned char *buf = (unsigned char*)malloc(sizeof(unsigned char) * FB_WIDTH * FB_HEIGHT * FB_BYTES_PER_PIXEL);

	//フレームバッファに背景を書き込む
	memcpy(chws->fb, bg, sizeof(unsigned char) * FB_WIDTH * FB_HEIGHT * FB_BYTES_PER_PIXEL);

	struct CHTS *ts = chws->ts;

	int ledbytes = 0;
	int n = 0;
	chws->clickStat = FREE;
	struct CHWS_Object *target = NULL;
	while(true){
		//フレームバッファに送る前に画像を合成する	
		//背景描画
		memcpy(buf, bg, sizeof(unsigned char)* FB_WIDTH * FB_HEIGHT * FB_BYTES_PER_PIXEL);

		chws->clickStat = CHWS_getClickStat(chws);
		if(chws->clickStat == PUSH){
			system("echo 'h*' > /dev/ttyUSB0");
			target = CHWS_hitObject(chws);
			if(target != NULL){
				target->process(chws, target);
			}
		}

		if(chws->clickStat == HOLD){
			if(target != NULL){
				target->process(chws, target);
			}
		}

		if(chws->clickStat == RELEASE){
			system("echo 'l*' > /dev/ttyUSB0");
			if(target != NULL){
				target->process(chws, target);
			}
		}

		//オブジェクト描画
		int i;
		for(i = 0; i < CHWS_OBJECT_NUM && chws->objects[i] != NULL; i++){
			CHFB_printImage(buf, (chws->objects)[i]->icon, (chws->objects)[i]->x, (chws->objects)[i]->y);
		}

		//フレームバッファに書き込む
		memcpy(chws->fb, buf, sizeof(unsigned char)* FB_WIDTH * FB_HEIGHT * FB_BYTES_PER_PIXEL);

		usleep(75000);
	}
	free(buf);
}

int main(int argc, char* argv[]){

	FILE *inputfile;

	//背景ファイルのデータ抽出
	inputfile = fopen("/psp/programming/c/img/desktop.ppm", "rb");
	struct PPM ppm;
	PPM_createPPM(&ppm, inputfile);
	fclose(inputfile);

	//イメージの抽出bg元ファイルはRGB888なので、RGB565に変換
	unsigned char *mainbg = (unsigned char*)malloc(sizeof(unsigned char) * ppm.width * ppm.height * FB_BYTES_PER_PIXEL);
	CHFB_convertImage888to565(mainbg, &ppm);

	//背景ファイルのデータ抽出
	inputfile = fopen("/psp/programming/c/img/setupping.ppm", "rb");
	PPM_createPPM(&ppm, inputfile);
	fclose(inputfile);

	//イメージの抽出bg元ファイルはRGB888なので、RGB565に変換
	unsigned char *startupbg = (unsigned char*)malloc(sizeof(unsigned char) * ppm.width * ppm.height * FB_BYTES_PER_PIXEL);
	CHFB_convertImage888to565(startupbg, &ppm);

	struct CHWS *chws = CHWS_create(startupbg);

	mainLoop(chws, mainbg);

	CHTS_close(chws->ts);

	//画像プール廃棄
	CHPool_trashPool(chws->pool);

	//後始末
	free(mainbg);
	free(startupbg);
}
