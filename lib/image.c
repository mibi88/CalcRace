#include "image.h"

void draw_image(int sx, int sy, const unsigned char *image_data, const int w, const int h) {
	int x, y, index;
	for(y=0;y!=h;y++){
		for(x=0;x!=w;x++){
			index = (y * w + x) * 4;
			put_pixel(sx+x, sy+y, (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]);
			/* printf("%d, %d, %d, %d\n", (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]); */
		}
	}
}
void draw_image_del_color(int sx, int sy, const unsigned char *image_data, const int w, const int h, const int r, const int g, const int b, const int a) {
	int x, y, index;
	for(y=0;y!=h;y++){
		for(x=0;x!=w;x++){
			index = (y * w + x) * 4;
			if((int)image_data[index] != r || (int)image_data[index+1] != g || (int)image_data[index+2] != b || (int)image_data[index+3] != a){
				put_pixel(sx+x, sy+y, (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]);
			}				
			/* printf("%d, %d, %d, %d\n", (int)image_data[index], (int)image_data[index+1], (int)image_data[index+2], (int)image_data[index+3]); */
		}
	}
}
