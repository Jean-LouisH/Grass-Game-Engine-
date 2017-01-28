/**
 * 2D Camera
 *
 * Author: Jean-Louis Haywood
 *
 * Manipulates the target and viewport values in the Camera2D struct to move and zoom the 2D Renderer's view.
 */

#pragma once

void camera_centreToWorld();										//Centres to world map when the viewport is larger.

void camera_follow(	unsigned char object,
					int objectNumber,
					bool followX,
					bool followY);									//Centres camera(X and/or Y) to a specified object.

void camera_keepZoomingBy(double deltaWidth);

void camera_limitTo(double left,
					double right,
					double down,
					double up);										//Prevents the camera frame from crossing specified points.

void camera_scroll(double xScroll, double yScroll); 				//Shifts camera position.				

void camera_scrollToTarget(	double newXPosition,
							double newYPosition,
							double scrollSpeed);					//Shifts camera to a specific point.

void camera_setTarget(double newXPosition, double newYPosition);	//Centres camera to a specified point.
void camera_setViewportHeight(double cameraHeight);
void camera_setViewportWidth(double cameraWidth);					
void camera_zoomToHeight(double targetHeight, double deltaHeight);
void camera_zoomToWidth(double targetWidth, double deltaWidth);		
