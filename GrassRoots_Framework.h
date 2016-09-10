#ifndef GRASSROOTS_FRAMEWORK_H
#define GRASSROOTS_FRAMEWORK_H
#endif

#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdbool.h>
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
    double angularDisplacement; //for rotation
    double transparency;
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
void computeTransparency();
void updateHUD();
void resizeObject();
void changeBackgroundColour();
void incrementTime();
void gravitateToObjects();
void gravitateToPlatform();
void gravitateToPoint();

//Render2D
void drawRadialPolygons();
void drawBoxes();
void drawBackground();
void drawGrid();
void adjustCamera();
void renderHUD();

