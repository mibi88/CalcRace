CC = emcc
LIBS = 
CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -O3 -ggdb -fsanitize=address -s WASM=1
FILES = src/main.c src/map.c src/tiles.c src/text.c src/player.c src/game.c src/memory.c lib/canvas.c lib/image.c

all:
	mkdir -p bin
	mkdir -p img_conv
	python3 tools/imgconv_dir_term.py "img/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/cars/skin1/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/font/skin1/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/backgrounds/" "img_conv/"
	$(CC) $(CFLAGS) $(FILES) -o bin/MathRace.js
	cp img/favicon.ico bin/
	cp src/MathRace.html bin/
	cp src/run.sh bin/
	chmod a+x bin/run.sh
run:
	bin/run.sh
clean:
	rm --force --recursive bin
	rm --force --recursive img_conv
