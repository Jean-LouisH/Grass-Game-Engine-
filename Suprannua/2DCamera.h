/**
* 2D Camera
*
* Manipulates the target and viewport values in the Camera2D struct variable to move and zoom the 2D Renderer's view.
*/

void camera_setTarget(double newXPosition, double newYPosition); //Centres camera to a specified point.
void camera_scroll(double xScroll, double yScroll); //Shifts camera position.
void camera_scrollToTarget(double newXPosition, double newYPosition, double scrollSpeed); //Shifts camera to a specific point.
void camera_setWidth(double cameraWidth); //Sets the viewport to a specified width.
void camera_setHeight(double cameraHeight); //Sets the viewport to a specified height.
void camera_centreWorldSize(); //Centres the camera to the world when the entire viewport is larger than it.
void camera_keepZoomingBy(double deltaWidth); //Gradually zooms camera in or out.
void camera_zoomToWidth(double targetWidth, double deltaWidth); //Zooms to a specific width.
void camera_zoomToHeight(double targetHeight, double deltaHeight); //Zooms to a specific height.
void camera_limitTo(double left, double right, double down, double up); //Prevents the camera frame from crossing specified points.
void camera_follow(unsigned char object, int objectNumber, bool followX, bool followY); //Centres camera(X and/or Y) to a specified object.
