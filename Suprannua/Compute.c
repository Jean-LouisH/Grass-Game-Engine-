#include "Definitions.h"

void compute_plotPolygon(int objectNumber)
{
    int i;

    for (i = 0; i < polygon[objectNumber].properties.edges; i++)
    {
        polygon[objectNumber].vertices[i].xPosition = polygon[objectNumber].centre.xPosition +
                (polygon[objectNumber].radius * cos(((360 / polygon[objectNumber].properties.edges) *
                                                    (i)) * (PI / 180)));
        polygon[objectNumber].vertices[i].yPosition = polygon[objectNumber].centre.yPosition +
                (polygon[objectNumber].radius * sin(((360 / polygon[objectNumber].properties.edges) *
                                                     (i)) * (PI / 180)));
    }//polygon defined sides divide a full circle into angle increments that are multiplied by j to plot all points.
}

void compute_plotBox(int objectNumber)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        box[objectNumber].vertices[i].xPosition = box[objectNumber].centre.xPosition + ((box[objectNumber].dimensions.width / 2)
                    * sqrt(2) * (cos((45 + (i * 90)) * (PI / 180))));
        box[objectNumber].vertices[i].yPosition = box[objectNumber].centre.yPosition + ((box[objectNumber].dimensions.height / 2)
                    * sqrt(2) * (sin((45 + (i * 90)) * (PI / 180))));
    }//All expected angles return a ratio of 1/sqrt(2). Sqrt(2) cancels this to give the circumscribed square size.
}

bool compute_isWithinPlatformRange(unsigned char object, int objectNumber, int platformNumber)
{
    bool platformFlag = false;

    if(polygon[objectNumber].centre.xPosition >
            box[platformNumber].centre.xPosition - (box[platformNumber].dimensions.width / 2) &&
        polygon[objectNumber].centre.xPosition <
            box[platformNumber].centre.xPosition + (box[platformNumber].dimensions.width / 2))
    {
        platformFlag = true;
    }

    return (platformFlag);
}

bool compute_isOnPlatform(unsigned char object, int objectNumber, int platformNumber)
{
    bool platformFlag = false;

    switch(object)
    {
        case POLYGON:
                        if(box[platformNumber].properties.classification == PLATFORM)
                        {
                            if(polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius <=
                                box[platformNumber].centre.yPosition + (box[platformNumber].dimensions.height / 2) &&
                               polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius >
                                box[platformNumber].centre.yPosition - (box[platformNumber].dimensions.height / 2))
                            {
                                if(compute_isWithinPlatformRange(object, objectNumber, platformNumber))
                                {
                                    platformFlag = true;
                                }
                            }
                        }
        break;
    }

    return (platformFlag);
}
bool compute_isTouchingUnderPlatform(unsigned char object, int objectNumber, int platformNumber)
{
    bool platformFlag = false;

    switch(object)
    {
        case POLYGON:
                        if(box[platformNumber].properties.classification == PLATFORM)
                        {
                            if (polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius >=
                                    box[platformNumber].centre.yPosition - (box[platformNumber].dimensions.height / 2) &&
                                polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius <
                                    box[platformNumber].centre.yPosition + (box[platformNumber].dimensions.height / 2))
                            {
                                if(compute_isWithinPlatformRange(object, objectNumber, platformNumber))
                                {
                                    platformFlag = true;
                                }
                            }
                        }
        break;
    }

    return (platformFlag);
}

void compute_detectPlatformCollision()
{
    int i;
    int j;

    for(i = 0; i < MAX_POLYGONS; i++)
    {
        for(j = 0; j < MAX_BOXES; j++)
        {
            if(polygon[i].properties.classification == ENTITY)
            {
                if(compute_isOnPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
                        polygon[i].properties.bouncePercentage; //Allow bounce on top
                    polygon[i].centre.yPosition = box[j].centre.yPosition + (box[j].dimensions.height / 2) + polygon[i].radius;
                    //Adjust the polygon on top of the platform.
                }
                else if(compute_isTouchingUnderPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 *
                        polygon[i].properties.bouncePercentage; //Allow bounce below
                    polygon[i].centre.yPosition = box[j].centre.yPosition - (box[j].dimensions.height / 2) - polygon[i].radius;
                }
            }
        }
    }
}

void compute_transform()
{
    int i;
    int j;

    for (i = 0; i < MAX_POLYGONS; i++)
	{
		//X Axis
		polygon[i].centre.xPosition += (polygon[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < polygon[i].properties.edges; j++)
		{
			polygon[i].vertices[j].xPosition +=
				(polygon[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
		//Y Axis
		polygon[i].centre.yPosition += (polygon[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < polygon[i].properties.edges; j++)
		{
			polygon[i].vertices[j].yPosition +=
				(polygon[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
	}

	for (i = 0; i < MAX_BOXES; i++)
	{
		//X Axis
		box[i].centre.xPosition += (box[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < 4; j++)
		{
			box[i].vertices[j].xPosition +=
				(box[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
		//Y Axis
		box[i].centre.yPosition += (box[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < 4; j++)
		{
			box[i].vertices[j].yPosition +=
				(box[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
	}

	//Rotation
	for (i = 0; i < MAX_POLYGONS; i++)
	{
		while (polygon[i].properties.angle >= 360)
			polygon[i].properties.angle -= 360;
        while (polygon[i].properties.angle < 0)
            polygon[i].properties.angle += 360;

		for (j = 0; j < polygon[i].properties.edges; j++)
		{
			polygon[i].vertices[j].xPosition = polygon[i].centre.xPosition +
				(polygon[i].radius * cos(((360 / polygon[i].properties.edges) *
                (j) - polygon[i].properties.angle) * (PI / 180)));
            polygon[i].vertices[j].yPosition = polygon[i].centre.yPosition +
				(polygon[i].radius * sin(((360 / polygon[i].properties.edges) *
                (j) - polygon[i].properties.angle) * (PI / 180)));
		}
	}
}
void compute_incrementTime()
{
    timeCount = (frameCount * FRAME_DELAY_MILLISECS) * 0.001;
}

void compute_gravitate(unsigned char object, int objectNumber, bool direction)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.yVelocity += ((direction * 2) - 1) * platformGravity *
                        FRAME_DELAY_MILLISECS * 0.001;
        break;
        case BOX:       box[objectNumber].properties.yVelocity += ((direction * 2) - 1) * platformGravity *
                        FRAME_DELAY_MILLISECS * 0.001;
        break;
    }
}

void compute_rigidBodyDynamics()
{
    //polygon[i].properties.angle
    //platformGravity
    //polygon[i].properties.xVelocity
}

void compute_roll(unsigned char object, int objectNumber)
{
    switch(object)
    {
        case POLYGON:
                        if(polygon[objectNumber].properties.xVelocity < 0)
                            AI_spin(POLYGON, objectNumber, ANTICLOCKWISE,
                                    -1 * (polygon[objectNumber].properties.xVelocity / polygon[objectNumber].radius)
                                     * (FRAME_RATE));
                        else if(polygon[objectNumber].properties.xVelocity > 0)
                            AI_spin(POLYGON, objectNumber, CLOCKWISE,
                                    (polygon[objectNumber].properties.xVelocity / polygon[objectNumber].radius)
                                    * (FRAME_RATE));
        break;
    }
}

void compute_limitBoundary()
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
