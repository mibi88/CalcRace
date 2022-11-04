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

#include "canvas.h"

EM_JS(void, init_canvas, (int width, int height, char *canvasname), {
	canvas = document.getElementById(UTF8ToString(canvasname));
	canvas.width = width;
	canvas.height = height;
	window.ctx = canvas.getContext("2d", antialias = 0);
	window.ctx.imageSmoothingEnabled = false;
	/* var scaleX = window.innerWidth / canvas.width;
	var scaleY = window.innerWidth / canvas.height;
	var scaleToFit = Math.min(scaleX, scaleY);
	var scaleToCover = Math.max(scaleX, scaleY);
	canvas.style.transformOrigin = '0 0';
	canvas.style.transform = 'scale(' + scaleToFit + ')'; */
	/* TODO : Replace the following line */
	canvas.style.transform = "scale(8)";
	window.image = window.ctx.createImageData(width, height);
	window.image.imageSmoothingEnabled = false;
	window.data = image.data;
	window.w = canvas.width;
	window.h = canvas.height;
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
	document.onkeyup = function(e) { kmap[e.keyCode] = false; /* console.log(kmap[e.keyCode]); */ };
	document.onkeydown = function(e) { kmap[e.keyCode] = true; /* console.log(kmap[e.keyCode]); */ };
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
