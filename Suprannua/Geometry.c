#include "Suprannua.h"

double geometry_findDistance(	unsigned char firstObject,
								int firstObjectNumber,
								unsigned char secondObject,
								int secondObjectNumber)
{
	if (firstObject == POLYGON)
	{
		if (secondObject == POLYGON)
			return (hypot(polygon[firstObjectNumber].centre.xPosition -
				polygon[secondObjectNumber].centre.xPosition,
				polygon[firstObjectNumber].centre.yPosition -
				polygon[secondObjectNumber].centre.yPosition));
		else if (secondObject == BLOCK)
			return (hypot(polygon[firstObjectNumber].centre.xPosition -
				block[secondObjectNumber].centre.xPosition,
				polygon[firstObjectNumber].centre.yPosition -
				block[secondObjectNumber].centre.yPosition));
		else
			return 0.0;
	}
	else if (firstObject == BLOCK)
	{
		if (secondObject == POLYGON)
			return (hypot(block[firstObjectNumber].centre.xPosition -
					polygon[secondObjectNumber].centre.xPosition,
					block[firstObjectNumber].centre.yPosition -
					polygon[secondObjectNumber].centre.yPosition));
		else if (secondObject == BLOCK)
			return (hypot(block[firstObjectNumber].centre.xPosition -
					block[secondObjectNumber].centre.xPosition,
					block[firstObjectNumber].centre.yPosition -
					block[secondObjectNumber].centre.yPosition));
		else
			return 0.0;
	}
}

void geometry_plotBlock(int objectNumber)
{
	int i;

	/*All expected angles return a ratio of 1/sqrt(2). Sqrt(2) cancels this to give the circumscribed square size.*/
	for (i = 0; i < 4; i++)
	{
		block[objectNumber].vertices[i].xPosition = block[objectNumber].centre.xPosition + ((block[objectNumber].dimensions.width / 2)
			* sqrt(2) * (cos((45 + (i * 90)) * (PI / 180))));
		block[objectNumber].vertices[i].yPosition = block[objectNumber].centre.yPosition + ((block[objectNumber].dimensions.height / 2)
			* sqrt(2) * (sin((45 + (i * 90)) * (PI / 180))));
	}
}

void geometry_plotPolygon(int objectNumber)
{
    int i;

	/* Polygon defined sides divide a full circle into angle increments that are multiplied by i to plot all points.*/
    for (i = 0; i < polygon[objectNumber].properties.edges; i++)
    {
        polygon[objectNumber].vertices[i].xPosition = polygon[objectNumber].centre.xPosition +
                (polygon[objectNumber].radius * cos(((360 / polygon[objectNumber].properties.edges) *
					(i)) * (PI / 180)));
        polygon[objectNumber].vertices[i].yPosition = polygon[objectNumber].centre.yPosition +
                (polygon[objectNumber].radius * sin(((360 / polygon[objectNumber].properties.edges) *
					(i)) * (PI / 180)));
    }
}

void geometry_transform()
{
    int i;
    int j;

													/*Translation*/
    for (i = 0; i <= storedPolygons; i++)
	{
	    if(polygon[i].properties.classification != NOTHING)
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
	}

	for (i = 0; i <= storedBlocks; i++)
	{
	    if(block[i].properties.classification != NOTHING)
        {
            //X Axis
            block[i].centre.xPosition += (block[i].properties.xVelocity / FRAME_RATE);

            for (j = 0; j < 4; j++)
            {
                block[i].vertices[j].xPosition +=
                    (block[i].properties.xVelocity / FRAME_RATE);
            }
            //Y Axis
            block[i].centre.yPosition += (block[i].properties.yVelocity / FRAME_RATE);

            for (j = 0; j < 4; j++)
            {
                block[i].vertices[j].yPosition +=
                    (block[i].properties.yVelocity / FRAME_RATE);
            }
        }
	}

													/*Rotation*/
	for (i = 0; i <= storedPolygons; i++)
	{
	    if(polygon[i].properties.classification != NOTHING)
        {
			/*Prevents the store angle displacement values from exceeding the 0 to 360 range*/
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
}
