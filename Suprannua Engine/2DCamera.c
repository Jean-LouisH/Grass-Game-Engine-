#include "SuprannuaEngine.h"

void camera_centreToWorld()
{
	if (camera2D.viewport.width > worldSizeMetres.width &&
		camera2D.viewport.height > worldSizeMetres.height)
	{
		// centres when everything can fit.
		camera_scrollToTarget(worldSizeMetres.width / 2, worldSizeMetres.height / 2, 120.0);
	}
}

void camera_follow(	unsigned char object,
					int objectNumber,
					bool followX,
					bool followY)
{
	switch (object)
	{
		case POLYGON:   //if it's not too wide to bother following.
						if (followX && camera2D.viewport.width < worldSizeMetres.width)
						{
							if (polygon[objectNumber].centre.xPosition > camera2D.target.xPosition)
								camera2D.target.xPosition = polygon[objectNumber].centre.xPosition;

							if (polygon[objectNumber].centre.xPosition < camera2D.target.xPosition)
								camera2D.target.xPosition = polygon[objectNumber].centre.xPosition;
						}
						//if it's not too tall to bother following.
						if (followY && camera2D.viewport.height < worldSizeMetres.height)
						{
							if (polygon[objectNumber].centre.yPosition > camera2D.target.yPosition)
								camera2D.target.yPosition = polygon[objectNumber].centre.yPosition;

							if (polygon[objectNumber].centre.yPosition < camera2D.target.yPosition)
								camera2D.target.yPosition = polygon[objectNumber].centre.yPosition;
						}
		break;
		case BLOCK:       
						if (followX && camera2D.viewport.width < worldSizeMetres.width)
						{
							if (block[objectNumber].centre.xPosition > camera2D.target.xPosition)
								camera2D.target.xPosition = block[objectNumber].centre.xPosition;

							if (block[objectNumber].centre.xPosition < camera2D.target.xPosition)
								camera2D.target.xPosition = block[objectNumber].centre.xPosition;
						}
						if (followY && camera2D.viewport.height < worldSizeMetres.height)
						{
							if (block[objectNumber].centre.yPosition > camera2D.target.yPosition)
								camera2D.target.yPosition = block[objectNumber].centre.yPosition;

							if (block[objectNumber].centre.yPosition < camera2D.target.yPosition)
								camera2D.target.yPosition = block[objectNumber].centre.yPosition;
						}
		break;
	}
}

void camera_keepZoomingBy(double deltaWidth)
{
	camera2D.viewport.width += deltaWidth;

	if (camera2D.viewport.width < 1)
		camera2D.viewport.width = 1; //Prevents zooming to less than 0.

	camera2D.viewport.height = camera2D.viewport.width / (1.777);
	camera_centreToWorld();
}

void camera_limitTo(double left,
					double right,
					double down,
					double up)
{
	if (camera2D.target.xPosition - (camera2D.viewport.width / 2) < left)
		camera2D.target.xPosition = left + (camera2D.viewport.width / 2);

	if (camera2D.target.xPosition + (camera2D.viewport.width / 2) > right)
		camera2D.target.xPosition = right - (camera2D.viewport.width / 2);

	if (camera2D.target.yPosition + (camera2D.viewport.height / 2) > up)
		camera2D.target.yPosition = up - (camera2D.viewport.height / 2);

	if (camera2D.target.yPosition - (camera2D.viewport.height / 2) < down)
		camera2D.target.yPosition = down + (camera2D.viewport.height / 2);
}

void camera_scroll(double xScroll, double yScroll)
{
	camera2D.target.xPosition += xScroll / FRAME_RATE;
	camera2D.target.yPosition += yScroll / FRAME_RATE;
}

void camera_scrollToTarget(	double targetXPosition,
							double targetYPosition,
							double scrollSpeed)
{
	if (camera2D.target.xPosition > targetXPosition)
		camera2D.target.xPosition -= scrollSpeed / FRAME_RATE;

	if (camera2D.target.xPosition < targetXPosition)
		camera2D.target.xPosition += scrollSpeed / FRAME_RATE;

	if (camera2D.target.yPosition > targetYPosition)
		camera2D.target.yPosition -= scrollSpeed / FRAME_RATE;

	if (camera2D.target.yPosition < targetYPosition)
		camera2D.target.yPosition += scrollSpeed / FRAME_RATE;
}

void camera_setTarget(double newXPosition, double newYPosition)
{
    camera2D.target.xPosition = newXPosition;
    camera2D.target.yPosition = newYPosition;
}

void camera_setViewportHeight(double cameraHeight)
{
	camera2D.viewport.height = cameraHeight;
	camera2D.viewport.width = camera2D.viewport.height * (1.777); //16:9 aspect ratio.
	camera_centreToWorld();
}

void camera_setViewportWidth(double cameraWidth)
{
	camera2D.viewport.width = cameraWidth;
	camera2D.viewport.height = camera2D.viewport.width / (1.777); //16:9 aspect ratio.
	camera_centreToWorld();
}

void camera_zoomToHeight(double targetHeight, double deltaHeight)
{
	if (camera2D.viewport.height > targetHeight)
		camera2D.viewport.height -= deltaHeight / FRAME_RATE;

	if (camera2D.viewport.height < targetHeight)
		camera2D.viewport.height += deltaHeight / FRAME_RATE;
}

void camera_zoomToWidth(double targetWidth, double deltaWidth)
{
    if(camera2D.viewport.width > targetWidth)
      camera2D.viewport.width -= deltaWidth / FRAME_RATE;

    if(camera2D.viewport.width < targetWidth)
      camera2D.viewport.width += deltaWidth / FRAME_RATE;
}
