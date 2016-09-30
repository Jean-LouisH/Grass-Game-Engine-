#include "Grass.h"

void camera_set(double newXPosition, double newYPosition)
{
    camera2D.target.xPosition = newXPosition;
    camera2D.target.yPosition = newYPosition;
}

void camera_scroll(double xScroll, double yScroll)
{
    camera2D.target.xPosition += xScroll;
    camera2D.target.yPosition += yScroll;
}

void camera_follow(unsigned char object, int objectNumber, bool followX, bool followY)
{
    switch(object)
    {
        case POLYGON:   if(followX)
                        {
                            if(camera2D.target.xPosition < (xMapSize - 25))
                                if(polygon[objectNumber].centre.xPosition > camera2D.target.xPosition)
                                    camera_set(polygon[objectNumber].centre.xPosition, yMapSize/2);

                            if(camera2D.target.xPosition > 25)
                                if(polygon[0].centre.xPosition < camera2D.target.xPosition)
                                    camera_set(polygon[0].centre.xPosition, yMapSize/2);
                        }
        break;
    }
}
