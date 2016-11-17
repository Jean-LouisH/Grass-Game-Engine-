#include "Definitions.h"

bool logic_isWithinPlatformRange(unsigned char object, int objectNumber, int platformNumber)
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

bool logic_isOnPlatform(unsigned char object, int objectNumber, int platformNumber)
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
                                if(logic_isWithinPlatformRange(object, objectNumber, platformNumber))
                                {
                                    platformFlag = true;
                                }
                            }
                        }
        break;
    }

    return (platformFlag);
}
bool logic_isTouchingUnderPlatform(unsigned char object, int objectNumber, int platformNumber)
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
                                if(logic_isWithinPlatformRange(object, objectNumber, platformNumber))
                                {
                                    platformFlag = true;
                                }
                            }
                        }
        break;
    }

    return (platformFlag);
}
