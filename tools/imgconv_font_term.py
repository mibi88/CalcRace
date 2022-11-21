"""
    Imgconv - converts image data in a header file.
    Copyright (C) 2022  Mibi88

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see https://www.gnu.org/licenses/.
"""

import sys
from imgconv_lib import *

NAMES = [
    "space",
    "exclamation",
    "quote",
    "hash",
    "dollar",
    "percents",
    "and",
    "apostrophe",
    "parenthese_open",
    "parenthese_close",
    "multiply",
    "plus",
    "comma",
    "minus",
    "dot",
    "slash",
    "n0",
    "n1",
    "n2",
    "n3",
    "n4",
    "n5",
    "n6",
    "n7",
    "n8",
    "n9",
    "colon",
    "semicolon",
    "less",
    "equal",
    "bigger",
    "question",
    "at",
    "lb_a",
    "lb_b",
    "lb_c",
    "lb_d",
    "lb_e",
    "lb_f",
    "lb_g",
    "lb_h",
    "lb_i",
    "lb_j",
    "lb_k",
    "lb_l",
    "lb_m",
    "lb_n",
    "lb_o",
    "lb_p",
    "lb_q",
    "lb_r",
    "lb_s",
    "lb_t",
    "lb_u",
    "lb_v",
    "lb_w",
    "lb_x",
    "lb_y",
    "lb_z",
    "squareb_open",
    "backslash",
    "squareb_close",
    "caret",
    "underscore",
    "backtick",
    "ls_a",
    "ls_b",
    "ls_c",
    "ls_d",
    "ls_e",
    "ls_f",
    "ls_g",
    "ls_h",
    "ls_i",
    "ls_j",
    "ls_k",
    "ls_l",
    "ls_m",
    "ls_n",
    "ls_o",
    "ls_p",
    "ls_q",
    "ls_r",
    "ls_s",
    "ls_t",
    "ls_u",
    "ls_v",
    "ls_w",
    "ls_x",
    "ls_y",
    "ls_z",
    "curlyb_open",
    "vbar",
    "curlyb_close",
    "tilde",
    "del"
]

if len(sys.argv) > 2:
	font = sys.argv[1]
	outpath = sys.argv[2]
	img = Image.open(font).convert("RGBA")
	c = 0
	for y in range(6):
		for x in range(16):
			char = img.crop((x*8, y*8, (x+1)*8, (y+1)*8))
			char_name = NAMES[c]
			char.save(outpath+char_name+".png")
			c+=1