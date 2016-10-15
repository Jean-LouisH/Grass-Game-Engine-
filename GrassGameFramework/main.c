/**

                GrassGameFramework

Description:    A superannuated, 2D platformer game framework developed in C and legacy OpenGL.
                For learning purposes in algorithms and coding practice.

Author:         Jean-Louis Haywood
Created:        01/09/2016
Updated:        15/10/2016
Version:        0.6.5

To do;

1. Grass_Compute:   Add Rigid Body calculations.
2.                  Add glColor4f for transparency options.
3.                  Add DrawString for HUD.
4. Grass_Compute:   Radial Collision detection.

*/

#include "Definitions.h"
#include "GLUTCallbackFunctions.h"
#include "GameScript.h"
#include "GrassKernel.h"
#include "main.h"

//Loop iterations
int i;
int j;
int k;

int frameCount = 0;
double timeCount;
char headsUpDisplay[8][32];
char keyStates[256];

RadialPolygon polygon[MAX_POLYGONS] = {0};
Box box[MAX_BOXES]                  = {0};
Camera camera2D;

int main(int argc, char **argv)
{
    runGLUT(argc, argv);
    return 0;
}

void runGLUT(int argc, char **argv)
{
    int screenWidth;
    int screenHeight;

    //GLUT initialisation
    glutInit(&argc, argv);

    screenWidth     =   glutGet(GLUT_SCREEN_WIDTH) * 0.750;
    screenHeight    =   (screenWidth * 0.563);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth) / 2,
                           ((glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) / 2) - 20);
    glutCreateWindow(gameTitle);

    //Run GLUT callback registration
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutDisplayFunc(runGrassKernel);
    glutTimerFunc(FRAME_DELAY_MILLISECS, timer, FRAME_DELAY_MILLISECS);
    glutMainLoop();
}
