CC = emcc
LIBS = 
CFLAGS = -std=c89 -Wall -Wextra -Wpedantic -ggdb -fsanitize=address -s WASM=1
FILES = src/main.c src/map.c src/tiles.c lib/canvas.c lib/image.c

all:
	mkdir -p bin
	$(CC) $(FILES) -o bin/MathRace.js
	cp img/favicon.ico bin/
	cp src/MathRace.html bin/
run:
	emrun bin/MathRace.html
clean:
	rm --force --recursive bin
