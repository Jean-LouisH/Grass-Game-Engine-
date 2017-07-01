#include "SuprannuaEngine.h"

bool input_isPressed(unsigned char input)
{
	//XOR gated ASCII character for capital or common letters.
	if (keyStates[input] || keyStates[(input ^ 0x0020)])
		return true;
	/*else if (specialKeyStates[input])
		return true;*/
	else
		return false;
}

bool input_isDoublePressed(unsigned char input, int eventReference)
{
	static double timeStamp[100] = { false };
	const double delayTime = 0.5;
	static bool doubleTapFlag = false;

	if (keyStates[input] || keyStates[(input ^ 0x0020)])
	{
		if (timeStamp[eventReference] + delayTime < timeCount)
		{
			timeStamp[eventReference] = 0.0;
		}

		if (event_isOnInstant(eventReference) && timeStamp[eventReference] > 0.0 &&
			timeCount < timeStamp[eventReference] + delayTime)
		{
			doubleTapFlag = true;
		}

		if (timeStamp[eventReference] == 0.0)
		{
			timeStamp[eventReference] = timeCount;
		}

		if (frameCount == 0)
		{
			timeStamp[eventReference] = 0.0;
		}
	}
	else if (timeCount < timeStamp[eventReference] + delayTime)
	{
		doubleTapFlag = false;
	}
	else
	{
		return false;
	}

	return doubleTapFlag;
}
