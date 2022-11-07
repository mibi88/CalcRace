#include "text.h"

void dtext(unsigned char *text, int sx, int sy, int len) {
	int i, osx = sx;
	unsigned char c;
	for(i=0;i<len;i++){
		c = text[i];
		switch(c){
			case '0':
				draw_image_del_color(sx, sy, &n0_data, 8, 8, 0, 0, 0, 0);
				break;
			case '1':
				draw_image_del_color(sx, sy, &n1_data, 8, 8, 0, 0, 0, 0);
				break;
			case '2':
				draw_image_del_color(sx, sy, &n2_data, 8, 8, 0, 0, 0, 0);
				break;
			case '3':
				draw_image_del_color(sx, sy, &n3_data, 8, 8, 0, 0, 0, 0);
				break;
			case '4':
				draw_image_del_color(sx, sy, &n4_data, 8, 8, 0, 0, 0, 0);
				break;
			case '5':
				draw_image_del_color(sx, sy, &n5_data, 8, 8, 0, 0, 0, 0);
				break;
			case '6':
				draw_image_del_color(sx, sy, &n6_data, 8, 8, 0, 0, 0, 0);
				break;
			case '7':
				draw_image_del_color(sx, sy, &n7_data, 8, 8, 0, 0, 0, 0);
				break;
			case '8':
				draw_image_del_color(sx, sy, &n8_data, 8, 8, 0, 0, 0, 0);
				break;
			case '9':
				draw_image_del_color(sx, sy, &n9_data, 8, 8, 0, 0, 0, 0);
				break;
			case '*':
				draw_image_del_color(sx, sy, &multiply_data, 8, 8, 0, 0, 0, 0);
				break;
		}
		if(c == '\n'){
			sy += 9;
			sx = osx;
		}else{
			sx += 9;
		}
	}
}

int text_size_y(unsigned char* text, int len) {
	int i, n = 0;
	for(i=0;i<len;i++){
		if(text[i] == '\n'){
			n++;
		}
	}
	return n*9;
}
