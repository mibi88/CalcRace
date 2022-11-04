CC = emcc
LIBS = 
CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -ggdb -fsanitize=address -s WASM=1
FILES = src/main.c src/map.c src/tiles.c lib/canvas.c lib/image.c

all:
	mkdir -p bin
	mkdir -p img_conv
	python3 tools/imgconv_dir_term.py "img/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/cars/skin1/" "img_conv/"
	$(CC) $(CFLAGS) $(FILES) -o bin/MathRace.js
	cp img/favicon.ico bin/
	cp src/MathRace.html bin/
run:
	cd bin
	python3 -m http.server 8000
	cd ..
clean:
	rm --force --recursive bin
	rm --force --recursive img_conv