#include "Suprannua.h"

void physics_detectPlatformCollision()
{
    int i;
    int j;

    for(i = 0; i <= occupiedPolygons; i++)
    {
        if(polygon[i].properties.classification == ENTITY)
        {
            for(j = 0; j <= occupiedBlocks; j++)
            {
                if(logic_isOnPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
							polygon[i].properties.bouncePercentage; //Allow bounce on top

                    polygon[i].centre.yPosition = block[j].centre.yPosition + (block[j].dimensions.height / 2) + polygon[i].radius;
                    //Adjust the polygon on top of the platform.
                }
                if(logic_isTouchingUnderPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
							polygon[i].properties.bouncePercentage; //Allow bounce below

                    polygon[i].centre.yPosition = block[j].centre.yPosition - (block[j].dimensions.height / 2) - polygon[i].radius;
                }
            }
        }
    }
}

void physics_detectCollision()
{
    int i;
    int j;

    double centreDistance;
    double combinedRadius;
	double gradient;
	double xVelocityStore;
	double yVelocityStore;

    for(i = 0; i <= occupiedPolygons; i++)
    {
        if(polygon[i].properties.classification == ENTITY)
        {
            for(j = 0; j <= occupiedPolygons; j++)
            {
                if(j != i && polygon[j].properties.classification == ENTITY)
                {
                    centreDistance = geometry_findDistance(POLYGON, i, POLYGON, j);
                    combinedRadius = polygon[i].radius + polygon[j].radius;

                    if(centreDistance < combinedRadius)
                    {
						/*gradient = (polygon[i].centre.yPosition / polygon[i].centre.xPosition);
						polygon[i].centre.xPosition = polygon[j].centre.xPosition  - sqrt(pow(combinedRadius, 2) - 
														pow(polygon[i].centre.yPosition - 
														polygon[j].centre.yPosition, 2));
						polygon[i].centre.yPosition = gradient * polygon[i].centre.xPosition;*/

						/*xVelocityStore = polygon[i].properties.xVelocity;
						polygon[i].properties.xVelocity = polygon[j].properties.xVelocity;
						polygon[j].properties.xVelocity = xVelocityStore;

						yVelocityStore = polygon[i].properties.yVelocity;
						polygon[i].properties.yVelocity = polygon[j].properties.yVelocity;
						polygon[j].properties.yVelocity = yVelocityStore;*/
                    }
                }
            }
        }
    }
}

void physics_incrementTime()
{
    timeCount = frameCount / FRAME_RATE;
}

void physics_gravitate(unsigned char object, int objectNumber, bool direction)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.yVelocity += ((direction * 2) - 1) * platformGravity / FRAME_RATE;
        break;
        case BLOCK:       block[objectNumber].properties.yVelocity += ((direction * 2) - 1) / FRAME_RATE;
        break;
    }
}

void physics_rigidBodyDynamics()
{
    //polygon[i].properties.angle
    //platformGravity
    //polygon[i].properties.xVelocity
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

void physics_limitBoundary()
{
    int i;

	for (i = 0; i <= occupiedPolygons; i++)
	{
	    if(polygon[i].properties.classification != NOTHING)
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

void physics_force(unsigned char firstObject, int firstObjectNumber,
                 unsigned char preposition, unsigned char secondObject, int secondobjectNumber)// preposition - "to", "from"
{

}
