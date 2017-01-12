#include "Suprannua.h"

void physics_detectPlatformCollision()
{
    int i;
    int j;

    for(i = 0; i <= storedPolygons; i++)
    {
        if(polygon[i].properties.classification == ENTITY)
        {
            for(j = 0; j <= storedBlocks; j++)
            {
				if (block[j].properties.classification == PLATFORM)
				{
					if (event_isOnPlatform(POLYGON, i, j))
					{
						//Allow bounce on top
						polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
							polygon[i].properties.bouncePercentage;

						//Adjust the polygon on top of the platform.
						polygon[i].centre.yPosition = block[j].centre.yPosition +
							(block[j].dimensions.height / 2) + polygon[i].radius;
					}
					if (event_isTouchingUnderPlatform(POLYGON, i, j))
					{
						//Allow bounce below
						polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
							polygon[i].properties.bouncePercentage;

						polygon[i].centre.yPosition = block[j].centre.yPosition -
							(block[j].dimensions.height / 2) - polygon[i].radius;
					}
				}
            }
        }
    }
}

void physics_detectPolygonCollision()
{
	int i;
	int j;

	double centreDistance;
	double combinedRadius;
	double positionAngle;
	double xDelta;
	double yDelta;
	double iTheta;
	double jTheta;
	double iVelocity;
	double jVelocity;
	double iCollisionAngleRatio;
	double jCollisionAngleRatio;

	for(i = 0; i <= storedPolygons; i++)
	{
		for(j = 0; j <= storedPolygons; j++)
		{
			if(j != i && polygon[j].properties.classification == polygon[i].properties.classification)
			{
				centreDistance = geometry_findDistance(POLYGON, i, POLYGON, j);
				combinedRadius = polygon[i].radius + polygon[j].radius;

				if(centreDistance < combinedRadius)
				{
					positionAngle = atan2(polygon[j].centre.yPosition - polygon[i].centre.yPosition,
						polygon[j].centre.xPosition - polygon[i].centre.xPosition);

					/*2D Linear Momentum Elastic Collision Response.
						*
						* Based on final velocity equations of two moving objects.
						*
						* v'_x1 =	(v_1 * cos(theta_1 - positionAngle)(m_1 - m_2) + 2m_2 * v_2 *
						*			cos(theta_2 - positionAngle)) / (m_1 + m_2) * (cos(positionAngle) +
						*			v_1 sin(theta_1 - positionAngle) * cos(positionAngle + pi/2))
						*
						* v'_y1 =	(v_1 * cos(theta_1 - positionAngle)(m_1 - m_2) + 2m_2 * v_2 *
						*			cos(theta_2 - positionAngle)) / (m_1 + m_2) * (sin(positionAngle) +
						*			v_1 sin(theta_1 - positionAngle) * sin(positionAngle + pi/2))
						*
						*/

					iTheta = atan2(polygon[i].properties.yVelocity, polygon[i].properties.xVelocity);
					jTheta = atan2(polygon[j].properties.yVelocity, polygon[j].properties.xVelocity);
					iVelocity = hypot(polygon[i].properties.xVelocity, polygon[i].properties.yVelocity);
					jVelocity = hypot(polygon[j].properties.xVelocity, polygon[j].properties.yVelocity);
					iCollisionAngleRatio = ((iVelocity * cos(iTheta - positionAngle) *
										(polygon[i].properties.mass - polygon[j].properties.mass) +
										(2 * polygon[j].properties.mass * jVelocity * cos(jTheta - positionAngle))) /
										(polygon[i].properties.mass + polygon[j].properties.mass));
					jCollisionAngleRatio = ((jVelocity * cos(jTheta - positionAngle) *
										(polygon[j].properties.mass - polygon[i].properties.mass) +
										(2 * polygon[i].properties.mass * iVelocity * cos(iTheta - positionAngle))) /
										(polygon[j].properties.mass + polygon[i].properties.mass));
						
					//First polygon
					polygon[i].properties.xVelocity = (iCollisionAngleRatio *
													cos(positionAngle) + (iVelocity * sin(iTheta - positionAngle) *
													cos(positionAngle + (PI / 2)))) * polygon[i].properties.bouncePercentage;
						
					polygon[i].properties.yVelocity = (iCollisionAngleRatio *
													sin(positionAngle) + (iVelocity * sin(iTheta - positionAngle) *
													sin(positionAngle + (PI / 2)))) * polygon[i].properties.bouncePercentage;
						
					//Second polygon.
					polygon[j].properties.xVelocity = (jCollisionAngleRatio *
													cos(positionAngle) + (jVelocity * sin(jTheta - positionAngle) *
													cos(positionAngle + (PI / 2)))) * polygon[j].properties.bouncePercentage;
						
					polygon[j].properties.yVelocity = (jCollisionAngleRatio *
													sin(positionAngle) + (jVelocity * sin(jTheta - positionAngle) *
													sin(positionAngle + (PI / 2)))) * polygon[j].properties.bouncePercentage;
				}
			}
		}

		for (j = 0; j <= storedPolygons; j++)
		{
			if (j != i && polygon[j].properties.classification == ENTITY)
			{
				centreDistance = geometry_findDistance(POLYGON, i, POLYGON, j);
				combinedRadius = polygon[i].radius + polygon[j].radius;

				if (centreDistance < combinedRadius)
				{
					positionAngle = atan2(polygon[j].centre.yPosition - polygon[i].centre.yPosition,
						polygon[j].centre.xPosition - polygon[i].centre.xPosition);

					/* Prevents polygons from clipping into each other before frame is rendered.
					*
					* Derived from complex equation:
					*
					* r = sqrt((xDelta)^2 + (yDelta)^2)
					*
					*/

					xDelta = (combinedRadius)* cos(positionAngle);
					yDelta = (combinedRadius)* sin(positionAngle);

					polygon[i].centre.xPosition = polygon[j].centre.xPosition - xDelta;
					polygon[i].centre.yPosition = polygon[j].centre.yPosition - yDelta;

					//geometry_plotPolygon(i);
				}
			}
		}
	}
}

void physics_incrementTime()
{
    timeCount = frameCount / FRAME_RATE;
}

void physics_force(unsigned char firstObject, int firstObjectNumber,
	unsigned char preposition, unsigned char secondObject, int secondObjectNumber)// preposition - "to", "from"
{
	double force;
	double positionAngle;

	if (firstObjectNumber != secondObjectNumber && polygon[firstObjectNumber].properties.classification ==
		polygon[secondObjectNumber].properties.classification)
	{
		positionAngle = atan2(polygon[secondObjectNumber].centre.yPosition - polygon[firstObjectNumber].centre.yPosition,
			polygon[secondObjectNumber].centre.xPosition - polygon[firstObjectNumber].centre.xPosition);

		force = (gravityConstant * polygon[firstObjectNumber].properties.mass * polygon[secondObjectNumber].properties.mass) /
			pow(hypot(polygon[secondObjectNumber].centre.xPosition - polygon[firstObjectNumber].centre.xPosition,
				polygon[secondObjectNumber].centre.yPosition - polygon[firstObjectNumber].centre.yPosition), 2);

		switch (preposition)
		{
		case TO:;						break;
		case FROM: force = force * -1;	break;
		}

		polygon[firstObjectNumber].properties.xVelocity += (force / polygon[firstObjectNumber].properties.mass) * cos(positionAngle) / FRAME_RATE;
		polygon[firstObjectNumber].properties.yVelocity += (force / polygon[firstObjectNumber].properties.mass) * sin(positionAngle) / FRAME_RATE;
	}
}

void physics_gravitate(unsigned char object, int objectNumber, bool direction)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.yVelocity += ((direction * 2) - 1) * platformGravity / FRAME_RATE;
        break;
        case BLOCK:       block[objectNumber].properties.yVelocity += ((direction * 2) - 1) * platformGravity / FRAME_RATE;
        break;
    }
}

void physics_limitBoundary()
{
	int i;

	for (i = 0; i <= storedPolygons; i++)
	{
		if (polygon[i].properties.classification != NOTHING)
		{
			//X Axis
			if (polygon[i].centre.xPosition + polygon[i].radius >= worldSizeMetres.width)
			{
				polygon[i].centre.xPosition = worldSizeMetres.width - polygon[i].radius;
				polygon[i].properties.xVelocity = -1 * polygon[i].properties.xVelocity;
			}
			else if (polygon[i].centre.xPosition - polygon[i].radius <= 0)
			{
				polygon[i].centre.xPosition = 0 + polygon[i].radius;
				polygon[i].properties.xVelocity = -1 * polygon[i].properties.xVelocity;
			}

			//Y Axis
			if (polygon[i].centre.yPosition + polygon[i].radius >= worldSizeMetres.height)
			{
				polygon[i].centre.yPosition = worldSizeMetres.height - polygon[i].radius;
				polygon[i].properties.yVelocity = -1 * polygon[i].properties.yVelocity;
			}
			else if (polygon[i].centre.yPosition - polygon[i].radius <= 0)
			{
				polygon[i].centre.yPosition = 0 + polygon[i].radius;
				polygon[i].properties.yVelocity = -1 * polygon[i].properties.yVelocity;
			}
		}
	}
}

void physics_resistRolling(unsigned char object, int objectNumber, double deceleration)
{
	if (polygon[objectNumber].properties.xVelocity > 0)
	{
		edit_adjust(POLYGON, objectNumber, XVELOCITY, (-1 * deceleration));
		if (polygon[objectNumber].properties.xVelocity < 0)
			polygon[objectNumber].properties.xVelocity = 0;
	}
	else if (polygon[objectNumber].properties.xVelocity < 0)
	{
		edit_adjust(POLYGON, objectNumber, XVELOCITY, (deceleration));
		if (polygon[objectNumber].properties.xVelocity > 0)
			polygon[objectNumber].properties.xVelocity = 0;
	}
}

void physics_roll(unsigned char object, int objectNumber)
{
    switch(object)
    {
        case POLYGON:
                        if(polygon[objectNumber].properties.xVelocity < 0)
                            AI_spin(POLYGON, objectNumber, ANTICLOCKWISE,
                                    -1 * (polygon[objectNumber].properties.xVelocity / polygon[objectNumber].radius)
                                     / (PI / 180));
                        else if(polygon[objectNumber].properties.xVelocity > 0)
                            AI_spin(POLYGON, objectNumber, CLOCKWISE,
                                    (polygon[objectNumber].properties.xVelocity / polygon[objectNumber].radius)
                                    / (PI / 180));
        break;
    }
}
