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

#define VERSION                 "0.6.5"

//Physics
#define PI                      3.1415926535897932384626433832795

//Supported maximums
#define MAX_POLYGONS            50
#define MAX_POLYGON_SIDES       12
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
    double width;
    double height;
}Rect;

typedef struct
{
    Vertex target;
    Rect viewport;
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
extern char keyStates[256]; //keyboard input buffer
extern char gameTitle[64];
extern double dpadSensitivity;

extern Rect worldMap;
extern bool gamePause;

extern double friction; //for bounce calculations
extern double objectGravity;
extern double platformGravity;

//Loop iterations
extern int i;
extern int j;
extern int k;

extern int frameCount;
extern double timeCount;

extern RadialPolygon polygon[MAX_POLYGONS];
extern Box box[MAX_BOXES];
extern Camera camera2D;

extern char headsUpDisplay[8][32];
