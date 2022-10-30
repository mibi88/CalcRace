/*
 * MathRace - Get better in mental calculation while having some fun !
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

#include "tiles.h"

#include "graphics.h"

void drawtile(int x, int y, int type){
	switch(type){
		case 1:
			draw_image(x, y, ask_data, 32, 32);
			break;
		case 2:
			draw_image(x, y, border_curve1_data, 32, 32);
			break;
		case 3:
			draw_image(x, y, border_curve2_data, 32, 32);
			break;
		case 4:
			draw_image(x, y, border_curve3_data, 32, 32);
			break;
		case 5:
			draw_image(x, y, border_curve4_data, 32, 32);
			break;
		case 6:
			draw_image(x, y, border_horizontal1_data, 32, 32);
			break;
		case 7:
			draw_image(x, y, border_horizontal2_data, 32, 32);
			break;
		case 8:
			draw_image(x, y, border_vertical1_data, 32, 32);
			break;
		case 9:
			draw_image(x, y, border_vertical2_data, 32, 32);
			break;
		case 10:
			draw_image(x, y, bush1_data, 32, 32);
			break;
		case 11:
			draw_image(x, y, coin_data, 32, 32);
			break;
		case 12:
			draw_image(x, y, coin1_data, 32, 32);
			break;
		case 13:
			draw_image(x, y, coin2_data, 32, 32);
			break;
		case 14:
			draw_image(x, y, coin3_data, 32, 32);
			break;
		case 15:
			draw_image(x, y, color_change1_data, 32, 32);
			break;
		case 16:
			draw_image(x, y, color_change2_data, 32, 32);
			break;
		case 17:
			draw_image(x, y, color_change3_data, 32, 32);
			break;
		case 18:
			draw_image(x, y, color_change4_data, 32, 32);
			break;
		case 19:
			draw_image(x, y, cube_data, 32, 32);
			break;
		case 20:
			draw_image(x, y, curve_middle1_data, 32, 32);
			break;
		case 21:
			draw_image(x, y, curve_middle2_data, 32, 32);
			break;
		case 22:
			draw_image(x, y, curve_middle3_data, 32, 32);
			break;
		case 23:
			draw_image(x, y, curve_middle4_data, 32, 32);
			break;
		case 24:
			draw_image(x, y, endline_data, 32, 32);
			break;
		case 25:
			draw_image(x, y, grass1_data, 32, 32);
			break;
		case 26:
			draw_image(x, y, grass2_data, 32, 32);
			break;
		case 27:
			draw_image(x, y, lake_border1_data, 32, 32);
			break;
		case 28:
			draw_image(x, y, lake_border2_data, 32, 32);
			break;
		case 29:
			draw_image(x, y, lake_border3_data, 32, 32);
			break;
		case 30:
			draw_image(x, y, lake_border4_data, 32, 32);
			break;
		case 31:
			draw_image(x, y, little_tree_data, 32, 32);
			break;
		case 32:
			draw_image(x, y, road_middle_data, 32, 32);
			break;
	};
}