#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



/////////////////////////////////////////////////////////
//Define framework constants
/////////////////////////////////////////////////////////

#define SOFTWARE                "Suprannua"
#define VERSION                 " 0.7.6 "

//Physics
#define PI                      3.1415926535897932384626433832795

//Supported maximums
#define MAX_POLYGONS            500
#define MAX_POLYGON_SIDES       12
#define MAX_BOXES               500
#define MAX_TEXTS               8

#define FULL                    255 //Colour level

#define FRAME_RATE              60.0
#define FRAME_DELAY_MILLISECS   1000.0/FRAME_RATE

//////////////////////////////////////////////////////////
//Enums
//////////////////////////////////////////////////////////
enum colourPalette
{
    BLACK, WHITE, ALPHA, RED, GREEN, BLUE, ORANGE, YELLOW,
    VIOLET, PURPLE, BROWN, SKY_BLUE, GOLD, SEA_GREEN,
    PINK, GREY
};
enum objectName
{
    GAME, POLYGON, BOX
};
enum objectType
{
    NOTHING, BACKGROUND, FOREGROUND, CAMERA, ENTITY, PLATFORM
};
enum attributes
{
    ANGLE, MASS, XVELOCITY, YVELOCITY, GRAVITY, TYPE,
    EDGES, BOUNCE
};
enum prepositions
{
    TO, FROM
};
enum controlModes
{
    GAMEPLAY, MENU
};
enum spinDirections
{
    ANTICLOCKWISE, CLOCKWISE
};
enum gravitation
{
    DOWN, UP
};
enum AIMessages
{
    WAIT
};

/////////////////////////////////////////////////////////
//Structs
/////////////////////////////////////////////////////////

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
    unsigned char colour[4];
    int edges;
    double angle; //for rotation
    double mass;
    double bouncePercentage;
    double xVelocity;
    double yVelocity;
}Property;

typedef struct
{
    Property properties;
    Vertex vertices[MAX_POLYGON_SIDES];
    Vertex centre;
    double radius;
}RegularPolygon;

typedef struct
{
    Property properties;
    Vertex vertices[4];
    Vertex centre;
    Rect dimensions;
}Box;

typedef struct
{
    Vertex textPin;
    char text[128];
    unsigned char classification;
}HeadsUpDisplay;

////////////////////////////////////////////////////////////
//Externs
////////////////////////////////////////////////////////////
//Custom defined
extern char keyStates[256]; //keyboard input buffer
extern char specialKeyStates[21];
extern char gameTitle[64];
extern double dpadSensitivity;

extern Rect worldSizeMetres;

extern double platformGravity;

extern bool isGamePaused;

extern int frameCount;
extern double timeCount;
extern double framesPerSecond;
extern int passedFrames;
extern double startTime;
extern double currentTime;
extern double firstTimeSample;
extern double kernelTime;
extern unsigned char gameState;

extern RegularPolygon polygon[MAX_POLYGONS];
extern Box box[MAX_BOXES];
extern Camera camera2D;

extern HeadsUpDisplay textCache[MAX_TEXTS];

#endif
