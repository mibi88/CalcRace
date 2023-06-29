/*
 * CalcRace - Get better in mental calculation while having some fun !
 * Copyright (C) 2022  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#include <audio.h>

#ifdef __EMSCRIPTEN__

EM_JS(void, init_audio, (char* ctype), {
    /* Create a new audio context and oscillator. */
    window.audioctx = new AudioContext();
    window.oscillator = window.audioctx.createOscillator();
    window.oscillator.type = UTF8ToString(ctype);
    /* Start the oscillator. */
    window.oscillator.start();
})

EM_JS(void, set_frequency, (int hz), {
    /* Update the frequency of the oscillator. */
    window.oscillator.frequency.setValueAtTime(hz, window.audioctx.currentTime);
})

EM_JS(void, start_beep, (void), {
    try{
        /* Connect the oscillator to the audioctx, to let the user hear the
        sound. */
        window.oscillator.connect(window.audioctx.destination);
    }catch(error){
        /* If there was an error throw it in the console. */
        console.log("[audio.h] " + error);
    }
})

EM_JS(void, stop_beep, (void), {
    try{
        /* Disconnect the oscillator from the audioctx, so the user wont hear
        the sound anymore. */
        window.oscillator.disconnect(window.audioctx.destination);
    }catch(error){
        /* If there was an error throw it in the console. */
        console.log("[audio.h] " + error);
    }
})

#else
/* SDL version */

void init_audio(char *ctype) {
    return; /* TODO : Code this */
}

void set_frequency(int hz) {
    return; /* TODO : Code this */
}

void start_beep(void) {
    return; /* TODO : Code this */
}

void stop_beep(void) {
    return; /* TODO : Code this */
}

#endif
