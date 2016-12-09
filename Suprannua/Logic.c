#include "Suprannua.h"

bool logic_isWithinPlatformWidth(unsigned char object, int objectNumber, int platformNumber)
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

bool logic_isWithinPlatformHeight(unsigned char object, int objectNumber, int platformNumber)
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

bool logic_isOnPlatform(unsigned char object, int objectNumber, int platformNumber)
{
    switch(object)
    {
        case POLYGON:
                        if(block[platformNumber].properties.classification == PLATFORM)
                        {
                            if(polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius <=
                                block[platformNumber].centre.yPosition + (block[platformNumber].dimensions.height / 2) &&
                               polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius >
                                block[platformNumber].centre.yPosition - (block[platformNumber].dimensions.height / 2))
                            {
								if (logic_isWithinPlatformWidth(object, objectNumber, platformNumber))
								{
									return true;
								}
								else
									return false;
                            }
                        }
        break;
		//To add block case
    }
}

bool logic_isTouchingUnderPlatform(unsigned char object, int objectNumber, int platformNumber)
{
    switch(object)
    {
        case POLYGON:
                        if(block[platformNumber].properties.classification == PLATFORM)
                        {
                            if (polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius >=
                                    block[platformNumber].centre.yPosition - (block[platformNumber].dimensions.height / 2) &&
                                polygon[objectNumber].centre.yPosition + polygon[objectNumber].radius <
                                    block[platformNumber].centre.yPosition + (block[platformNumber].dimensions.height / 2))
                            {
								if (logic_isWithinPlatformWidth(object, objectNumber, platformNumber))
								{
									return true;
								}
								else
									return false;
                            }
                        }
        break;
		//To add block case
    }
}

bool logic_isTouchingLeftOfPlatform(unsigned char object, int objectNumber, int platformNumber)
{
    if(object == POLYGON)
    {
        if(block[platformNumber].properties.classification == PLATFORM)
        {
            if(	polygon[objectNumber].centre.xPosition + polygon[objectNumber].radius >=
				block[platformNumber].centre.xPosition - (block[platformNumber].dimensions.width / 2) &&
				polygon[objectNumber].centre.xPosition + polygon[objectNumber].radius <
				block[platformNumber].centre.xPosition + (block[platformNumber].dimensions.width / 2))
            {
				if (logic_isWithinPlatformHeight(object, objectNumber, platformNumber))
				{
					return true;
				}
				else
					return false;
            }
        }
    }
}

bool logic_isTouchingRightOfPlatform(unsigned char object, int objectNumber, int platformNumber)
{
    if(object == POLYGON)
    {
        if(block[platformNumber].properties.classification == PLATFORM)
        {
            if(	polygon[objectNumber].centre.xPosition - polygon[objectNumber].radius <=
				block[platformNumber].centre.xPosition + (block[platformNumber].dimensions.width / 2) &&
				polygon[objectNumber].centre.xPosition - polygon[objectNumber].radius >
				block[platformNumber].centre.xPosition - (block[platformNumber].dimensions.width / 2))
            {
				if (logic_isWithinPlatformHeight(object, objectNumber, platformNumber))
				{
					return true;
				}
				else
					return false;
            }
        }
    }
}

bool logic_arePolygonsTouching(int firstObjectNumber, int secondObjectNumber)
{
	if (geometry_findDistance(POLYGON, firstObjectNumber, POLYGON, secondObjectNumber) <
		polygon[firstObjectNumber].radius + polygon[secondObjectNumber].radius)
	{
		return true;
	}
	else
		return false;
}
