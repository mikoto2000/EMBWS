#ifndef CHWS_H
#define CHWS_H
#include "CHWS.h"
#endif

struct CHWS_Object* CHWS_Object_create(int x, int y, int width, int height, struct PPM *icon, void* process){
	struct CHWS_Object *newObj = malloc(sizeof(struct CHWS_Object));
	newObj->x=x;
	newObj->y=y;
	newObj->width=width;
	newObj->height=height;
	newObj->icon=icon;
	newObj->process=process;

	return newObj;
}

struct CHWS_Object** CHWS_Objects_create(struct CHWS *chws){
	//オブジェクトの配列
	struct CHWS_Object **objects = malloc(sizeof(struct CHWS_Object*) * CHWS_OBJECT_NUM);
	//printf("%d\n",sizeof(struct CHWS_Object*) * CHWS_OBJECT_NUM);
	objects[0] = CHWS_Object_create(40,50,60,60,&(chws->pool[LED]),GLED0_toggle); 
	objects[1] = CHWS_Object_create(100,50,60,60,&(chws->pool[LED]),GLED1_toggle);
	objects[2] = CHWS_Object_create(160,50,60,60,&(chws->pool[LED]),GLED2_toggle);
	objects[3] = CHWS_Object_create(220,50,60,60,&(chws->pool[LED]),GLED3_toggle);
	objects[4] = CHWS_Object_create(130,135,60,60,&(chws->pool[MOTER]),GMOTER_setSpeed);
	objects[5] = CHWS_Object_create(190,135,60,60,&(chws->pool[NOMAL_PLUS]),test);
	objects[6] = CHWS_Object_create(70,135,60,60,&(chws->pool[NOMAL_MINUS]),test);
	objects[7] = CHWS_Object_create(270,135,60,100,&(chws->pool[BAR]),test);
	objects[8] = CHWS_Object_create(270,183,60,60,&(chws->pool[LED]),test);
	objects[9] = CHWS_Object_create(31,223,60,60,&(chws->pool[NOMAL_START]),test);
	objects[10] = NULL;

	return objects;
}

struct CHWS* CHWS_create(unsigned char *bg){
	struct CHWS *chws = malloc(sizeof(struct CHWS));

	//フレームバッファを開く
	unsigned char *fb = CHFB_getFB();

	//フレームバッファに背景を書き込む
	memcpy(fb, bg, sizeof(unsigned char) * FB_WIDTH * FB_HEIGHT * FB_BYTES_PER_PIXEL);

	//画像プールの作成
	struct PPM *pool = CHPool_createPool();

	//タッチスクリーン情報取得
	struct CHTS *ts = CHTS_open();

	chws->ts=ts;
	chws->fb=fb;
	chws->pool=pool;
	chws->objects = CHWS_Objects_create(chws);
	chws->gainer = GAINER_create();

	//タッチスクリーンポーリング処理用スレッドの生成と実行
	pthread_t t_reader;
	pthread_create(&t_reader, NULL, CHTS_read, (void *)ts);

	//押し続け、離し続け判断用配列の初期化
	chws->clicking[0] = false;
	chws->clicking[1] = false;

	return chws;
}

enum CLICK_STAT CHWS_getClickStat(struct CHWS *chws){
	//TS情報の更新
	chws->clicking[0] = chws->clicking[1];
	chws->clicking[1] = chws->ts->click;

	enum CLICK_STAT cs = FREE;

	//タッチされた 
	if(chws->clicking[0] == false && chws->clicking[1] == true){
		cs = PUSH;
		return cs;
	}
	//タッチされ続けている
	if(chws->clicking[0] == true && chws->clicking[1] == true){
		cs = HOLD;
		return cs;
	}
	//離された
	if(chws->clicking[0] == true && chws->clicking[1] == false){
		cs = RELEASE;
		return cs;
	}
	//離され続けている
	if(chws->clicking[0] == false && chws->clicking[1] == false){
		cs = FREE;
		return cs;
	}


}

struct CHWS_Object* CHWS_hitObject(struct CHWS *chws){
	struct CHWS_Object **objects = chws->objects;
	int tsx,tsy,objx,objy,objw,objh;
	tsx = chws->ts->x;
	tsy = chws->ts->y;
	int i;
	for(i = 0; i < CHWS_OBJECT_NUM && objects[i] != NULL; i++){
		objx = chws->objects[i]->x;
		objy = chws->objects[i]->y;
		objw = chws->objects[i]->width;
		objh = chws->objects[i]->height;

		if(tsx <= objx + objw / 2 && tsx >= objx - objw /2 &&
				tsy <= objy + objh / 2 && tsy >= objy - objh / 2){
			return chws->objects[i];
		}
	}
	return NULL;
}

void* test(struct CHWS *chws, struct CHWS_Object *object){
	object->x = chws->ts->x;
	object->y = chws->ts->y;
}
