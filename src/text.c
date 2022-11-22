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

#include "text.h"

#include "font.h"

void dtext(unsigned char *text, int sx, int sy, int len) {
	/* Todo : don't use an image for each character. */
	int i, osx = sx;
	unsigned char c;
	for(i=0;i<len;i++){
		c = text[i];
		switch(c){
			case ' ':
				draw_image_del_color(sx, sy, (const unsigned char*)space_data, 8, 8, 0, 0, 0, 0);
				break;
			case '!':
				draw_image_del_color(sx, sy, (const unsigned char*)exclamation_data, 8, 8, 0, 0, 0, 0);
				break;
			case '"':
				draw_image_del_color(sx, sy, (const unsigned char*)quote_data, 8, 8, 0, 0, 0, 0);
				break;
			case '#':
				draw_image_del_color(sx, sy, (const unsigned char*)hash_data, 8, 8, 0, 0, 0, 0);
				break;
			case '$':
				draw_image_del_color(sx, sy, (const unsigned char*)dollar_data, 8, 8, 0, 0, 0, 0);
				break;
			case '%':
				draw_image_del_color(sx, sy, (const unsigned char*)percents_data, 8, 8, 0, 0, 0, 0);
				break;
			case '&':
				draw_image_del_color(sx, sy, (const unsigned char*)and_data, 8, 8, 0, 0, 0, 0);
				break;
			case '\'':
				draw_image_del_color(sx, sy, (const unsigned char*)apostrophe_data, 8, 8, 0, 0, 0, 0);
				break;
			case '(':
				draw_image_del_color(sx, sy, (const unsigned char*)parenthese_open_data, 8, 8, 0, 0, 0, 0);
				break;
			case ')':
				draw_image_del_color(sx, sy, (const unsigned char*)parenthese_close_data, 8, 8, 0, 0, 0, 0);
				break;
			case '*':
				draw_image_del_color(sx, sy, (const unsigned char*)multiply_data, 8, 8, 0, 0, 0, 0);
				break;		
			case '+':
				draw_image_del_color(sx, sy, (const unsigned char*)plus_data, 8, 8, 0, 0, 0, 0);
				break;
			case ',':
				draw_image_del_color(sx, sy, (const unsigned char*)comma_data, 8, 8, 0, 0, 0, 0);
				break;
			case '-':
				draw_image_del_color(sx, sy, (const unsigned char*)minus_data, 8, 8, 0, 0, 0, 0);
				break;
			case '.':
				draw_image_del_color(sx, sy, (const unsigned char*)dot_data, 8, 8, 0, 0, 0, 0);
				break;
			case '/':
				draw_image_del_color(sx, sy, (const unsigned char*)slash_data, 8, 8, 0, 0, 0, 0);
				break;
			case '0':
				draw_image_del_color(sx, sy, (const unsigned char*)n0_data, 8, 8, 0, 0, 0, 0);
				break;
			case '1':
				draw_image_del_color(sx, sy, (const unsigned char*)n1_data, 8, 8, 0, 0, 0, 0);
				break;
			case '2':
				draw_image_del_color(sx, sy, (const unsigned char*)n2_data, 8, 8, 0, 0, 0, 0);
				break;
			case '3':
				draw_image_del_color(sx, sy, (const unsigned char*)n3_data, 8, 8, 0, 0, 0, 0);
				break;
			case '4':
				draw_image_del_color(sx, sy, (const unsigned char*)n4_data, 8, 8, 0, 0, 0, 0);
				break;
			case '5':
				draw_image_del_color(sx, sy, (const unsigned char*)n5_data, 8, 8, 0, 0, 0, 0);
				break;
			case '6':
				draw_image_del_color(sx, sy, (const unsigned char*)n6_data, 8, 8, 0, 0, 0, 0);
				break;
			case '7':
				draw_image_del_color(sx, sy, (const unsigned char*)n7_data, 8, 8, 0, 0, 0, 0);
				break;
			case '8':
				draw_image_del_color(sx, sy, (const unsigned char*)n8_data, 8, 8, 0, 0, 0, 0);
				break;
			case '9':
				draw_image_del_color(sx, sy, (const unsigned char*)n9_data, 8, 8, 0, 0, 0, 0);
				break;
			case ':':
				draw_image_del_color(sx, sy, (const unsigned char*)colon_data, 8, 8, 0, 0, 0, 0);
				break;
			case ';':
				draw_image_del_color(sx, sy, (const unsigned char*)semicolon_data, 8, 8, 0, 0, 0, 0);
				break;
			case '<':
				draw_image_del_color(sx, sy, (const unsigned char*)less_data, 8, 8, 0, 0, 0, 0);
				break;
			case '=':
				draw_image_del_color(sx, sy, (const unsigned char*)equal_data, 8, 8, 0, 0, 0, 0);
				break;
			case '>':
				draw_image_del_color(sx, sy, (const unsigned char*)bigger_data, 8, 8, 0, 0, 0, 0);
				break;
			case '?':
				draw_image_del_color(sx, sy, (const unsigned char*)question_data, 8, 8, 0, 0, 0, 0);
				break;
			case '@':
				draw_image_del_color(sx, sy, (const unsigned char*)at_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'A':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_a_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'B':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_b_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'C':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_c_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'D':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_d_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'E':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_e_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'F':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_f_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'G':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_g_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'H':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_h_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'I':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_i_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'J':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_j_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'K':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_k_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'L':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_l_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'M':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_m_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'N':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_n_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'O':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_o_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'P':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_p_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'Q':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_q_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'R':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_r_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'S':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_s_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'T':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_t_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'U':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_u_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'V':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_v_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'W':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_w_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'X':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_x_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'Y':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_y_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'Z':
				draw_image_del_color(sx, sy, (const unsigned char*)lb_z_data, 8, 8, 0, 0, 0, 0);
				break;
			case '[':
				draw_image_del_color(sx, sy, (const unsigned char*)squareb_open_data, 8, 8, 0, 0, 0, 0);
				break;
			case '\\':
				draw_image_del_color(sx, sy, (const unsigned char*)backslash_data, 8, 8, 0, 0, 0, 0);
				break;
			case ']':
				draw_image_del_color(sx, sy, (const unsigned char*)squareb_close_data, 8, 8, 0, 0, 0, 0);
				break;
			case '^':
				draw_image_del_color(sx, sy, (const unsigned char*)caret_data, 8, 8, 0, 0, 0, 0);
				break;
			case '_':
				draw_image_del_color(sx, sy, (const unsigned char*)underscore_data, 8, 8, 0, 0, 0, 0);
				break;
			case '`':
				draw_image_del_color(sx, sy, (const unsigned char*)backtick_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'a':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_a_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'b':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_b_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'c':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_c_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'd':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_d_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'e':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_e_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'f':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_f_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'g':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_g_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'h':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_h_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'i':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_i_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'j':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_j_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'k':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_k_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'l':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_l_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'm':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_m_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'n':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_n_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'o':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_o_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'p':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_p_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'q':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_q_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'r':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_r_data, 8, 8, 0, 0, 0, 0);
				break;
			case 's':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_s_data, 8, 8, 0, 0, 0, 0);
				break;
			case 't':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_t_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'u':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_u_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'v':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_v_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'w':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_w_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'x':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_x_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'y':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_y_data, 8, 8, 0, 0, 0, 0);
				break;
			case 'z':
				draw_image_del_color(sx, sy, (const unsigned char*)ls_z_data, 8, 8, 0, 0, 0, 0);
				break;
			case '{':
				draw_image_del_color(sx, sy, (const unsigned char*)curlyb_open_data, 8, 8, 0, 0, 0, 0);
				break;
			case '|':
				draw_image_del_color(sx, sy, (const unsigned char*)vbar_data, 8, 8, 0, 0, 0, 0);
				break;
			case '}':
				draw_image_del_color(sx, sy, (const unsigned char*)curlyb_close_data, 8, 8, 0, 0, 0, 0);
				break;
			case '~':
				draw_image_del_color(sx, sy, (const unsigned char*)tilde_data, 8, 8, 0, 0, 0, 0);
				break;
			case 0x7F:
				draw_image_del_color(sx, sy, (const unsigned char*)del_data, 8, 8, 0, 0, 0, 0);
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
