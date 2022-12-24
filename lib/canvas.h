/*
 * Draw easly on an HTML5 canvas.
 * This is a part of MathRace
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

#ifndef CANVAS_H
#define CANVAS_H

#define KEY_UP 38
#define KEY_DOWN 40
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define KEY_SPACE 32

#include <emscripten.h>
typedef enum {FALSE, TRUE} bool;

void init_canvas(int width, int height, char *canvasname);
void put_pixel(int x, int y, int r, int g, int b, int a);
void update(void);
void clear(void);
void init_getkey(void);
bool getkey(int key);
int getwidth(void);
int getheight(void);
int ms_time(void);
void init_mouse(void);
void init_click(void);
void init_touch_move(void);
void init_touch(void);
int get_mouse_x(void);
int get_mouse_y(void);
bool is_clicked(void);
void main_loop(void (*loop_function)(void), int fps);

#endif
