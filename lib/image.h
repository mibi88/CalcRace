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

#ifndef IMAGE_H
#define IMAGE_H

#include <canvas.h>
#include <stdio.h>

/* Draws the image in image_data of width w and height h at sx, sy on screen. */
void draw_image(int sx, int sy, const unsigned char *image_data, const int w,
    const int h);

/* Draws a part at px, py with a width of w and a height of h of the image in
image_data of width w at sx, sy on screen. */
void draw_image_part(int sx, int sy, int px, int py,
    const unsigned char *image_data, const int w, const int h, const int rw);

/* Draws the image in image_data of width w and height h at sx, sy on screen.
Pixels with the color (r, g, b, a) are not drawn. */
void draw_image_del_color(int sx, int sy, const unsigned char *image_data,
    const int w, const int h, const int r, const int g, const int b,
    const int a);

/* Draws a part at px, py with a width of w and a height of h of the image in
image_data of width w at sx, sy on screen. Pixels with the color (r, g, b, a)
are not drawn. */
void draw_image_del_color_part(int sx, int sy, int px, int py,
    const unsigned char *image_data, const int w, const int h, const int r,
    const int g, const int b, const int a, const int rw);

#endif

