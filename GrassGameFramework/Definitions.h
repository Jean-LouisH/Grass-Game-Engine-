#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#endif

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

/////////////////////////////////////////////////////////
//Define framework constants
/////////////////////////////////////////////////////////

#define VERSION                 "0.5.2"

//Physics
#define PEAK_COLOUR_LEVEL       255.0
#define PI                      3.1415926535897932384626433832795

//Supported maximums
#define MAX_POLYGONS            50
#define MAX_POLYGON_SIDES       8
#define MAX_BOXES               50

#define FRAME_DELAY_MILLISECS   17

//////////////////////////////////////////////////////////
//Enums, structs
//////////////////////////////////////////////////////////
enum RGBColours
{
    RED, GREEN, BLUE
};
enum objectName
{
    GAME, POLYGON, BOX
};
enum objectType
{
    NOTHING, BACKGROUND, ENTITY, PLATFORM
};
enum attributes
{
    ANGLE, MASS, XVELOCITY, YVELOCITY, GRAVITY, FRICTION
};
enum prepositions
{
    TO, FROM
};
enum spinDirections
{
    ANTICLOCKWISE, CLOCKWISE
};
enum AIMessages
{
    WAIT
};

typedef struct
{
    double xPosition;
    double yPosition;
}Vertex;

typedef struct
{
    Vertex target;
}Camera;

typedef struct
{
    unsigned char classification; //backgrounds, entities, platforms
    unsigned char colour[3];
    double acceleration;
    double angle; //for rotation
    int sides;
    int layer; //arranges objects by distance from screen
    double mass;
    double xVelocity;
    double yVelocity;
}Property;

typedef struct
{
    Property properties;
    Vertex vertices[MAX_POLYGON_SIDES];
    Vertex centre;
    double radius;
}RadialPolygon;

typedef struct
{
    Property properties;
    Vertex vertices[4];
    Vertex centre;
    double boxWidth;
    double boxHeight;
}Box;

////////////////////////////////////////////////////////////
//Externs
////////////////////////////////////////////////////////////
//Custom defined
extern char keyStates[256];
extern char gameTitle[64];
extern int screenWidth;
extern int screenHeight;
extern double dpadSensitivity;
extern double xMapSize;
extern double yMapSize;
extern bool gamePause;

extern double friction;
extern double objectGravity;
extern double platformGravity;
extern double pointGravity[8];

//Loop iterations
extern int i;
extern int j;
extern int k;

extern int frameCount;
extern double timeCount;
extern double smallerMapDimension;

extern RadialPolygon polygon[MAX_POLYGONS];
extern Box box[MAX_BOXES];
extern Camera camera2D;

extern char headsUpDisplay[8][32];
