#ifndef KEYBOARD_H
#define KEYBOARD_H

/* Define the new keys and the amount of keys. */
enum {
	NKEY_UP,
	NKEY_DOWN,
	NKEY_LEFT,
	NKEY_RIGHT,
	NKEY_SPACE,
	KEYS_AMOUNT
};

typedef enum {
	K_REPEAT,
	K_NO_REPEAT
} Keymode;

/* Enable or disable repeat for all the keys. */
void setprofile(Keymode new_profile[KEYS_AMOUNT]);

/* Returns true if a key is down, or false if it's not the case. */
int kdown(int key);

#endif
