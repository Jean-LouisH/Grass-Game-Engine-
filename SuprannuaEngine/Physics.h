/**
 * Physics
 *
 * Author: Jean-Louis Haywood
 *
 * Calculates all physical effects per time step according to metres, kilograms and seconds.
 */

#pragma once

 /*| Allows objects to settle on or under platforms.*/
void physics_detectPlatformCollision();

/*| Bounces regular polygons from each other.*/
void physics_detectPolygonCollision();

/*| Updates game or simulation time.*/
void physics_incrementTime();

/*| Attracts or repels an object to another based on square inverse distance.*/
void physics_force(unsigned char firstObject,
	int firstObjectNumber,
	unsigned char preposition,	// preposition - "to", "from"
	unsigned char secondObject,
	int secondObjectNumber);

/*| Causes an object to fall or rise.*/
void physics_gravitate(unsigned char object,
	int objectNumber,
	bool direction);

/*| Prevents objects from escaping map dimensions*/
void physics_limitBoundary();
void physics_resistMovement(unsigned char object, int objectNumber, bool direction, double deceleration);

/*| Rotates regular polygons based on velocity and circumference.*/
void physics_roll(unsigned char object, int objectNumber);	
