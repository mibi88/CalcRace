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

#include <canvas.h>

#ifdef __EMSCRIPTEN__

EM_JS(void, init_canvas, (int width, int height, char *canvasname), {
    /* Get the canvas element. I threw everything in window to be able to share
    these variables with other functions of this file. */
    window.canvas = document.getElementById(UTF8ToString(canvasname));
    /* Set the width and the height of the canvas. */
    window.canvas.width = width;
    window.canvas.height = height;
    /* Get the canvas context and disable antialiasing for speed, because I
    don't need it in my retro looking game. */
    window.ctx = window.canvas.getContext("2d", antialias = 0);
    window.ctx.imageSmoothingEnabled = false;
    /* Created an image for double buffering. */
    window.image = window.ctx.createImageData(width, height);
    window.image.imageSmoothingEnabled = false;
    /* Got image.data to be able to manipulate pixels in it in put_pixel. */
    window.data = image.data;
})

EM_JS(void, put_pixel, (int x, int y, int r, int g, int b, int a), {
    if(x >= 0 && x < window.canvas.width && y >= 0 && y < window.canvas.height){
        var index = (y * window.canvas.width + x) * 4;
        data[index + 0] = r;
        data[index + 1] = g;
        data[index + 2] = b;
        data[index + 3] = a;
    }
})

EM_JS(void, update, (void), {
    /* Draw the image at 0, 0 on the canvas. */
    window.ctx.putImageData(window.image, 0, 0);
})

EM_JS(void, clear, (void), {
    /* Fill the image with white. */
    for(i=0;i!=window.canvas.width*window.canvas.height*4;i++){
        data[i] = 255;
    }
})

EM_JS(void, init_getkey, (void), {
    /* Create a literal to store for each keycode if the key is pressed or
    not. */
    kmap = {};
    /* If a key is held down. */
    document.onkeydown = function(e) {
        /* Set the element with this key code to true, because the key is held
        down. */
        kmap[e.keyCode] = true;
    };
    document.onkeyup = function(e) {
        /* Set the element with this key code to false, because the key is
        released. */
        kmap[e.keyCode] = false;
    };
})

EM_JS(bool, getkey, (int key), {
    /* Get the status of the key in kmap and return it. */
    return kmap[key];
})

EM_JS(int, getwidth, (void), {
    /* Get the width of the canvas from the canvas element. */
    return window.canvas.width;
})

EM_JS(int, getheight, (void), {
    /* Get the height of the canvas from the canvas element. */
    return window.canvas.height;
})

EM_JS(int, ms_time, (void), {
    /* Get the current ms time from js. */
    return Date.now();
})

EM_JS(void, init_mouse, (void), {
    window.mx = 0;
    window.my = 0;
    /* Add event listener for mouse movement to update the position of the
    mouse, to be able to get it later with get_mouse_x and get_mouse_y */
    window.canvas.addEventListener("mousemove", (event) => {
        /* Divide the position by the size of a pixel of the canvas to get the
        position of the mouse on the canvas. */
        window.mx = Number(event.offsetX/(window.canvas.offsetWidth/
            window.canvas.width));
        window.my = Number(event.offsetY/(window.canvas.offsetHeight/
            window.canvas.height));
    });
})

EM_JS(void, init_click, (void), {
    window.click = 0;
    /* If the user is clicking */
    window.canvas.addEventListener("mousedown", function(event) {
        window.click = 1; /* Set click to 1 because the user is clicking. */
        /* Update the mouse position. */
        window.mx = Number(event.offsetX/(window.canvas.offsetWidth/
            window.canvas.width));
        window.my = Number(event.offsetY/(window.canvas.offsetHeight/
            window.canvas.height));
    });
    /* If the user released the pressed mouse button */
    window.canvas.addEventListener("mouseup", function(event) {
        window.click = 0; /* Set click to 0 because the user isn't clicking. */
        /* Update the mouse position. */
        window.mx = Number(event.offsetX/(window.canvas.offsetWidth/
            window.canvas.width));
        window.my = Number(event.offsetY/(window.canvas.offsetHeight/
            window.canvas.height));
    });
})

EM_JS(void, init_touch_move, (void), {
    window.mx = 0;
    window.my = 0;
    /* Add event listener for mouse movement to update the position of the
    mouse, to be able to get it later with get_mouse_x and get_mouse_y */
    window.canvas.addEventListener("mousemove", (event) => {
        window.mx = Number(event.offsetX/(window.canvas.offsetWidth/
            window.canvas.width));
        window.my = Number(event.offsetY/(window.canvas.offsetHeight/
            window.canvas.height));
    });
})

EM_JS(void, init_touch, (void), {
    window.click = 0;
    /* If the user starts pressing on the screen. */
    window.canvas.addEventListener("touchstart", function(event) {
        canvas_rect = window.canvas.getBoundingClientRect();
        /* The game only needs to handle one press on the screen, so I only get
        the first one. */
        /* I update the mouse position because the touch screen should be
        handled like a mouse */
        window.mx = Number((event.changedTouches.item(0).pageX -
            canvas_rect.left)/(window.canvas.offsetWidth/window.canvas.width));
        window.my = Number((event.changedTouches.item(0).pageY -
            canvas_rect.top)/(window.canvas.offsetHeight/window.canvas.height));
        window.click = 1; /* It's like a click. */
    });
    /* If the user stops pressing on the screen. */
    window.canvas.addEventListener("touchend", function(event) {
        window.click = 0; /* It's not like a click anymore. */
    });
})

EM_JS(int, get_mouse_x, (void), {
    /* Return mx that stores the x position of the mouse on screen. */
    return window.mx;
})

EM_JS(int, get_mouse_y, (void), {
    /* Return my that stores the y position of the mouse on screen. */
    return window.my;
})

EM_JS(bool, is_clicked, (void), {
    /* Return click, a bool that stores if the user is clicking/pressing on the
    screen. */
    return window.click;
})

void main_loop(void (*loop_function)(void), int fps) {
    /* Use emscripten_set_main_loop to call loop_function at fps frames per
    second. */
    emscripten_set_main_loop(loop_function, fps, 1);
}

#else
/* SDL version */

int _w = 0, _h = 0;
Uint8 *_kbuffer;
SDL_Surface *_surface;

void init_canvas(int width, int height, char *canvasname) {
    /* Initialize the SDL etc. */
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        puts("[canvaslib] Failed to initialize the SDL !");
        exit(-1);
    }
    SDL_WM_SetCaption(canvasname, canvasname);
    _surface = SDL_SetVideoMode(width, height, 32, 0);
    if(!_surface){
        puts("[canvaslib] Failed to get the surface from the SDL window !");
        exit(-1);
    }
    if(SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,
        SDL_DEFAULT_REPEAT_INTERVAL) < 0){
        puts("[canvaslib] Can't enable key repeat !");
        exit(-1);
    }
    /* Store the width and the height in _w and _h to be able to get them
    later. */
    _w = width;
    _h = height;
    /* Enable unicode to be able to get the pressed keys. */
    SDL_EnableUNICODE(1);
    /* Lock the SDL surface to be able to modify it. */
    SDL_LockSurface(_surface);
    /* Clear the window. */
    clear();
}

void put_pixel(int x, int y, int r, int g, int b, int a) {
    Uint32 *target_pixel; /* Target pixel contains the position of the pixel in
    the SDL surface. */
    if(x>=0 && x<_w && y>=0 && y<_h){
        /* If the pixel is in the surface. */
        /* Calculate the position of the pixel in the surface. */
        target_pixel = (Uint32 *)((Uint8 *)_surface->pixels+y*_surface->pitch+x*
            _surface->format->BytesPerPixel);
        /* Convert r, g, b to an Uint32 and store it at target_pixel. */
        *target_pixel = SDL_MapRGB(_surface->format, r, g, b);
    }
}

void update(void) {
    /* Unlock the surface to be able to display the surface in the window. */
    SDL_UnlockSurface(_surface);
    /* Display the surface in the window. */
    SDL_Flip(_surface);
    /* Lock the SDL surface to be able to modify it. */
    SDL_LockSurface(_surface);
}

void clear(void) {
    /* Fill the surface with white. */
    SDL_FillRect(_surface, NULL, 0xFFFFFF);
}

void init_getkey(void) {
    return; /* Not needed with SDL */
}

bool getkey(int key) {
    /* Get all events. */
    SDL_PumpEvents();
    /* Get the status of all keys in _kbuffer */
    _kbuffer = SDL_GetKeyState(NULL);
    /* Return the value of _kbuffer at key. */
    return _kbuffer[key];
}

int getwidth(void) {
    return _w; /* Return the width of the surface previously stored. */
}

int getheight(void) {
    return _h; /* Return the height of the surface previously stored. */
}

int ms_time(void) {
    return SDL_GetTicks(); /* Get the ms elapsed since midnight. */
}

void init_mouse(void) {
    return; /* TODO : Code this */
}

void init_click(void) {
    return; /* TODO : Code this */
}

void init_touch_move(void) {
    return; /* TODO : Code this */
}

void init_touch(void) {
    return; /* TODO : Code this */
}

int get_mouse_x(void) {
    return 0; /* TODO : Code this */
}

int get_mouse_y(void) {
    return 0; /* TODO : Code this */
}

bool is_clicked(void) {
    return 0; /* TODO : Code this */
}

bool _exit(void) {
    SDL_Event event;
    /* Check if there is a quit event. */
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return 1; /* If there is one. */
        }
    }
    return 0; /* Else */
}

void main_loop(void (*loop_function)(void), int fps) {
    Uint32 _last_t; /* _last_t contains the time in ms before running
    loop_function. */
    Uint32 ticks = 1000/(Uint32)fps; /* ticks contains the duration of one loop
    in ms. */
    while(!_exit()){ /* If the user wants to exit, do not continue the loop. */
        _last_t = SDL_GetTicks(); /* Get the current ticks. */
        loop_function(); /* Call the loop function */
        if(SDL_GetTicks() < _last_t){ /* If _last_t is smaller than the ticks,
            what's not normal, don't wait because it would be very long. */
            _last_t = SDL_GetTicks();
        }else{
            /* Wait that ticks ms are elapsed. */
            while(SDL_GetTicks() - _last_t < ticks);
        }
    }
}

#endif
