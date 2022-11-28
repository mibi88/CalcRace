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

from PIL import Image

import os

def conv(image, path, outpath, prefix = ""):
	name, ext = os.path.splitext(image)
	if ext == ".png":
		img = Image.open(path + image).convert("RGBA")
		w, h = img.size

		pixels = []

		for y in range(h):
			for x in range(w):
				pixel = img.getpixel((x, y))
				pixels.append(pixel[0])
				pixels.append(pixel[1])
				pixels.append(pixel[2])
				pixels.append(pixel[3])

		image_name = name

		out = "#ifndef " + image_name.upper() + "_H\n#define " + image_name.upper() + "_H\n#include \"../lib/image.h\"\n\n/* Image " + image + " converted with tools/imgconv_dir.py */\n\nconst unsigned char " + image_name + "_data[" + str(w*h*4) + "] = {"

		for i in pixels:
			out += hex(i) + ", "
		out = out[:-2]
		out += "};\n\nconst int " + image_name + "_width = " + str(w) + ";\nconst int " + image_name + "_height = " + str(h) + ";\n#endif\n"
		# print(out)

		with open(outpath + prefix + name + ".h", "w") as file:
			file.write(out)
			file.close()
