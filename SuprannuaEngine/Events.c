#include "SuprannuaEngine.h"

bool event_arePolygonsTouching(int firstObjectNumber, int secondObjectNumber)
{
	return (geometry_findDistance(POLYGON, firstObjectNumber, POLYGON, secondObjectNumber) <
		polygon[firstObjectNumber].radius + polygon[secondObjectNumber].radius);
}

bool event_doAfter(double interval, int eventID)
{
	return !(event_doFor(interval, eventID));
}

bool event_doFor(double interval, int eventID)
{
	static double remainingTime[100];

	if (remainingTime[eventID] <= 0)
	{
		remainingTime[eventID] = interval;
	}

	remainingTime[eventID] -= (FRAME_TIME_MILLISECS / 1000);

	return (remainingTime[eventID] > 0);
}

bool event_hasFalleninAHole(unsigned char object, int objectNumber)
{
	return (polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius < 1);
}

bool event_hasPolygonPastXLocation(int objectNumber, double xPosition)
{
	return (polygon[objectNumber].centre.xPosition > xPosition);
}

bool event_hasPolygonPastYLocation(int objectNumber, double yPosition)
{
	return (polygon[objectNumber].centre.yPosition > yPosition);
}

bool event_isPolygonHigher(int firstObjectNumber, int secondObjectNumber)
{
	return (polygon[firstObjectNumber].centre.yPosition > polygon[secondObjectNumber].centre.yPosition);
}

bool event_isOnCycle(double interval)
{
	return (frameCount % (int)(FRAME_RATE * interval * 2) < (FRAME_RATE * interval));
}

bool event_isOnPlatform(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	if (block[platformNumber].properties.classification == PLATFORM)
	{
		if (polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius <=
			block[platformNumber].centre.yPosition + (block[platformNumber].dimensions.height / 2) &&
			polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius >
			block[platformNumber].centre.yPosition - (block[platformNumber].dimensions.height / 2))
		{
			return (event_isWithinPlatformWidth(object, objectNumber, platformNumber));
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool event_isOnceEvery(double interval)
{
	return (frameCount % (int)(FRAME_RATE * interval) == 0);
}

bool event_isOnInstant(int eventID)
{
	static int callFrame[100] = {0};

	if (frameCount > 1)
	{
		if (callFrame[eventID] == (frameCount - 1))
		{
			callFrame[eventID] = frameCount;
			return false;
		}
		else
		{
			callFrame[eventID] = frameCount;
			return true;
		}
	}
}

bool event_isPolygonAirboune(unsigned char object,
	int objectNumber)
{
	int i;

	for (i = 0; i <= storedBlocks; i++)
	{
		if (event_isOnPlatform(object, objectNumber, i))
			break;
		if (event_isTouchingUnderPlatform(object, objectNumber, i))
			break;
		if (i == storedBlocks)
			return true;
	}

	return false;
}

bool event_isTouchingLeftOfPlatform(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	if (block[platformNumber].properties.classification == PLATFORM)
	{
		if (polygon[objectNumber].centre.xPosition + polygon[objectNumber].radius >=
			block[platformNumber].centre.xPosition - (block[platformNumber].dimensions.width / 2) &&
			polygon[objectNumber].centre.xPosition + polygon[objectNumber].radius <
			block[platformNumber].centre.xPosition + (block[platformNumber].dimensions.width / 2))
		{
			return (event_isWithinPlatformHeight(object, objectNumber, platformNumber));
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool event_isTouchingRightOfPlatform(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	if (block[platformNumber].properties.classification == PLATFORM)
	{
		if (polygon[objectNumber].centre.xPosition - polygon[objectNumber].radius <=
			block[platformNumber].centre.xPosition + (block[platformNumber].dimensions.width / 2) &&
			polygon[objectNumber].centre.xPosition - polygon[objectNumber].radius >
			block[platformNumber].centre.xPosition - (block[platformNumber].dimensions.width / 2))
		{
			return (event_isWithinPlatformHeight(object, objectNumber, platformNumber));
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool event_isTouchingUnderPlatform(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	if (block[platformNumber].properties.classification == PLATFORM)
	{
		if (polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius >=
			block[platformNumber].centre.yPosition - (block[platformNumber].dimensions.height / 2) &&
			polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius <
			block[platformNumber].centre.yPosition + (block[platformNumber].dimensions.height / 2))
		{
			return (event_isWithinPlatformWidth(object, objectNumber, platformNumber));
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool event_isPolygonWithinRadius(int firstObjectNumber,
	double radius,
	int secondObjectNumber)
{
	return (geometry_findDistance(POLYGON, firstObjectNumber, POLYGON, secondObjectNumber) <= radius);
}

bool event_isWithinPlatformHeight(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	return (polygon[objectNumber].centre.yPosition >
		block[platformNumber].centre.yPosition - (block[platformNumber].dimensions.height / 2) &&
		polygon[objectNumber].centre.yPosition <
		block[platformNumber].centre.yPosition + (block[platformNumber].dimensions.height / 2));
}

bool event_isWithinPlatformWidth(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	return (polygon[objectNumber].centre.xPosition >
		block[platformNumber].centre.xPosition - (block[platformNumber].dimensions.width / 2) &&
		polygon[objectNumber].centre.xPosition <
		block[platformNumber].centre.xPosition + (block[platformNumber].dimensions.width / 2));
}

bool event_isWithinTime(double startTime, double endTime)
{
	return (timeCount >= startTime && timeCount <= endTime);
}