#include "Definitions.h"
#include "2DCamera.h"

void camera_target(double newXPosition, double newYPosition)
{
    camera2D.target.xPosition = newXPosition;
    camera2D.target.yPosition = newYPosition;
}

void camera_scroll(double xScroll, double yScroll)
{
    camera2D.target.xPosition += xScroll;
    camera2D.target.yPosition += yScroll;
}

void camera_scrollToTarget(double targetXPosition, double targetYPosition, double scrollSpeed)
{
    if(camera2D.target.xPosition > targetXPosition)
      camera2D.target.xPosition -= scrollSpeed;

    if(camera2D.target.xPosition < targetXPosition)
      camera2D.target.xPosition += scrollSpeed;

    if(camera2D.target.yPosition > targetYPosition)
      camera2D.target.yPosition -= scrollSpeed;

    if(camera2D.target.yPosition < targetYPosition)
      camera2D.target.yPosition += scrollSpeed;
}

void camera_resolution(double cameraWidth)
{
    camera2D.viewport.width = cameraWidth;
    camera2D.viewport.height = camera2D.viewport.width / (1.777); //16:9 aspect ratio.

    if(camera2D.viewport.width > worldMap.width &&
       camera2D.viewport.height > worldMap.height)
    {
        camera_scrollToTarget(worldMap.width / 2, worldMap.height / 2, 1.0);// centres worldMap when everything can fit.
    }
}

void camera_zoom(double approach)
{
    camera2D.viewport.width -= approach;
    camera2D.viewport.height = camera2D.viewport.width / (1.777);

    if(camera2D.viewport.width > worldMap.width &&
       camera2D.viewport.height > worldMap.height)
    {
        camera_scrollToTarget(worldMap.width / 2, worldMap.height / 2, 1);
    }
}

void camera_limit(double left, double right, double up, double down)
{
    if(camera2D.target.xPosition - (camera2D.viewport.width/2) < left)
        camera2D.target.xPosition = left + (camera2D.viewport.width/2);

    if(camera2D.target.xPosition + (camera2D.viewport.width/2) > right)
        camera2D.target.xPosition = right - (camera2D.viewport.width/2);

    if(camera2D.target.yPosition + (camera2D.viewport.height/2) > up)
        camera2D.target.yPosition = up - (camera2D.viewport.height/2);

    if(camera2D.target.yPosition - (camera2D.viewport.height/2) < down)
        camera2D.target.yPosition = down + (camera2D.viewport.height/2);
}

void camera_follow(unsigned char object, int objectNumber, bool followX, bool followY)
{
    switch(object)
    {
        case POLYGON:   if(followX && camera2D.viewport.width < worldMap.width) //if it's not too wide to bother following.
                        {
                            if(polygon[objectNumber].centre.xPosition > camera2D.target.xPosition)
                                camera2D.target.xPosition = polygon[objectNumber].centre.xPosition;

                            if(polygon[objectNumber].centre.xPosition < camera2D.target.xPosition)
                                camera2D.target.xPosition = polygon[objectNumber].centre.xPosition;
                        }
                        if (followY && camera2D.viewport.height < worldMap.height) //if it's not too tall to bother following.
                        {
                            if(polygon[objectNumber].centre.yPosition > camera2D.target.yPosition)
                                camera2D.target.yPosition = polygon[objectNumber].centre.yPosition;

                            if(polygon[objectNumber].centre.yPosition < camera2D.target.yPosition)
                                camera2D.target.yPosition = polygon[objectNumber].centre.yPosition;
                        }
        break;
        case BOX:       if(followX && camera2D.viewport.width < worldMap.width)
                        {
                            if(box[objectNumber].centre.xPosition > camera2D.target.xPosition)
                                camera2D.target.xPosition = box[objectNumber].centre.xPosition;

                            if(box[objectNumber].centre.xPosition < camera2D.target.xPosition)
                                camera2D.target.xPosition = box[objectNumber].centre.xPosition;
                        }
                        if (followY && camera2D.viewport.height < worldMap.height)
                        {
                            if(box[objectNumber].centre.yPosition > camera2D.target.yPosition)
                                camera2D.target.yPosition = box[objectNumber].centre.yPosition;

                            if(box[objectNumber].centre.yPosition < camera2D.target.yPosition)
                                camera2D.target.yPosition = box[objectNumber].centre.yPosition;
                        }
        break;
    }
}
