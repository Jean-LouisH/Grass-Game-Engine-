/**
 * Events
 *
 * Author: Jean-Louis Haywood
 *
 * Detects when specific events based on time or positioning of game objects exist.
 */

#pragma once

bool event_arePolygonsTouching(int firstObjectNumber, int secondObjectNumber);
bool event_doFor(double interval);
bool event_hasFalleninAHole(unsigned char object, int objectNumber);
bool event_hasPolygonPastXLocation(int objectNumber, double xPosition);
bool event_hasPolygonPastYLocation(int objectNumber, double yPosition);
bool event_isPolygonHigher(int firstObjectNumber, int secondObjectNumber);
bool event_isOnCycle(double interval);	//Allows continuous operations on a time cycle.

bool event_isOnPlatform(unsigned char object,
	int objectNumber,
	int platformNumber);

bool event_isOnceEvery(double interval);	//Allows single operations on a time cycle.

bool event_isOnInstant();

bool event_isPolygonAirboune(unsigned char object,
	int objectNumber);

bool event_isTouchingLeftOfPlatform(unsigned char object,
	int objectNumber,
	int platformNumber);

bool event_isTouchingRightOfPlatform(unsigned char object,
	int objectNumber,
	int platformNumber);

bool event_isTouchingUnderPlatform(unsigned char object,
	int objectNumber,
	int platformNumber);

bool event_isPolygonWithinRadius(int firstObjectNumber,
	double radius,
	int secondObjectNumber);

bool event_isWithinPlatformHeight(unsigned char object,
	int objectNumber,
	int platformNumber);

bool event_isWithinPlatformWidth(unsigned char object,
	int objectNumber,
	int platformNumber);

bool event_isWithinTime(double startTime, double endTime);