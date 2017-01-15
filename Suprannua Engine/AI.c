#include "SuprannuaEngine.h"

void AI_avoid(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{
	double positionAngle;

	positionAngle = atan2(polygon[objectNumber].centre.yPosition - polygon[agentNumber].centre.yPosition,
		polygon[objectNumber].centre.xPosition - polygon[agentNumber].centre.xPosition);

	polygon[agentNumber].properties.xVelocity = -1 * dpadSensitivity * cos(positionAngle);
	if (polygon[agentNumber].properties.classification == AIRBOURNE)
		polygon[agentNumber].properties.yVelocity = dpadSensitivity * sin(positionAngle);
	else if(event_isPolygonHigher(agentNumber, objectNumber))
		AI_jump(POLYGON, agentNumber, 40);
}

void AI_catch(unsigned char agent, int agentNumber, unsigned char object, int objectNumber, bool followX, bool followY)
{
	double positionAngle;

	positionAngle = atan2(polygon[objectNumber].centre.yPosition - polygon[agentNumber].centre.yPosition,
		polygon[objectNumber].centre.xPosition - polygon[agentNumber].centre.xPosition);

	if (followY)
	{
		if ((event_hasPolygonPastXLocation(agentNumber, polygon[objectNumber].centre.xPosition) &&
			polygon[objectNumber].properties.xVelocity < 0) ||
			(!event_hasPolygonPastXLocation(agentNumber, polygon[objectNumber].centre.xPosition) &&
				polygon[objectNumber].properties.xVelocity > 0))
		{
			polygon[agentNumber].properties.yVelocity = dpadSensitivity * sin(positionAngle);
		}
	}

	if (followX)
	{
		if ((event_hasPolygonPastXLocation(agentNumber, polygon[objectNumber].centre.xPosition) &&
			polygon[objectNumber].properties.xVelocity < 0) ||
			(!event_hasPolygonPastXLocation(agentNumber, polygon[objectNumber].centre.xPosition) &&
				polygon[objectNumber].properties.xVelocity > 0))
		{
			polygon[agentNumber].properties.yVelocity = dpadSensitivity * sin(positionAngle);
		}
	}
}

void AI_follow(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{
	double positionAngle;

	positionAngle = atan2(polygon[objectNumber].centre.yPosition - polygon[agentNumber].centre.yPosition,
		polygon[objectNumber].centre.xPosition - polygon[agentNumber].centre.xPosition);

	polygon[agentNumber].properties.xVelocity = dpadSensitivity * cos(positionAngle);
	if (polygon[agentNumber].properties.classification == AIRBOURNE)
		polygon[agentNumber].properties.yVelocity = dpadSensitivity * sin(positionAngle);
	else if (!event_isPolygonHigher(agentNumber, objectNumber))
		AI_jump(POLYGON, agentNumber, 40);
}

void AI_jump(unsigned char agent, int agentNumber, double jumpVelocity)
{
	int i;

	for (i = 0; i <= storedBlocks; i++)
	{
		if (event_isOnPlatform(POLYGON, agentNumber, i))
		{
			edit_change(POLYGON, agentNumber, YVELOCITY, jumpVelocity + block[i].properties.yVelocity);
			break;
		}
		else if (event_isTouchingUnderPlatform(POLYGON, agentNumber, i))
		{
			edit_change(POLYGON, agentNumber, YVELOCITY, -1 * jumpVelocity + block[i].properties.yVelocity);
			break;
		}
	}
	for (i = 0; i <= storedPolygons; i++)
	{
		if (event_isPolygonHigher(agentNumber, i) && event_arePolygonsTouching(agentNumber, i))
		{
			edit_change(POLYGON, agentNumber, YVELOCITY, jumpVelocity + polygon[i].properties.yVelocity);
			break;
		}
	}
}

void AI_listen()
{

}

void AI_mimic(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{

}

void AI_shoot(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{
	double positionAngle;

	positionAngle = atan2(polygon[objectNumber].centre.yPosition - polygon[agentNumber].centre.yPosition,
		polygon[objectNumber].centre.xPosition - polygon[agentNumber].centre.xPosition);

	edit_createPolygon(	AIRBOURNE, 12, 0.5, polygon[agentNumber].centre.xPosition + polygon[agentNumber].radius + 0.001,
						polygon[agentNumber].centre.yPosition, WHITE);

	polygon[storedPolygons].properties.xVelocity = dpadSensitivity * cos(positionAngle);
	polygon[storedPolygons].properties.yVelocity = dpadSensitivity * sin(positionAngle);
}

void AI_signal(unsigned char message)
{

}

void AI_spin(unsigned char agent, int agentNumber, bool direction, double amount)
{
	switch (agent)
	{
		/*((direction * 2) - 1) is used to alternate between -1 and +1 from
		* direction values of either 0 or 1.
		*
		* ((0 * 2) - 1) = -1
		* ((1 * 2) - 1) = +1
		*/

		case POLYGON:   polygon[agentNumber].properties.angle +=
						((direction * 2) - 1) * (amount / (FRAME_RATE));
		break;
	}
}

void AI_travel(unsigned char agent, int agentNumber, double toXPosition, double toYPosition, double Velocity)
{
	double positionAngle;

	positionAngle = atan2(toYPosition - polygon[agentNumber].centre.yPosition,
		toXPosition - polygon[agentNumber].centre.xPosition);

	polygon[agentNumber].properties.xVelocity = dpadSensitivity * cos(positionAngle);
	if (polygon[agentNumber].properties.classification == AIRBOURNE)
		polygon[agentNumber].properties.yVelocity = dpadSensitivity * sin(positionAngle);
	else if (polygon[agentNumber].centre.yPosition < toYPosition)
		AI_jump(POLYGON, agentNumber, 40);
}