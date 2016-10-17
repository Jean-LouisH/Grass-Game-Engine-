#include "Definitions.h"
#include "Compute.h"

void compute_plotPolygon(int objectNumber)
{
    for (j = 0; j < polygon[k].properties.sides; j++)
    {
        polygon[k].vertices[j].xPosition = polygon[k].centre.xPosition +
                (polygon[k].radius * cos(((360 / polygon[k].properties.sides) * (j)) * (PI / 180)));
        polygon[k].vertices[j].yPosition = polygon[k].centre.yPosition +
                (polygon[k].radius * sin(((360 / polygon[k].properties.sides) * (j)) * (PI / 180)));
    }//polygon defined sides divide a full circle into angle increments that are multiplied by j to plot all points.
}

bool compute_isOnPlatform(unsigned char firstObject, int firstObjectNumber, unsigned char secondObject, int secondObjectNumber)
{
    if(box[secondObjectNumber].properties.classification == PLATFORM)
    {
        if(polygon[0].centre.yPosition - polygon[0].radius <=
            box[i].centre.yPosition + (box[i].boxHeight / 2) &&
           polygon[0].centre.yPosition - polygon[0].radius >
            box[i].centre.yPosition - (box[i].boxHeight / 2))
        {
            if(polygon[0].centre.xPosition >
                box[i].centre.xPosition - (box[i].boxWidth / 2) &&
            polygon[0].centre.xPosition <
                box[i].centre.xPosition + (box[i].boxWidth / 2))
                ;
        }//to be completed.
    }
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

void compute_detectPlatformCollision()
{
    for(i = 0; i < MAX_POLYGONS; i++)
    {
        for(j = 0; j < MAX_BOXES; j++)
        {
            if(box[j].properties.classification == PLATFORM &&
               polygon[i].properties.classification == ENTITY)
            {
                if(polygon[i].centre.xPosition >
                        box[j].centre.xPosition - (box[j].boxWidth / 2) &&
                    polygon[i].centre.xPosition <
                        box[j].centre.xPosition + (box[j].boxWidth / 2))//If the centre is within the platform length.
                {
                    if(polygon[i].centre.yPosition - polygon[i].radius <
                            box[j].centre.yPosition + (box[j].boxHeight / 2) &&
                        polygon[i].centre.yPosition - polygon[i].radius >
                            box[j].centre.yPosition - (box[j].boxHeight / 2)) //If on top of platform.
                    {
                        polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 * friction; //Allow bounce on top
                        polygon[i].centre.yPosition = box[j].centre.yPosition + (box[j].boxHeight / 2) + polygon[i].radius;
                        //Adjust the polygon on top of the platform.
                    }
                    else if(polygon[i].centre.yPosition + polygon[i].radius >
                                box[j].centre.yPosition - (box[j].boxHeight / 2) &&
                            polygon[i].centre.yPosition + polygon[i].radius <
                                box[j].centre.yPosition + (box[j].boxHeight / 2))
                    {
                        polygon[i].properties.yVelocity = -30.0; //Allow bounce below
                        polygon[i].centre.yPosition = box[j].centre.yPosition - (box[j].boxHeight / 2) - polygon[i].radius;
                    }
                }
            }
        }
    }
    for(i = 0; i < MAX_BOXES; i++)
    {
        if((box[i].centre.yPosition) - (box[i].boxHeight/2) <= 0)
        {
            box[i].properties.yVelocity = box[i].properties.yVelocity * -1 * friction;

            if(box[i].properties.yVelocity < 0.01)
                box[i].properties.yVelocity = platformGravity;
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

		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			polygon[i].vertices[j].xPosition = polygon[i].centre.xPosition +
				(polygon[i].radius * cos(((360 / polygon[i].properties.sides) *
                (j) - polygon[i].properties.angle) * (PI / 180)));
            polygon[i].vertices[j].yPosition = polygon[i].centre.yPosition +
				(polygon[i].radius * sin(((360 / polygon[i].properties.sides) *
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
		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			polygon[i].vertices[j].xPosition +=
				(polygon[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
		//Y Axis
		polygon[i].centre.yPosition += (polygon[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < polygon[i].properties.sides; j++)
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

void compute_gravitate(unsigned char object, int objectNumber)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.yVelocity -= platformGravity *
                        FRAME_DELAY_MILLISECS * 0.001;
        break;
        case BOX:       box[objectNumber].properties.yVelocity -= platformGravity *
                        FRAME_DELAY_MILLISECS * 0.001;
        break;
    }
}

void compute_rigidBodyDynamics()
{
    for(i = 0; i < MAX_POLYGONS; i++)
    {
        //polygon[i].properties.angle
        //platformGravity
        //polygon[i].properties.xVelocity
    }
}

void compute_roll(unsigned char object, int objectNumber)
{
    switch(object)
    {
    case POLYGON:      //if(polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius < 1)
                    if(polygon[objectNumber].properties.xVelocity < 0)
                        AI_spin(POLYGON, objectNumber, ANTICLOCKWISE,
                                -1 * (polygon[objectNumber].properties.xVelocity / polygon[objectNumber].radius)
                                 * (1000/FRAME_DELAY_MILLISECS));
                    else if(polygon[objectNumber].properties.xVelocity > 0)
                        AI_spin(POLYGON, objectNumber, CLOCKWISE,
                                (polygon[objectNumber].properties.xVelocity / polygon[objectNumber].radius)
                                * (1000/FRAME_DELAY_MILLISECS));
    break;
    /*case BOX:          if(box[objectNumber].properties.xVelocity < 0)
                            box[objectNumber].properties.angle -= dpadSensitivity / 1;
                        else if(box[objectNumber].properties.xVelocity > 0)
                            box[objectNumber].properties.angle += dpadSensitivity / 1;
    break;*/
    }//might exclude boxes.
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
