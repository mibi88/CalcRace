#ifndef IMAGE_H
#define IMAGE_H

#include "canvas.h"
#include <stdio.h>

void draw_image(int sx, int sy, const unsigned char *image_data, const int w, const int h);
void draw_image_del_color(int sx, int sy, const unsigned char *image_data, const int w, const int h, const int r, const int g, const int b, const int a);

#endif
