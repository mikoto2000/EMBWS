#include <stdbool.h>
#include <stdlib.h>

#ifndef CHWS_H
#define CHWS_H
#include "CHWS.h"
#endif

struct GAINER {
	bool led[4];
};

struct GAINER* GAINER_create();
void GLED0_toggle(struct CHWS *chws, struct CHWS_Object *object);
void GLED1_toggle(struct CHWS *chws, struct CHWS_Object *object);
void GLED2_toggle(struct CHWS *chws, struct CHWS_Object *object);
void GLED3_toggle(struct CHWS *chws, struct CHWS_Object *object);
void GMOTER_setSpeed(struct CHWS *chws, struct CHWS_Object *object);
