/**
 * Logic
 *
 * Author: Jean-Louis Haywood
 *
 * Determines if certain logical states within the game are true.
 */

bool logic_isOnPlatform(unsigned char object, int objectNumber, int platformNumber);
bool logic_isWithinPlatformHeight(unsigned char object, int objectNumber, int platformNumber);
bool logic_isTouchingUnderPlatform(unsigned char object, int objectNumber, int platformNumber);
bool logic_isWithinPlatformWidth(unsigned char object, int objectNumber, int platformNumber);
bool logic_isTouchingLeftOfPlatform(unsigned char object, int objectNumber, int platformNumber);
bool logic_isTouchingRightOfPlatform(unsigned char object, int objectNumber, int platformNumber);
bool logic_arePolygonsTouching(int firstObjectNumber, int secondObjectNumber);
