CC = emcc
LIBS =
CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -O0 -ggdb -fsanitize=address -lm -s \
	WASM=1
RELEASEFLAGS = -std=c89 -Wall -Wextra -Wpedantic -O3 -lm -s WASM=2
FILES = src/map.c \
	src/tiles.c \
	src/text.c \
	src/player.c \
	src/game.c \
	src/memory.c \
	src/main.c \
	lib/canvas.c \
	lib/image.c \
	lib/audio.c

all:
	mkdir -p bin
	mkdir -p img_conv
	python3 tools/imgconv_dir_term.py "img/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/cars/skin1/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/backgrounds/" "img_conv/"
	$(CC) $(CFLAGS) $(FILES) -o bin/CalcRace.js
	cp img/favicon.ico bin/
	cp src/CalcRace.html bin/
	cp src/run.sh bin/
	chmod a+x bin/run.sh
release:
	mkdir -p bin
	mkdir -p img_conv
	python3 tools/imgconv_dir_term.py "img/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/cars/skin1/" "img_conv/"
	python3 tools/imgconv_dir_term.py "img/backgrounds/" "img_conv/"
	$(CC) $(RELEASEFLAGS) $(FILES) -o bin/CalcRace.js
	cp img/favicon.ico bin/
	cp src/CalcRace.html bin/
	cp src/run.sh bin/
	chmod a+x bin/run.sh
github_pages:
	rm --force bin/run.sh
	mv bin/CalcRace.html bin/index.html
run:
	bin/run.sh
clean:
	rm --force --recursive bin
	rm --force --recursive img_conv
	rm --force --recursive tools/__pycache__
