#include "SuprannuaEngine.h"

bool event_arePolygonsTouching(int firstObjectNumber, int secondObjectNumber)
{
	if (geometry_findDistance(POLYGON, firstObjectNumber, POLYGON, secondObjectNumber) <
		polygon[firstObjectNumber].radius + polygon[secondObjectNumber].radius)
	{
		return true;
	}
	else
		return false;
}

bool event_doAfter(double interval, int eventReference)
{
	return !(event_doFor(interval, eventReference));
}

bool event_doFor(double interval, int eventReference)
{
	static double remainingTime[100];

	if (remainingTime[eventReference] <= 0)
		remainingTime[eventReference] = interval;

	remainingTime[eventReference] -= (FRAME_TIME_MILLISECS / 1000);

	if (remainingTime[eventReference] > 0)
		return true;
	else
		return false;
}

bool event_hasFalleninAHole(unsigned char object, int objectNumber)
{
	if (polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius < 1)
		return true;
	else
		return false;
}

bool event_hasPolygonPastXLocation(int objectNumber, double xPosition)
{
	if (polygon[objectNumber].centre.xPosition > xPosition)
		return true;
	else
		return false;
}

bool event_hasPolygonPastYLocation(int objectNumber, double yPosition)
{
	if (polygon[objectNumber].centre.yPosition > yPosition)
		return true;
	else
		return false;
}

bool event_isPolygonHigher(int firstObjectNumber, int secondObjectNumber)
{
	if (polygon[firstObjectNumber].centre.yPosition > polygon[secondObjectNumber].centre.yPosition)
		return true;
	else
		return false;
}

bool event_isOnCycle(double interval)
{
	if (frameCount % (int)(FRAME_RATE * interval * 2) < (FRAME_RATE * interval))
		return true;
	else
		return false;
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
			if (event_isWithinPlatformWidth(object, objectNumber, platformNumber))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool event_isOnceEvery(double interval)
{
	if (frameCount % (int)(FRAME_RATE * interval) == 0)
		return true;
	else
		return false;
}

bool event_isOnInstant(int eventReference)
{
	static int callFrame[100] = {0};

	if (frameCount > 1)
	{
		if (callFrame[eventReference] == (frameCount - 1))
		{
			callFrame[eventReference] = frameCount;
			return false;
		}
		else
		{
			callFrame[eventReference] = frameCount;
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
			if (event_isWithinPlatformHeight(object, objectNumber, platformNumber))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
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
			if (event_isWithinPlatformHeight(object, objectNumber, platformNumber))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
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
			if (event_isWithinPlatformWidth(object, objectNumber, platformNumber))
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool event_isPolygonWithinRadius(int firstObjectNumber,
	double radius,
	int secondObjectNumber)
{
	if (geometry_findDistance(POLYGON, firstObjectNumber, POLYGON, secondObjectNumber) <= radius)
		return true;
	else
		return false;
}


bool event_isWithinPlatformHeight(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	if (polygon[objectNumber].centre.yPosition >
		block[platformNumber].centre.yPosition - (block[platformNumber].dimensions.height / 2) &&
		polygon[objectNumber].centre.yPosition <
		block[platformNumber].centre.yPosition + (block[platformNumber].dimensions.height / 2))
	{
		return true;
	}
	else
		return false;
}

bool event_isWithinPlatformWidth(unsigned char object,
	int objectNumber,
	int platformNumber)
{
	if (polygon[objectNumber].centre.xPosition >
		block[platformNumber].centre.xPosition - (block[platformNumber].dimensions.width / 2) &&
		polygon[objectNumber].centre.xPosition <
		block[platformNumber].centre.xPosition + (block[platformNumber].dimensions.width / 2))
	{
		return true;
	}
	else
		return false;
}

bool event_isWithinTime(double startTime, double endTime)
{
	if (timeCount >= startTime && timeCount <= endTime)
		return true;
	else
		return false;
}