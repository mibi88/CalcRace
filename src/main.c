#include <emscripten.h>

#include "../lib/canvas.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../img_conv/car1.h"
#include "../img_conv/bush1.h"

/* #define WIDTH 160
#define HEIGHT 120 */
/* #define WIDTH 1024
#define HEIGHT 768 */
#define WIDTH 64
#define HEIGHT 48
/* #define WIDTH 256
#define HEIGHT 240 */

void loop() {
	int i, x, y, s;
	float start, time;
	start = clock();
	srand(clock());
	clear();
	/* put_pixel(0, 0, 0, 0, 0, 255);
	put_pixel(WIDTH-1, HEIGHT-1, 0, 0, 0, 255); */
	draw_image(5, 3, bush1_data, bush1_width, bush1_height);
	draw_image_del_color(0, 0, car1_data, car1_width, car1_height, 0, 0, 0, 0);
	update();
	time = clock() - start;
	printf("Time : %d\n", (int)(time / 1000));
}

int main(void) {
	init_canvas(WIDTH, HEIGHT, "canvas");
	init_getkey();
	emscripten_set_main_loop(loop, 50, 1);
	return 0;
}
