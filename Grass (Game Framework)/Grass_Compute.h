//Compute
void compute_findSmallerMapDimension();
void compute_plotPolygon(int objectNumber);
void compute_plotBox(int objectNumber);
bool compute_isOnPlatform(unsigned char firstObject, int firstObjectNumber, unsigned char secondObject, int secondObjectNumber);
void compute_roll(unsigned char object, int objectNumber);
void compute_limitBoundary();
void compute_rigidBodyDynamics();
void detectRadialCollision();
void detectBoxCollision();
void compute_detectPlatformCollision();
void reduceVelocity();
void compute_rotate();
void compute_translate();
void compute_HUD();
void changeBackgroundColour();
void compute_gravitate(unsigned char object, int objectNumber);
void compute_incrementTime();
