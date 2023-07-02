/*
 * Draw easly on an HTML5 canvas.
 * This is a part of CalcRace
 * Copyright (C) 2022  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#include <image.h>

void draw_image(int sx, int sy, const unsigned char *image_data, const int w,
    const int h) {
    int x, y; /* x and y contain the position in the image. */
    int index; /* index contains the position in the image data of the pixel
    that will be drawn. */
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            /* I multiply (y * w + x by 4 because each color is made of 4
            unsigned chars for r, g, b and a). */
            index = (y * w + x) * 4;
            /* Put the pixel on the canvas. */
            put_pixel(sx+x, sy+y, (int)image_data[index],
                (int)image_data[index+1], (int)image_data[index+2],
                (int)image_data[index+3]);
        }
    }
}

void draw_image_part(int sx, int sy, int px, int py,
    const unsigned char *image_data, const int w, const int h, const int rw) {
    int x, y; /* x and y contain the position in the image part that will be
    drawn. */
    int ix = px, iy = py; /* ix and iy contain the position in the image. */
    int index; /* index contains the position in the image data of the pixel
    that will be drawn. */
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            index = (iy * rw + ix) * 4;
            /* Put the pixel on the canvas. */
            put_pixel(sx+x, sy+y, (int)image_data[index],
                (int)image_data[index+1], (int)image_data[index+2],
                (int)image_data[index+3]);
            ix++; /* Increment the x position in the image */
        }
        ix = px; /* Reset the x position in the image */
        iy++; /* Increment the y position in the image */
    }
}

void draw_image_del_color(int sx, int sy, const unsigned char *image_data,
    const int w, const int h, const int r, const int g, const int b,
    const int a) {
    int x, y; /* x and y contain the position in the image. */
    int index; /* index contains the position in the image data of the pixel
    that will be drawn. */
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            index = (y * w + x) * 4;
            if((int)image_data[index] != r || (int)image_data[index+1] != g ||
                (int)image_data[index+2] != b || (int)image_data[index+3] != a){
                /* If the pixel has not the color used for transparency. */
                /* Put the pixel on the canvas. */
                put_pixel(sx+x, sy+y, (int)image_data[index],
                    (int)image_data[index+1], (int)image_data[index+2],
                    (int)image_data[index+3]);
            }
        }
    }
}

void draw_image_del_color_part(int sx, int sy, int px, int py,
    const unsigned char *image_data, const int w, const int h, const int r,
    const int g, const int b, const int a, const int rw) {
    int x, y; /* x and y contain the position in the image part that will be
    drawn. */
    int ix=px, iy=py; /* ix and iy contain the position in the image. */
    int index; /* index contains the position in the image data of the pixel
    that will be drawn. */
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            index = (iy * rw + ix) * 4;
            if((int)image_data[index] != r || (int)image_data[index+1] != g ||
                (int)image_data[index+2] != b || (int)image_data[index+3] != a){
                /* If the pixel has not the color used for transparency. */
                /* Put the pixel on the canvas. */
                put_pixel(sx+x, sy+y, (int)image_data[index],
                    (int)image_data[index+1], (int)image_data[index+2],
                    (int)image_data[index+3]);
            }
            ix++; /* Increment the x position in the image */
        }
        ix=px; /* Reset the x position in the image */
        iy++; /* Increment the y position in the image */
    }
}

