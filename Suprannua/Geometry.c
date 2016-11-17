#include "Definitions.h"

void geometry_plotPolygon(int objectNumber)
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

void geometry_plotBox(int objectNumber)
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

void geometry_transform()
{
    int i;
    int j;

    for (i = 0; i < MAX_POLYGONS; i++)
	{
		//X Axis
		polygon[i].centre.xPosition += (polygon[i].properties.xVelocity / FRAME_RATE);
		for (j = 0; j < polygon[i].properties.edges; j++)
		{
			polygon[i].vertices[j].xPosition +=
				(polygon[i].properties.xVelocity / FRAME_RATE);
		}
		//Y Axis
		polygon[i].centre.yPosition += (polygon[i].properties.yVelocity / FRAME_RATE);
		for (j = 0; j < polygon[i].properties.edges; j++)
		{
			polygon[i].vertices[j].yPosition +=
				(polygon[i].properties.yVelocity / FRAME_RATE);
		}
	}

	for (i = 0; i < MAX_BOXES; i++)
	{
		//X Axis
		box[i].centre.xPosition += (box[i].properties.xVelocity / FRAME_RATE);
		for (j = 0; j < 4; j++)
		{
			box[i].vertices[j].xPosition +=
				(box[i].properties.xVelocity / FRAME_RATE);
		}
		//Y Axis
		box[i].centre.yPosition += (box[i].properties.yVelocity / FRAME_RATE);
		for (j = 0; j < 4; j++)
		{
			box[i].vertices[j].yPosition +=
				(box[i].properties.yVelocity / FRAME_RATE);
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
