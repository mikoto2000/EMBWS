#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

struct CHTS {
        int infile;
        short *tsbuf;
        int x;
        int y;
        bool click;
};

void CHTS_getXY(struct CHTS *ts);
struct CHTS* CHTS_open();
void* CHTS_read(void *x);
void CHTS_close(struct CHTS *ts);
