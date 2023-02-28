#ifndef KEYPAD_H
#define KEYPAD_H

#include <cstdint>
#include "main.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define GPIO_BASE 0x40010400

const char NO_KEY = '\0';
constexpr auto LIST_MAX = 10;		// Max number of keys on the active list.;
constexpr auto MAPSIZE = 10;// MAPSIZE is the number of rows (times 16 columns);

typedef enum
{
	IDLE, PRESSED, HOLD, RELEASED
} KeyState;

class Key
{
public:
	// members
	char kchar;
	int kcode;
	KeyState kstate;
	bool stateChanged;

	// methods
	Key();
	Key(char userKeyChar);
	void key_update(char userKeyChar, KeyState userState, bool userStatus);
};

typedef struct
{
	unsigned char rows;
	unsigned char columns;
} KeypadSize;

class Keypad: public Key
{
public:
	Keypad(char *userKeymap, const char* rowPins[], const char* colPins[], unsigned char numRows, unsigned char numCols);

	uint16_t bitMap[MAPSIZE];	// 10 row x 16 column array of bits. Except Due which has 32 columns.
	Key key[LIST_MAX];
	unsigned long holdTimer;

	char getKey();
	bool getKeys();
	KeyState getState();
	bool isPressed(char keyChar);
	void setDebounceTime(uint16_t);
	void setHoldTime(uint16_t);
	void addEventListener(void (*listener)(char));
	int findInList(char keyChar);
	int findInList(int keyCode);
	char waitForKey();
	bool keyStateChanged();
	unsigned char numKeys();

private:
	uint32_t startTime;
	char *keymap;
	uint8_t *_rowPins;
	uint8_t *_columnPins;
	KeypadSize sizeKpd;
	uint16_t debounceTime;
	uint16_t holdTime;
	bool single_key;
	char rPortrs[16]{};
	char cPortrs[16]{};
	unsigned char rPins[16]{};
	unsigned char cPins[16]{};

	void scanKeys();
	bool updateList();
	void nextKeyState(unsigned char n, bool button);
	void transitionTo(unsigned char n, KeyState nextState);
	void (*keypadEventListener)(char);
};

#endif
