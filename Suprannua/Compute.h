//Compute
void compute_plotPolygon(int objectNumber);//plot polygon points based on number of sides, and radius.
void compute_plotBox(int objectNumber);//plot box points based on centre, height and width.
bool compute_isOnPlatform(unsigned char object, int objectNumber, int platformNumber);
bool compute_isTouchingUnderPlatform(unsigned char object, int objectNumber, int platformNumber);
bool compute_isWithinPlatformRange(unsigned char object, int objectNumber, int platformNumber);
void compute_roll(unsigned char object, int objectNumber);//rotates radial objects based on velocity and circumference.
void compute_limitBoundary();//prevents objects from escaping map dimensions.
void compute_rigidBodyDynamics();//computes rag doll effects based on objects angle of edge from platform surface.
void detectRadialCollision();//bounces radial polygons from each other
void compute_detectPlatformCollision();//allows objects to settle on platforms or bounce from under.
void compute_transform(); //update points based on velocity.
void compute_gravitate(unsigned char object, int objectNumber, bool direction);//causes an object to fall.
void compute_incrementTime();//updates game or simulation time.
