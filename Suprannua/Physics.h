/**
* Physics
*
* Calculates all physical effects per time step according to metres, kilograms and seconds.
*/

void physics_roll(unsigned char object, int objectNumber); //Rotates regular polygons based on velocity and circumference.
void physics_limitBoundary(); //Prevents objects from escaping map dimensions.
void physics_rigidBodyDynamics(); //Computes rag doll effects based on objects angle of edge from platform surface.
void physics_detectPolygonCollision(); //Bounces regular polygons from each other.
void physics_detectPlatformCollision(); //Allows objects to settle on or under platforms.
void physics_gravitate(unsigned char object, int objectNumber, bool direction); //Causes an object to fall or rise.
void physics_incrementTime(); //Updates game or simulation time.
void physics_force(unsigned char firstObject, int firstObjectNumber,
					unsigned char preposition, unsigned char secondObject, int secondobjectNumber);
					// Attracts or repels an object to another based on square inverse distance.
					// preposition - "to", "from"
