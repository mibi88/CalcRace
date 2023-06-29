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

def conv(infile, outfile, prefix = ""):
    # Get the name and the extension of the input file.
    name, ext = os.path.splitext(os.path.basename(infile))
    # If the input file is a png, we convert it.
    if ext == ".png":
        # We open the input file with Pillow
        img = Image.open(infile).convert("RGBA")
        w, h = img.size
        # We create an array for the RGBA values of each pixel of the image.
        pixels = []
        # We loop through the image.
        for y in range(h):
            for x in range(w):
                # We get the pixel.
                pixel = img.getpixel((x, y))
                # We add his r, g, b and a color values to the pixel array.
                pixels.append(pixel[0])
                pixels.append(pixel[1])
                pixels.append(pixel[2])
                pixels.append(pixel[3])

        image_name = name

        # We generate the part of the header that is before the array of colors.
        out = ("#ifndef " + image_name.upper() + "_H\n#define " +
            image_name.upper() +
            "_H\n#include <image.h>\n\n/* Image " + name +
            " converted with tools/imgconv_dir.py */\n\nconst unsigned char " +
            image_name + "_data[" + str(w*h*4) + "] = {")
        # We put the array of colors in out.
        for i in pixels:
            out += hex(i) + ", "
        out = out[:-2] # We remove the last ", " because nothing follows it.
        # We generate the end of the header.
        out += ("};\n\nconst int " + image_name + "_width = " + str(w) +
        ";\nconst int " + image_name + "_height = " + str(h) + ";\n#endif\n")
        # We write the header to the output file.
        with open(outfile, "w") as file:
            file.write(out)
            file.close()
    else:
        # We print an error message if the image is not a png because we are not
        # sure that we can open it.
        print("bad ext")
