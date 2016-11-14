//2DCamera
void camera_setTarget(double newXPosition, double newYPosition);//centres camera to a specified point.
void camera_scroll(double xScroll, double yScroll);//increments or decrements camera position.
void camera_scrollToTarget(double newXPosition, double newYPosition, double scrollSpeed);//increments or decrements to a specified point
void camera_setWidth(double cameraWidth);//sets the viewport to a specified width.
void camera_setHeight(double cameraHeight);
void camera_fitWorldSize();
void camera_zoom(double deltaWidth);//gradually zooms camera in or out.
void camera_limit(double left, double right, double down, double up);//prevents the camera frame from crossing specified points.
void camera_follow(unsigned char object, int objectNumber, bool followX, bool followY);//centres camera(X and/or Y) to a specified object.
