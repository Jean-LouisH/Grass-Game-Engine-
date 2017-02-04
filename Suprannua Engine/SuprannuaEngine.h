/**
 * SuprannuaEngine
 *
 * Author: Jean-Louis Haywood
 *
 * Contains all external references, global variables, structs and enums relevant to all parts of the game engine.
 */

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "resource.h"

#include "2DCamera.h"
#include "2DRenderer.h"
#include "AI.h"
#include "Editor.h"
#include "EngineKernel.h"
#include "Events.h"
#include "Game.h"
#include "Geometry.h"
#include "FreeglutCallbacks.h"
#include "Input.h"
#include "Physics.h"
#include "Text.h"

/*Define engine constants*/

#define SOFTWARE                "Suprannua Engine"
#define VERSION                 " 0.14.1 "

#define PI                      3.1415926535897932384626433832795
#define FULL                    255 //Colour level
#define FRAME_RATE              60.0
#define FRAME_TIME_MILLISECS	1000.0/FRAME_RATE

#define MAX_POLYGONS            1000
#define MAX_POLYGON_SIDES       20
#define MAX_BLOCKS              1000
#define MAX_TEXTS               1000

/*Enums*/

enum colourPalette
{
    RED,
	GREEN,
	BLUE,
	ALPHA,
	BLACK,
	WHITE,
	ORANGE,
	YELLOW,
    VIOLET,
	PURPLE,
	BROWN,
	SKY_BLUE,
	GOLD,
	SEA_GREEN,
	PINK,
	GREY,
	DARK_RED,
	DARK_GREEN,
	DARK_BLUE,
	DARK_BROWN,
	MAGENTA,
	DARK_GREY
};
enum objectName
{
    GAME,
	POLYGON,
	BLOCK,
	TEXT,
	CAMERA
};
enum objectType
{
    NOTHING,
	BACKGROUND,
	FOREGROUND,
	HUD,
	ENTITY,
	AIRBOURNE,
	PLATFORM
};
enum attributes
{
    ANGLE,
	MASS,
	PLATFORM_GRAVITY,
	GRAVITY_CONSTANT,
	TYPE,
	XVELOCITY,
	YVELOCITY,
	EDGES,
	BOUNCE,
	XPOSITION,
	YPOSITION,
	WIDTH,
	HEIGHT,
	RADIUS,
	XCENTRE,
	YCENTRE
};
enum prepositions
{
    TO,
	FROM
};
enum controlModes
{
    GAMEPLAY,
	MENU,
	CUSTOM1,
	CUSTOM2,
	CUSTOM3,
	TESTING
};
enum spinDirections
{
    ANTICLOCKWISE,
	CLOCKWISE
};
enum gravitation
{
    DOWN,
	UP
};
enum platformScrolling
{
	UP_DOWN,
	LEFT_RIGHT
};
enum AIMessages
{
    WAIT
};

/*Structs*/

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
	double bouncePercentage;
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
    char textContent[128];
	unsigned char colour[4];
    unsigned char classification;
}Text;

/*Externs*/

extern bool keyStates[128]; //keyboard input buffer
extern bool specialKeyStates[128];

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
extern Text textCache[MAX_TEXTS];

extern int storedPolygons;
extern int storedBlocks;
extern int storedTexts;

extern bool isKernelStatsEnabled;
extern bool isGridEnabled;

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
extern unsigned char darkRed[3];
extern unsigned char darkGreen[3];
extern unsigned char darkBlue[3];
extern unsigned char darkBrown[3];
extern unsigned char magenta[3];
extern unsigned char darkGrey[3];
