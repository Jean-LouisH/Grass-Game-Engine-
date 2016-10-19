#include "Definitions.h"
#include "Input.h"

bool input_isPressed(int input)
{
    //XOR gated ASCII character for capital or common letters.
    if (keyStates[input] || keyStates[(input^0x0020)])
        return (true);

    if (specialKeyStates[input])
        return (true);
}
