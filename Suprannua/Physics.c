#include "Definitions.h"

void physics_detectPlatformCollision()
{
    int i;
    int j;

    for(i = 0; i < MAX_POLYGONS; i++)
    {
        for(j = 0; j < MAX_BOXES; j++)
        {
            if(polygon[i].properties.classification == ENTITY)
            {
                if(logic_isOnPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
                        polygon[i].properties.bouncePercentage; //Allow bounce on top
                    polygon[i].centre.yPosition = box[j].centre.yPosition + (box[j].dimensions.height / 2) + polygon[i].radius;
                    //Adjust the polygon on top of the platform.
                }
                else if(logic_isTouchingUnderPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
                        polygon[i].properties.bouncePercentage; //Allow bounce below
                    polygon[i].centre.yPosition = box[j].centre.yPosition - (box[j].dimensions.height / 2) - polygon[i].radius;
                }
            }
        }
    }
}

void physics_incrementTime()
{
    timeCount = (frameCount * FRAME_DELAY_MILLISECS) * 0.001;
}

void physics_gravitate(unsigned char object, int objectNumber, bool direction)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.yVelocity += ((direction * 2) - 1) * platformGravity / FRAME_RATE;
        break;
        case BOX:       box[objectNumber].properties.yVelocity += ((direction * 2) - 1) / FRAME_RATE;
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

	for (i = 0; i < MAX_POLYGONS; i++)
	{
		//X Axis
		if(polygon[i].centre.xPosition + polygon[i].radius >= worldSizeMetres.width)
            polygon[i].centre.xPosition = worldSizeMetres.width - polygon[i].radius;

        else if (polygon[i].centre.xPosition - polygon[i].radius <= 0)
            polygon[i].centre.xPosition = 0 + polygon[i].radius;
	}
}
