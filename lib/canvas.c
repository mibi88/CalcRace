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
SDL_Window *_window;
SDL_Renderer *_renderer;

void init_canvas(int width, int height, char *canvasname) {
    /* Initialize the SDL */
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        puts("[canvaslib] Failed to initialize the SDL2!");
        exit(-1);
    }
    /* Create the window. */
    _window = SDL_CreateWindow(canvasname, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE);
    if(!_window){
        puts("[canvaslib] Failed to create the SDL2 window!");
        exit(-1);
    }
    /* Create the renderer to be able to draw stuff on screen. */
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if(!_renderer){
        puts("[canvaslib] Failed to create a renderer for the SDL2 window!");
        exit(-1);
    }
    /* Use nearest neighbour for scaling to have a pixelated look. */
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    /* Store the width and the height in _w and _h to be able to get them
    later. */
    _w = width;
    _h = height;
    /* Maximize the window. */
    SDL_MaximizeWindow(_window);
    /* Clear the window. */
    clear();
}

void put_pixel(int x, int y, int r, int g, int b, int a) {
    if(x >= 0 && x < _w && y >= 0 && y < _h){
        /* Set the drawing color and color the pixel in the renderer. */
        SDL_SetRenderDrawColor(_renderer, r, g, b, a);
        SDL_RenderDrawPoint(_renderer, x, y);
    }
}

void update(void) {
    /* Display the renderer in the window. */
    SDL_RenderPresent(_renderer);
}

void clear(void) {
    /* Fill the renderer with white. */
    /* Set the drawing color to white. */
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    /* Clear the renderer with this color. */
    SDL_RenderClear(_renderer);
}

void init_getkey(void) {
    return; /* Not needed with SDL */
}

bool getkey(int key) {
    /* Get all events. */
    SDL_PumpEvents();
    /* Get the status of all keys in _kbuffer */
    _kbuffer = (Uint8*)SDL_GetKeyboardState(NULL);
    /* Return the value of _kbuffer at key. */
    return _kbuffer[key];
}

int getwidth(void) {
    return _w; /* Return the width of the renderer previously stored. */
}

int getheight(void) {
    return _h; /* Return the height of the renderer previously stored. */
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
    /* The size of the drawing area. */
    int w, h;
    /* The scale of the renderer to fill the window. I don't like floats but
    I've found no better way of doing it easly, because the SDL takes
    floats ... */
    float xscale, yscale;
    /* Check if there is a quit event or if the size of the window changed. */
    while(SDL_PollEvent(&event)){
        /* If the size of the window changed. */
        if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            puts("[canvaslib] The window size changed !");
            /* Get the size of the drawing area. */
            SDL_GetRendererOutputSize(_renderer ,&w, &h);
            /* Print this size in the terminal, it can be useful for
            debugging. */
            printf("New size: %d, %d\n", w ,h);
            /* Calculate the size of one pixel on screen. */
            xscale = (float)w/(float)_w;
            yscale = (float)h/(float)_h;
            /* A pixel is a square so xscale and yscale need to be the same. I
            use the smallest value, because I don't want to have pixels that are
            not shown in the window. */
            if(xscale < yscale) yscale = xscale;
            else xscale = yscale;
            /* I set the scale of the renderer and print an error message if it
            fails. */
            if(SDL_RenderSetScale(_renderer, xscale, yscale)){
                puts("[canvaslib] Failed to scale renderer!");
            }
        }
        if(event.type == SDL_QUIT){
            return 1; /* The user wants to quit. */
        }
    }
    return 0; /* Else the user don't want to quit. */
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
    /* I destroy everything. */
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

#endif

