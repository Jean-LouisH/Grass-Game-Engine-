/**
 * 2D Camera
 *
 * Author: Jean-Louis Haywood
 *
 * Manipulates the target and viewport values in the Camera2D struct to move and zoom the 2D Renderer's view.
 */

#pragma once

 /*| Centres to world map when the viewport is larger.*/
void camera_centreToWorld();

/*| Centres camera(X and/or Y) to a specified object.*/
void camera_follow(unsigned char object,
	int objectNumber,
	bool followX,
	bool followY);

/*| Flips the X and Y camera coordinates.*/
void camera_invert(bool x, bool y);

/*| Adjusts the camera zoom in real time.*/
void camera_keepZoomingBy(double deltaWidth);

/*| Prevents the camera frame from crossing specified points.*/
void camera_limitTo(double left,
	double right,
	double down,
	double up);

/*| Shifts camera position.*/
void camera_scroll(double xScroll, double yScroll);					

/*| Shifts camera to a specific point.*/
void camera_scrollToTarget(double newXPosition,
	double newYPosition,
	double scrollSpeed);

/*| Centres camera to a specified point.*/
void camera_setTarget(double newXPosition, double newYPosition);

void camera_setViewportHeight(double cameraHeight);
void camera_setViewportWidth(double cameraWidth);
void camera_zoomToHeight(double targetHeight, double deltaHeight);
void camera_zoomToWidth(double targetWidth, double deltaWidth);
