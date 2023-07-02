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

#ifndef CANVAS_H
#define CANVAS_H

#ifdef __EMSCRIPTEN__

/* Some key numbers for the HTML5 canvas. */
enum {
    KEY_UP    = 38,
    KEY_DOWN  = 40,
    KEY_LEFT  = 37,
    KEY_RIGHT = 39,
    KEY_SPACE = 32
};

#include <emscripten.h>

#else

#include <SDL2/SDL.h>

/* Some key numbers for the SDL 1.2 window. */
enum {
    KEY_UP    = SDL_SCANCODE_UP,
    KEY_DOWN  = SDL_SCANCODE_DOWN,
    KEY_LEFT  = SDL_SCANCODE_LEFT,
    KEY_RIGHT = SDL_SCANCODE_RIGHT,
    KEY_SPACE = SDL_SCANCODE_SPACE
};

#endif

/* Define the bool type. */
typedef enum {FALSE, TRUE} bool;

/* Initialize the drawing management. char is the name of the canvas to use,
width the width of the canvas and height for his height */
void init_canvas(int width, int height, char *canvasname);

/* Draw a pixel at x, y with colors (r, g, b, a). a should always be 255. */
void put_pixel(int x, int y, int r, int g, int b, int a);

/* Update the canvas/window. */
void update(void);

/* Clear the canvas/window. */
void clear(void);

/* Initialize the keyboard management. */
void init_getkey(void);

/* Check if the key key is pressed. */
bool getkey(int key);

/* Get the width of the canvas/window. */
int getwidth(void);

/* Get the height of the canvas/window. */
int getheight(void);

/* Get the ms elapsed since midnight or the 1st January 1970. */
int ms_time(void);

/* Initialize the mouse management. */
void init_mouse(void);

/* Initialize the click management. */
void init_click(void);

/* Initialize the touch move management. */
void init_touch_move(void);

/* Initialize the touch management. */
void init_touch(void);

/* Get the x coordinate of the mouse/press on the screen. */
int get_mouse_x(void);

/* Get the y coordinate of the mouse/press on the screen. */
int get_mouse_y(void);

/* If the user is clicking. */
bool is_clicked(void);

/* Call loop_function at fps frames per second. */
void main_loop(void (*loop_function)(void), int fps);

#endif

