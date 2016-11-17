//Compute
void physics_roll(unsigned char object, int objectNumber);//rotates radial objects based on velocity and circumference.
void physics_limitBoundary();//prevents objects from escaping map dimensions.
void physics_rigidBodyDynamics();//computes rag doll effects based on objects angle of edge from platform surface.
void physics_detectCollision();//bounces radial polygons from each other
void physics_detectPlatformCollision();//allows objects to settle on platforms or bounce from under.
void physics_gravitate(unsigned char object, int objectNumber, bool direction);//causes an object to fall.
void physics_incrementTime();//updates game or simulation time.
