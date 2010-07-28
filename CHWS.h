#ifndef CHFB_H
#define CHFB_H
#include "CHFB.h"
#endif

#ifndef CHTS_H
#define CHTS_H
#include "CHTS.h"
#endif

#ifndef PPM_H
#define PPM_H
#include "ppm.h"
#endif

#ifndef CHPool_H
#define CHPool_H
#include "CHPool.h"
#endif

#define CHWS_OBJECT_NUM 20
enum CLICK_STAT {PUSH, HOLD, RELEASE, FREE};

struct CHWS {
	struct PPM *pool;
	struct CHTS *ts;
	unsigned char *fb;
	bool clicking[2];
	enum CLICK_STAT clickStat;
	struct CHWS_Object **objects;
	struct GAINER *gainer;
};

struct CHWS_Object {
	int x;
	int y;
	int width;
	int height;
	struct PPM *icon;
	void (*process)(struct CHWS *chws, struct CHWS_Object *object);
};

#ifndef GAINER_H
#define GAINER_H
#include "GAINER.h"
#endif

struct CHWS_Object* CHWS_Object_create(int x, int y, int width, int height, struct PPM *icon, void* process);
struct CHWS_Object** CHWS_Objects_create(struct CHWS *chws);
struct CHWS* CHWS_create(unsigned char *bg);
void* test(struct CHWS *chws, struct CHWS_Object *object);
enum CLICK_STAT CHWS_getClickStat(struct CHWS *chws);
struct CHWS_Object* CHWS_hitObject(struct CHWS *chws);
void* test(struct CHWS *chws, struct CHWS_Object *object);
