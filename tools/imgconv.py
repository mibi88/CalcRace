from PIL import Image

image = input("Image > ")

img = Image.open(image).convert("RGBA")
w, h = img.size

pixels = []

for y in range(h):
    for x in range(w):
        pixel = img.getpixel((x, y))
        pixels.append(pixel[0])
        pixels.append(pixel[1])
        pixels.append(pixel[2])
        pixels.append(pixel[3])

image_name = input("Image name > ")

out = "#include \"../lib/image.h\"\n\n/* Image " + image + " converted with tools/imgconv.py */\n\nconst unsigned char " + image_name + "_data[" + str(w*h*4) + "] = {"

for i in pixels:
    out += hex(i) + ", "
out = out[:-2]
out += "};\n\nconst int " + image_name + "_width = " + str(w) + ";\nconst int " + image_name + "_height = " + str(h) + ";\n"
# print(out)

with open(image_name + ".h", "w") as file:
    file.write(out)
    file.close()
