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

EM_JS(void, init_canvas, (int width, int height, char *canvasname), {
	window.canvas = document.getElementById(UTF8ToString(canvasname));
	window.canvas.width = width;
	window.canvas.height = height;
	window.ctx = window.canvas.getContext("2d", antialias = 0);
	window.ctx.imageSmoothingEnabled = false;
	window.image = window.ctx.createImageData(width, height);
	window.image.imageSmoothingEnabled = false;
	window.data = image.data;
	window.w = window.canvas.width;
	window.h = window.canvas.height;
})

EM_JS(void, put_pixel, (int x, int y, int r, int g, int b, int a), {
	if(x >= 0 && x < window.w && y >= 0 && y < window.h){
		var index = (y * window.w + x) * 4;
		data[index + 0] = r;
		data[index + 1] = g;
		data[index + 2] = b;
		data[index + 3] = a;
	}
})

EM_JS(void, update, (void), {
	window.ctx.putImageData(window.image, 0, 0);
})

EM_JS(void, clear, (void), {
	for(i=0;i!=window.w*window.h*4;i++){
		data[i] = 255;
	}
})

EM_JS(void, init_getkey, (void), {
	kmap = {};
	/* document.onkeydown = function(e){
		e = e || event;
		window.map[e.keyCode] = e.type == "keydown";
	}; */
	document.onkeyup = function(e) { kmap[e.keyCode] = false;
		/* console.log(kmap[e.keyCode]); */ };
	document.onkeydown = function(e) { kmap[e.keyCode] = true;
		/* console.log(kmap[e.keyCode]); */ };
})

EM_JS(bool, getkey, (int key), {
	/* if(kmap[key] == true) {
		console.log("GETKEY");
	} */
	return kmap[key];
})

EM_JS(int, getwidth, (void), {
	return window.w;
})

EM_JS(int, getheight, (void), {
	return window.h;
})

EM_JS(int, ms_time, (void), {
	return Date.now();
})

EM_JS(void, init_mouse, (void), {
	window.mx = 0;
	window.my = 0;
	window.canvas.addEventListener("mousemove", (event) => {
		window.mx = Number(event.offsetX/(window.canvas.offsetWidth/window.w));
		window.my = Number(event.offsetY/(window.canvas.offsetHeight/window.h));
	});
})

EM_JS(void, init_click, (void), {
	window.click = 0;
	window.canvas.addEventListener("mousedown", function(event) {
		window.click = 1;
		window.mx = Number(event.offsetX/(window.canvas.offsetWidth/window.w));
		window.my = Number(event.offsetY/(window.canvas.offsetHeight/window.h));
	});
	window.canvas.addEventListener("mouseup", function(event) {
		window.click = 0;
		window.mx = Number(event.offsetX/(window.canvas.offsetWidth/window.w));
		window.my = Number(event.offsetY/(window.canvas.offsetHeight/window.h));
	});
})

EM_JS(void, init_touch_move, (void), {
	window.mx = 0;
	window.my = 0;
	window.canvas.addEventListener("mousemove", (event) => {
		window.mx = Number(event.offsetX/(window.canvas.offsetWidth/window.w));
		window.my = Number(event.offsetY/(window.canvas.offsetHeight/window.h));
	});
})

EM_JS(void, init_touch, (void), {
	window.click = 0;
	window.canvas.addEventListener("touchstart", function(event) {
		canvas_rect = window.canvas.getBoundingClientRect();
		window.mx = Number((event.changedTouches.item(0).pageX -
			canvas_rect.left)/(window.canvas.offsetWidth/window.w));
		window.my = Number((event.changedTouches.item(0).pageY -
			canvas_rect.top)/(window.canvas.offsetHeight/window.h));
		window.click = 1;
	});
	window.canvas.addEventListener("touchend", function(event) {
		window.click = 0;
	});
})

EM_JS(int, get_mouse_x, (void), {
	return window.mx;
})

EM_JS(int, get_mouse_y, (void), {
	return window.my;
})

EM_JS(bool, is_clicked, (void), {
	return window.click;
})

void main_loop(void (*loop_function)(void), int fps) {
	emscripten_set_main_loop(loop_function, fps, 1);
}
