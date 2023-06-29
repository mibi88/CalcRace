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

#ifndef AUDIO_H
#define AUDIO_H

#ifdef __EMSCRIPTEN__

#include <emscripten.h>

#endif

/* Initialize the oscillator with the waveform type. */
void init_audio(char* type);

/* Set the frequency of the oscillator to hz Hz. */
void set_frequency(int hz);

/* Start beeping. */
void start_beep(void);

/* Stop the beep. */
void stop_beep(void);

#endif

