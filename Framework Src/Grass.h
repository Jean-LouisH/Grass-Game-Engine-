#ifndef GRASS_H
#define GRASS_H
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
#define PEAK_COLOUR_LEVEL       255.0
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

///////////////////////////////////////////////////////////
//Framework Functions
///////////////////////////////////////////////////////////
//Custom game assets
void initGameData();
void runGameScript();
void readInput();

//Main functions
void runGLUT(int argc, char **argv);
void runGrassKernel(); //display and framework functions on GLUTMainLoop().

//GLUT Callback function prototypes
void timer(int milliseconds);
void reshape(int width, int height);
void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);

//////////////////////////////////
//GrassKernel functions
//////////////////////////////////

//Compute
void compute_findSmallerMapDimension();
void compute_plotPolygon(int objectNumber);
void compute_plotBox(int objectNumber);
void compute_roll(unsigned char object, int objectNumber);
void compute_limitBoundary();
void compute_rigidBodyDynamics();
void detectRadialCollision();
void detectBoxCollision();
void compute_detectPlatformCollision();
void reduceVelocity();
void compute_rotate();
void compute_translate();
void compute_HUD();
void changeBackgroundColour();
void compute_gravitate(unsigned char object, int objectNumber);
void compute_incrementTime();

//Effects
void effects_dayNightCycle(double hoursPerSecond);

//2DRenderer
void render_drawPolygon();
void render_drawBox();
void render_drawGrid();
void render_HUD();

//2DCamera
void camera_set(double newXPosition, double newYPosition);
void camera_scroll(double xScroll, double yScroll);
void camera_follow(unsigned char object, int objectNumber, bool followX, bool followY);

//Editor Instructions
void edit_create(unsigned char object, unsigned char type, int numberOfSides, double newRadius, double newWidth,
       double newHeight, double newXPosition, double newYPosition,
       unsigned char red, unsigned char green, unsigned char blue); //object; "polygon", "box" | type; BACKGROUND, ENTITY, PLATFORM |
void edit_remove(unsigned char object, int objectNumber);
void edit_move(unsigned char object, int objectNumber, double newXPosition, double newYPosition);
void edit_resize(unsigned char object, int objectNumber, double scale);
void edit_change(unsigned char object, int objectNumber, unsigned char attribute, double amount);
            //attributes; "angle", "mass", "xVelocity", "yVelocity", "gravity", "friction"
            //GAME object allows access to gravity and friction.
void edit_adjust(unsigned char object, int objectNumber, unsigned char attribute, double amount);
void edit_colour(unsigned char object, int objectNumber, unsigned char red, unsigned char green, unsigned char blue);
void edit_force(unsigned char firstObject, int firstObjectNumber,
                 unsigned char preposition, unsigned char secondObject, int secondobjectNumber);// preposition - "to", "from"

//Artificial Intelligence
void AI_follow(unsigned char object, int objectNumber);
void AI_avoid(unsigned char object, int objectNumber);
void AI_shoot(unsigned char object, int objectNumber);
void AI_aim(unsigned char object, int objectNumber);
void AI_mimic(unsigned char object, int objectNumber);
void AI_signal(unsigned char message);
void AI_listen();
void AI_spin(unsigned char object, int objectNumber, unsigned char direction, double amount);
void AI_catch(unsigned char object[], int objectNumber);
void AI_travel(unsigned char object[], int objectNumber, double xVelocity, double yVelocity);

