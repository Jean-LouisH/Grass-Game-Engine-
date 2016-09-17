#ifndef GRASSROOTS_FRAMEWORK_H
#define GRASSROOTS_FRAMEWORK_H
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
//Physics
#define PEAK_COLOUR_LEVEL       255
#define PI                      3.141592

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
    POLYGON, BOX
};

enum objectType
{
    BACKGROUND, ENTITY, PLATFORM
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

extern int frameCount;

extern RadialPolygon polygon[MAX_POLYGONS];
extern Box box[MAX_BOXES];

extern char headsUpDisplay[8][32];

///////////////////////////////////////////////////////////
//Framework Functions
///////////////////////////////////////////////////////////
//Custom game assets
void initGameData();
void runGameScript();
void readInput();

//Main functions
void runGLUT(int argc, char **argv);

//GLUT Callback function prototypes
void runGrassKernel(); //display and framework functions on GLUTMainLoop().
void timer(int milliseconds);
void reshape(int width, int height);
void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);

//////////////////////////////////
//GrassKernel functions
//////////////////////////////////

//Compute
void limitBoundary();
void detectRadialCollision();
void detectBoxCollision();
void detectPlatformCollision();
void reduceVelocity();
void translateRotation();
void translatePosition();
void updateHUD();
void changeBackgroundColour();
void incrementTime();

//Render2D
void drawRadialPolygons();
void drawBoxes();
void drawBackground();
void drawGrid();
void adjustCamera();
void renderHUD();

//Instructions

void grass_create(unsigned char object, unsigned char type, double newRadius, double newWidth,
       double newHeight, double newXPosition, double newYPosition,
       unsigned char red, unsigned char green, unsigned char blue); //object; "polygon", "box" | type; BACKGROUND, ENTITY, PLATFORM |
void grass_remove(char object[], int objectNumber[]);
void grass_move(char object[], int objectNumber, double xPosition, double yPosition);
void grass_resize(char object[], int objectNumber, double scale);
void grass_change(char object[], int objectNumber, char attribute[], double amount);
            //property; "angle", "mass", "xVelocity", "yVelocity", "gravity", "friction"
void grass_colour(int red, int green, int blue);
void grass_gravitate(char object[], int objectNumber);
void grass_force(char firstObject[], int firstObjectNumber,
                 char preposition[], char secondObject[], int secondobjectNumber);// preposition - "to", "from"

//Artificial Intelligence

void AI_follow(char object[], int objectNumber);
void AI_avoid(char object[], int objectNumber);
void AI_shoot(char object[], int objectNumber);
void AI_aim(char object[], int objectNumber);
void AI_mimic(char object[], int objectNumber);
void AI_signal(char message[]);
void AI_listen();
void AI_catch(char object[], int objectNumber);
void AI_travel(char object[], int objectNumber, double xVelocity, double yVelocity);

