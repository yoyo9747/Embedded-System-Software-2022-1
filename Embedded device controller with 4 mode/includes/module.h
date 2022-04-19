#ifndef __MODULE__
#define __MODULE__
#include <time.h>

#define BACK 158
#define VOL_P 115
#define VOL_M 114

/////////counterMode
void counterMode(int sw,int change);
int change_radix(int radix);
int update_value(int sw,int radix);
/////////clockMode
void clockMode(int sw,int change);
/////////texteditorMode
void texteditorMode(int sw[10],int change);
void write_text(int offset,char c,char *text);
/////////drawboardMode
void drawboardMode(int sw[10],int change);
#endif
