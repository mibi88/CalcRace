CC = emcc
LIBS =
CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -O0 -ggdb -fsanitize=address -s WASM=1
RELEASEFLAGS = -std=c89 -Wall -Wextra -Wpedantic -O3 -s WASM=1
FILES = src/map.c src/tiles.c src/text.c src/player.c src/game.c src/memory.c src/main.c lib/canvas.c lib/image.c lib/audio.c

all:
	mkdir -p bin
	mkdir -p img_conv
	mkdir -p font_chars
	mkdir -p font_conv
	python3 tools/imgconv_dir_term.py "img/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/cars/skin1/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/backgrounds/" "img_conv/"
	python3 tools/imgconv_font_term.py "img/font/skin1/table.png" "font_chars/"
	python3 tools/imgconv_dir_term.py "font_chars/" "font_conv/"
	$(CC) $(CFLAGS) $(FILES) -o bin/MathRace.js
	cp img/favicon.ico bin/
	cp src/MathRace.html bin/
	cp src/run.sh bin/
	chmod a+x bin/run.sh
release:
	mkdir -p bin
	mkdir -p img_conv
	mkdir -p font_chars
	mkdir -p font_conv
	python3 tools/imgconv_dir_term.py "img/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/cars/skin1/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/backgrounds/" "img_conv/"
	python3 tools/imgconv_font_term.py "img/font/skin1/table.png" "font_chars/"
	python3 tools/imgconv_dir_term.py "font_chars/" "font_conv/"
	$(CC) $(RELEASEFLAGS) $(FILES) -o bin/MathRace.js
	cp img/favicon.ico bin/
	cp src/MathRace.html bin/
	cp src/run.sh bin/
	chmod a+x bin/run.sh
github_pages:
	rm --force bin/run.sh
	mv bin/MathRace.html bin/index.html
run:
	bin/run.sh
clean:
	rm --force --recursive bin
	rm --force --recursive img_conv
	rm --force --recursive font_chars
	rm --force --recursive font_conv
	rm --force --recursive tools/__pycache__
