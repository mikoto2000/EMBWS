#ifndef GAINER_H
#define GAINER_H
#include "GAINER.h"
#endif

struct GAINER* GAINER_create(){
	//われらがGainer君の初期化
	system("echo 'Q*' > /dev/ttyUSB0");
	sleep(1);
	system("echo 'KONFIGURATION_1*' > /dev/ttyUSB0");
	sleep(1);
	system("echo 'D0000*' > /dev/ttyUSB0");
	sleep(1);
	system("echo 'AFF000000*' > /dev/ttyUSB0");

	struct GAINER *gainer = malloc(sizeof(struct GAINER));
	return gainer;
}

void GLED0_toggle(struct CHWS *chws, struct CHWS_Object *object){
	if(chws->clickStat == PUSH){
		struct GAINER *gainer = chws->gainer;
		if(gainer->led[0] != true){
			system("echo 'H0*' > /dev/ttyUSB0");
			gainer->led[0] = true;
		}else{
			system("echo 'L0*' > /dev/ttyUSB0");
			gainer->led[0] = false;
		}	
	}
}

void GLED1_toggle(struct CHWS *chws, struct CHWS_Object *object){
	if(chws->clickStat == PUSH){
		struct GAINER *gainer = chws->gainer;
		if(gainer->led[1] != true){
			system("echo 'H1*' > /dev/ttyUSB0");
			gainer->led[1] = true;
		}else{
			system("echo 'L1*' > /dev/ttyUSB0");
			gainer->led[1] = false;
		}
	}
}

void GLED2_toggle(struct CHWS *chws, struct CHWS_Object *object){
	if(chws->clickStat == PUSH){
		struct GAINER *gainer = chws->gainer;
		if(gainer->led[2] != true){
			system("echo 'H2*' > /dev/ttyUSB0");
			gainer->led[2] = true;
		}else{
			system("echo 'L2*' > /dev/ttyUSB0");
			gainer->led[2] = false;
		}
	}
}

void GLED3_toggle(struct CHWS *chws, struct CHWS_Object *object){
	if(chws->clickStat == PUSH){
		struct GAINER *gainer = chws->gainer;
		if(gainer->led[3] != true){
			system("echo 'H3*' > /dev/ttyUSB0");
			gainer->led[3] = true;
		}else{
			system("echo 'L3*' > /dev/ttyUSB0");
			gainer->led[3] = false;
		}
	}
}

void GMOTER_setSpeed(struct CHWS *chws, struct CHWS_Object *object){
	object->y = chws->ts->y;
	int y = object->y;
	char command[255];
	sprintf(command, "echo 'AFF00%2X00*' > /dev/ttyUSB0", y);
	system(command);
}
