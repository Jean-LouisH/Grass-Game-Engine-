#include "Definitions.h"
#include "Compute.h"

void compute_plotPolygon(int objectNumber)
{
    for (j = 0; j < polygon[k].properties.edges; j++)
    {
        polygon[k].vertices[j].xPosition = polygon[k].centre.xPosition +
                (polygon[k].radius * cos(((360 / polygon[k].properties.edges) * (j)) * (PI / 180)));
        polygon[k].vertices[j].yPosition = polygon[k].centre.yPosition +
                (polygon[k].radius * sin(((360 / polygon[k].properties.edges) * (j)) * (PI / 180)));
    }//polygon defined sides divide a full circle into angle increments that are multiplied by j to plot all points.
}

void compute_plotBox(int objectNumber)
{
    for (j = 0; j < 4; j++)
    {
        box[k].vertices[j].xPosition = box[k].centre.xPosition + ((box[k].boxWidth / 2)
                    * sqrt(2) * (cos((45 + (j * 90)) * (PI / 180))));
        box[k].vertices[j].yPosition = box[k].centre.yPosition + ((box[k].boxHeight / 2)
                    * sqrt(2) * (sin((45 + (j * 90)) * (PI / 180))));
    }//All expected angles return a ratio of 1/sqrt(2). Sqrt(2) cancels this to give the circumscribed square size.
}

bool compute_isWithinPlatformRange(unsigned char object, int objectNumber, int platformNumber)
{
    bool platformFlag = false;

    if(polygon[objectNumber].centre.xPosition >
            box[platformNumber].centre.xPosition - (box[platformNumber].boxWidth / 2) &&
        polygon[objectNumber].centre.xPosition <
            box[platformNumber].centre.xPosition + (box[platformNumber].boxWidth / 2))
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
                                box[platformNumber].centre.yPosition + (box[platformNumber].boxHeight / 2) &&
                               polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius >
                                box[platformNumber].centre.yPosition - (box[platformNumber].boxHeight / 2))
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
                                    box[platformNumber].centre.yPosition - (box[platformNumber].boxHeight / 2) &&
                                polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius <
                                    box[platformNumber].centre.yPosition + (box[platformNumber].boxHeight / 2))
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
    for(i = 0; i < MAX_POLYGONS; i++)
    {
        for(j = 0; j < MAX_BOXES; j++)
        {
            if(polygon[i].properties.classification == ENTITY)
            {
                if(compute_isOnPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 * bouncePercentage; //Allow bounce on top
                    polygon[i].centre.yPosition = box[j].centre.yPosition + (box[j].boxHeight / 2) + polygon[i].radius;
                    //Adjust the polygon on top of the platform.
                }
                else if(compute_isTouchingUnderPlatform(POLYGON, i, j))
                {
                    polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 * bouncePercentage; //Allow bounce below
                    polygon[i].centre.yPosition = box[j].centre.yPosition - (box[j].boxHeight / 2) - polygon[i].radius;
                }
            }
        }
    }
}

void compute_rotate()
{
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

void compute_translate()
{
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
	for (i = 0; i < MAX_POLYGONS; i++)
	{
		//X Axis
		if(polygon[i].centre.xPosition + polygon[i].radius >= worldMap.width)
            polygon[i].centre.xPosition = worldMap.width - polygon[i].radius;

        else if (polygon[i].centre.xPosition - polygon[i].radius <= 0)
            polygon[i].centre.xPosition = 0 + polygon[i].radius;
	}
}
