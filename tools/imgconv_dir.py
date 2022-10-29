from PIL import Image

import os

path = input("Path > ")

for image in os.listdir(path):
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

	image_name = image[:-4]

	out = "#include \"../lib/image.h\"\n\n/* Image " + image + " converted with tools/imgconv_dir.py */\n\nconst unsigned char " + image_name + "_data[" + str(w*h*4) + "] = {"

	for i in pixels:
		out += hex(i) + ", "
	out = out[:-2]
	out += "};\n\nconst int " + image_name + "_width = " + str(w) + ";\nconst int " + image_name + "_height = " + str(h) + ";\n"
	# print(out)

	with open(path + image_name + ".h", "w") as file:
		file.write(out)
		file.close()
