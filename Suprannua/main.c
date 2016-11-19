/**

                Suprannua

Description:    A superannuated, 2D platformer, code reuse game framework developed in C and legacy OpenGL.
                For learning purposes in algorithms and coding practice.

Author:         Jean-Louis Haywood
Created:        01/09/2016

*/

#include "Definitions.h"
#include "GLUTCallbackFunctions.h"
#include "GameScript.h"
#include "Kernel.h"
#include "main.h"


int frameCount                          = 0;
double timeCount;
double framesPerSecond;
int passedFrames;
double startTime;
double currentTime;
double firstTimeSample;
double kernelTime;

unsigned char gameState                 = GAMEPLAY;
char keyStates[256];
char specialKeyStates[21];

HeadsUpDisplay textCache[8];
RegularPolygon polygon[MAX_POLYGONS]    = {0};
Block block[MAX_BLOCKS]                 = {0};
Camera camera2D;

int main(int argc, char **argv)
{
    runGLUT(argc, argv);
    return 0;
}

void runGLUT(int argc, char **argv)
{
    int screenWidthPixels;
    int screenHeightPixels;

    //GLUT initialisation
    glutInit(&argc, argv);

    screenWidthPixels     =   glutGet(GLUT_SCREEN_WIDTH) * 0.750;
    screenHeightPixels    =   (screenWidthPixels * 0.563);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(screenWidthPixels, screenHeightPixels);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidthPixels) / 2,
                           ((glutGet(GLUT_SCREEN_HEIGHT) - screenHeightPixels) / 2) - 20);
    glutCreateWindow(gameTitle);

    //Run GLUT callback registration
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(keySpecial);
    glutSpecialUpFunc(keyUpSpecial);
    glutReshapeFunc(resize);

    glutDisplayFunc(runKernel);
    glutTimerFunc(FRAME_DELAY_MILLISECS, timer, FRAME_DELAY_MILLISECS);
    glutMainLoop();
}
