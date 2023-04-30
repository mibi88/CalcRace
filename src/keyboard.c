#include <keyboard.h>
#include <touch.h>
#include <canvas.h>
#include <string.h>

/* Contains for each key a Keymode. If this Keymode is K_NO_REPEAT, we will wait
that the key is released before returning if the key was pressed or not in
kdown, but if the Keymode is K_REPEAT the value that kdown returns is always
true is the key is held down. */
Keymode profile[KEYS_AMOUNT];

/* True if the key was already pressed before. */
bool wasdown[KEYS_AMOUNT];

/* key_nums contains the lib/canvas.h keycodes for each keyboard.h key. */
int key_nums[KEYS_AMOUNT] = {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE
};

/* screen_zone contains the zone on the screen that does the same as the key in
key_nums */

int screen_zone[KEYS_AMOUNT*4] = {
	32, 0, 95, 32,
	32, 63, 95, 95,
	0, 32, 32, 95,
	63, 32, 127, 63,
	32, 32, 95, 63
};

void setprofile(Keymode new_profile[KEYS_AMOUNT]) {
	/* Copy the new profile into the old one. */
	memcpy(profile, new_profile, sizeof(Keymode)*KEYS_AMOUNT);
	memset(wasdown, 0, sizeof(bool)*KEYS_AMOUNT);
}

int _kdown(int key) {
	/* Check if a key/the right position on the screen is pressed. */
	int offset;
	offset = key*4;
	return click_on_zone(screen_zone[offset], screen_zone[offset+1],
		screen_zone[offset+2], screen_zone[offset+3]) | getkey(key_nums[key]);
}

int kdown(int key) {
	int out;
	out = _kdown(key); /* Check if the key is pressed or not. */
	if(profile[key] == K_NO_REPEAT){
		/* We return true after the key was pressed, but if she stays pressed we
		always return 0 before she's relesed. */
		/* Check if the key is not pressed the first time */
		if(wasdown[key] && out) return 0;
		/* Update wasdown. */
		if(!wasdown[key] && out) wasdown[key] = 1;
		else if(wasdown[key] && !out) wasdown[key] = 0;
	}else{
		return out;
	}
	return out;
}
