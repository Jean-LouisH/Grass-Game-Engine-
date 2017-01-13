#include "SuprannuaEngine.h"

bool input_isPressed(unsigned char input)
{
	//XOR gated ASCII character for capital or common letters.
	if (keyStates[input] || keyStates[(input ^ 0x0020)])
		return true;
	else if (specialKeyStates[input])
		return true;
	else
		return false;
}
