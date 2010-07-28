#ifndef CHPool_H
#define CHPool_H
#include "CHPool.h"
#endif

#define SETUPPING 0
#define NOMAL_START 1
#define PUSHED_START 2
#define LED 3
#define NOMAL_PLUS 4
#define PUSHED_PLUS 5
#define NOMAL_MINUS 6
#define PUSHED_MINUS 7
#define MENU 8
#define MOTER 9
#define BAR 10

struct PPM* CHPool_createPool();
void CHPool_trashPool(struct PPM *pool);
