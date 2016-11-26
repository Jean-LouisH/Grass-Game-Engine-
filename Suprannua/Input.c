#include "Suprannua.h"

bool input_isPressed(unsigned char input)
{
	bool inputFlag = false;

    //XOR gated ASCII character for capital or common letters.
	if (keyStates[input] == true || keyStates[(input^0x0020)] == true)
	{ 
		inputFlag = true;
	}

	if (specialKeyStates[input] == true)
	{
		inputFlag = true;
	}

	return (inputFlag);
}
