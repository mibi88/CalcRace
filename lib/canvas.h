#ifndef CANVAS_H
#define CANVAS_H

#include <emscripten.h>
#include <stdbool.h>

void init_canvas(int width, int height, char *canvasname);
void put_pixel(int x, int y, int r, int g, int b, int a);
void update(void);
void clear(void);
void init_getkey(void);
bool getkey(int key);
int getwidth(void);
int getheight(void);

#endif
