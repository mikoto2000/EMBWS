#ifndef CHTS_H
#define CHTS_H
#include "CHTS.h"
#endif

void CHTS_getXY(struct CHTS *ts){
        int xx, yy;
        xx = ((ts->tsbuf[1] - 280) / ((4500 - 280) / 320)) + 20;
        yy = 240-30-((ts->tsbuf[2] - 410) / ((4850 -410) / 240));
        if(xx > 0 && yy > 0){
                ts->x = xx;
                ts->y = yy;
        }
        //printf("x:%d y:%d\n", ts->x, ts->y);
}

struct CHTS* CHTS_open(){

	struct CHTS *newTs = malloc(sizeof(struct CHTS));

	int fd;
	int n = 0;

	newTs->x = 0;
	newTs->y = 0;
	newTs->click = false;

	if (0 > (newTs->infile = open("/dev/ts", O_RDONLY)))
	{
		perror("file ");
		return;
	}
	newTs->tsbuf = (short *)malloc(4 * sizeof(short));

	return newTs;
}

void* CHTS_read(void *x){
	struct CHTS *ts = x;
	while(true){
		if(read(ts->infile, ts->tsbuf, 4 * sizeof(short)) < 0) { perror("read"); }
		CHTS_getXY(ts);

		if(ts->tsbuf[1]!=0 || ts->tsbuf[2]!=0){
			ts->click = true;
		}else if(ts->tsbuf[1]==0 && ts->tsbuf[2]==0){
			ts->click = false;
		}
	}
}

void CHTS_close(struct CHTS *ts){
	free(&(ts->tsbuf));
	free(ts);
}


