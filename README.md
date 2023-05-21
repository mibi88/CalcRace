# CalcRace
A little video game made to get better in mental calculation !

## Compiling the game

Required tools and libraries to build this game
* For both targets
    * meson
    * ninja
    * python3
    * bash/zsh/dash
* For the web version
    * emscripten
* For the SDL2 version (**coming soon**)
    * SDL2

Then just run :
* `$ meson bin --cross-file wasm-cross.txt && cd bin && ninja` : to compile the web version of the game.
* `$ meson bin && cd bin && ninja` : to compile the SDL2 version of the game.

I hope that you'll have a lot of fun playing it !
