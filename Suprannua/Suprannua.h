#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/**
* Suprannua.h
*
* Contains all external references, global variables, structs and enums relevant to all parts of the game engine.
*/

#define _CRT_SECURE_NO_WARNINGS 

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "2DCamera.h"
#include "2DRenderer.h"
#include "AI.h"
#include "Editor.h"
#include "Game.h"
#include "Geometry.h"
#include "GLUT.h"
#include "HUD.h"
#include "Input.h"
#include "Kernel.h"
#include "Logic.h"
#include "Physics.h"

/////////////////////////////////////////////////////////
//Define framework constants
/////////////////////////////////////////////////////////

#define SOFTWARE                "Suprannua"
#define VERSION                 " 0.10.0 "

#define PI                      3.1415926535897932384626433832795
#define FULL                    255 //Colour level
#define FRAME_RATE              60.0
#define FRAME_DELAY_MILLISECS   1000.0/FRAME_RATE

#define MAX_POLYGONS            1000
#define MAX_POLYGON_SIDES       12
#define MAX_BLOCKS              1000
#define MAX_TEXTS               8

//////////////////////////////////////////////////////////
//Enums
//////////////////////////////////////////////////////////

enum colourPalette
{
    RED, GREEN, BLUE, ALPHA, BLACK, WHITE, ORANGE, YELLOW,
    VIOLET, PURPLE, BROWN, SKY_BLUE, GOLD, SEA_GREEN,
    PINK, GREY
};
enum objectName
{
    GAME, POLYGON, BLOCK, TEXT, CAMERA
};
enum objectType
{
    NOTHING, BACKGROUND, FOREGROUND, HUD, ENTITY, PLATFORM
};
enum attributes
{
    ANGLE, MASS, PLATFORM_GRAVITY, GRAVITY_CONSTANT, TYPE, 
	XVELOCITY, YVELOCITY, EDGES, BOUNCE, XPOSITION, YPOSITION,
	WIDTH, HEIGHT, RADIUS, XCENTRE, YCENTRE
};
enum prepositions
{
    TO, FROM
};
enum controlModes
{
    GAMEPLAY, MENU, CUSTOM1, CUSTOM2, CUSTOM3
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
}Block;

typedef struct
{
    Vertex textPin;
    char text[128];
    unsigned char classification;
}HeadsUpDisplay;

////////////////////////////////////////////////////////////
//Externs
////////////////////////////////////////////////////////////

extern bool keyStates[256]; //keyboard input buffer
extern bool specialKeyStates[21];
extern char gameTitle[64];
extern double dpadSensitivity;

extern Rect worldSizeMetres;

extern double platformGravity;
extern double gravityConstant;

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
extern Block block[MAX_BLOCKS];
extern Camera camera2D;

extern int occupiedPolygons;
extern int occupiedBlocks;
extern bool gridState;

extern HeadsUpDisplay textCache[MAX_TEXTS];

extern unsigned char black[3];
extern unsigned char white[3];
extern unsigned char red[3];
extern unsigned char green[3];
extern unsigned char blue[3];
extern unsigned char orange[3];
extern unsigned char yellow[3];
extern unsigned char violet[3];
extern unsigned char purple[3];
extern unsigned char brown[3];
extern unsigned char skyBlue[3];
extern unsigned char gold[3];
extern unsigned char seaGreen[3];
extern unsigned char pink[3];
extern unsigned char grey[3];

#endif
