#ifndef TEXT_H
#define TEXT_H

#include "../lib/image.h"

extern const unsigned char n0_data, n1_data, n2_data, n3_data, n4_data, n5_data, n6_data, n7_data, n8_data, n9_data, multiply_data, colon_data;

void dtext(unsigned char *text, int sx, int sy, int len);
int text_size_y(unsigned char* text, int len);

#endif
